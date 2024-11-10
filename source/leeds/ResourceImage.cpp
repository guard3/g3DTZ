#include <cstddef>
#include <cstring>
#include <format>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <zlib.h>

#include "ResourceImage.h"

#include "RslEngine.h"
#include "Pools.h"
#include "ModelInfo.h"
#include "Zones.h"
#include "TexListStore.h"
#include "ColStore.h"
#include "CullZones.h"
#include "Streaming.h"
#include "AnimManager.h"
#include "Ped.h"
#include "PedType.h"
#include "PedStats.h"
#include "WaterLevel.h"
#include "HandlingMgr.h"
#include "SurfaceTable.h"
#include "TimeCycle.h"
#include "Population.h"
#include "ParticleMgr.h"
#include "WeaponInfo.h"
#include "CutsceneMgr.h"
#include "Ferry.h"
#include "Train.h"
#include "Plane.h"
#include "SampMan.h"

namespace fs = std::filesystem;

struct sResourceImage
{
	void* pThePaths;
	CBuildingPool      *buildingPool;
	CTreadablePool     *treadablePool;
	CDummyPool         *dummyPool;
	CEntryInfoNodePool *entryInfoNodePool;
	CPtrNodePool       *ptrNodePool;
	uint32              numModelInfos;
	CBaseModelInfo    **modelInfoPtrs;
	void* m_pCarArrays;
	void* m_pTotalNumOfCarsOfRating;
	CTheZones          *theZones;
	void* m_pSectors;
	void* m_BigBuildingList;
	uint32              num2deffects;
	C2dEffect          *p2deffects;
	void               *modelIndices;
	CPool<TexListDef>  *texListPool;
	RslTexList         *storedTexList;
	CPool<ColDef>      *colPool;
	bool                colOnlyBB;
	void* tempColModels;
	CObjectInfo        *objectInfo;
	void               *vehicleModelInfoInst; // Static variables of CVehicleModelInfo; nullptr in VCS
	CStreaming         *streamingInst;
	CAnimManager       *animManagerInst;
	tFightMove         *fightMoves;
#ifdef LCS
	void* pedAnimInfo;
#endif
	CPedType** pedType;
	CPedStats** pedStats;
#ifdef VCS
	RslRGB(*RGBTable)[128]; // The ped and car colour table in VCS
	void* unknown1;
#endif
	int32           numAttributeZones;
	CAttributeZone *attributeZones;
	int32           numOccludersOnMap; // always 0
	void           *occluders;         // always nullptr
	CWaterLevel    *waterLevelInst;
#ifdef LCS
	CHandlingDataMgr* handlingManagerInst;
#else
	void* weatherTypeList;
#endif
	float             (*adhesiveLimitTable)[6];
	CTimeCycle         *timecycle;
	int32             (*pedGroups)[16];
	CParticleSystemMgr *particleSystemManager;
	CWeaponInfo       **weaponTables;
#ifdef VCS
	int unknown2;
#endif
	int _3dmarkerArray;
	CDirectory *cutsceneDir;
#ifdef LCS
	CFerry* ferryInst;
	CTrain* trainInst;
#else
	uint32 unknown3;
	uint32 unknown4;
#endif
	CPlane* planeInst;
#if defined VCS || defined PSP
	tSample* soundSamples;
#endif

	int menuCompressedTextures;
#ifdef VCS
	void* unknown7;
	void* unknown8;
	void* unknown9;
	void* unknown10;
	void* fontdef;
#endif
	int fontTexListSize;
	int fontCompressedTexList;
#ifdef VCS
	void* radarTextures;
#endif
};

void
LoadResourceImage(fs::path iPath, const base::sChunkHeader& header, std::istream& iStream) {
	static std::vector<std::byte> mem;

	/* Check the ident of the header */
	if (header.ident == 'GTAG') {
		/* GAME.DAT ident found, load input file as is */
		if (header.fileEnd <= sizeof(header))
			throw std::runtime_error("Input file is invalid");
		mem.resize(header.fileEnd);
		std::memcpy(mem.data(), &header, sizeof(header));
		if (!iStream.read(reinterpret_cast<char*>(mem.data() + sizeof(header)), header.fileEnd - sizeof(header)))
			throw std::runtime_error(iStream.gcount() == 0 ? "Cannot read from input file" : "Input file is invalid");
	} else {
		/* Ident is not recognised, set up a zlib stream for potentially compressed input */
		z_stream z{};
		switch (inflateInit(&z)) {
		case Z_OK:
			break;
		case Z_MEM_ERROR:
			throw std::bad_alloc();
		default:
			throw std::runtime_error("Cannot initialize zlib stream");
		}

		try {
			/* Copy the header chunk we already have and read enough bytes to fill the temp buffer */
			union {
				std::byte buff[4096];
				struct {
					std::byte in[2048];
					std::byte out[2048];
				} temp;
			};
			std::memcpy(temp.in, &header, sizeof(header));
			if (!iStream.read(reinterpret_cast<char*>(temp.in + sizeof(header)), sizeof(temp.in) - sizeof(header)))
				throw std::runtime_error(iStream.gcount() == 0 ? "Cannot read input file" : "Input file is invalid");

			/* Perform the first decompression step */
			z.avail_in = sizeof(temp.in);
			z.next_in = reinterpret_cast<Byte*>(temp.in);
			z.avail_out = sizeof(temp.out);
			z.next_out = reinterpret_cast<Byte*>(temp.out);
			if (int ret = inflate(&z, Z_SYNC_FLUSH); ret == Z_MEM_ERROR)
				throw std::bad_alloc();
			else if (ret != Z_OK || z.total_out <= sizeof(header))
				throw std::runtime_error(z.msg ? std::format("Zlib error: {}", z.msg) : "Input file is invalid");

			/* At this point we've produced enough bytes to read the header */
			auto pHeader = reinterpret_cast<base::sChunkHeader*>(temp.out);
			if (pHeader->ident != 'GTAG' || pHeader->fileEnd < z.total_out)
				throw std::runtime_error("Input file is invalid");

			/* For the output, allocate enough memory and copy over whatever decompressed data we have so far */
			mem.resize(pHeader->fileEnd);
			std::memcpy(mem.data(), temp.out, z.total_out);

			/* For the input, copy any unprocessed bytes that may be left and read more to fill the buffer */
			std::memcpy(buff, z.next_in, z.avail_in);
			if (!iStream.read(reinterpret_cast<char*>(buff + z.avail_in), sizeof(buff) - z.avail_in) && iStream.gcount() == 0)
				throw std::runtime_error("Cannot read input file");

			/* Start the decompression loop */
			z.avail_in += static_cast<uInt>(iStream.gcount());
			z.next_in = reinterpret_cast<Byte*>(buff);
			for (;;) {
				z.avail_out = mem.size() - z.total_out;
				z.next_out = reinterpret_cast<Byte*>(mem.data() + z.total_out);
				if (int ret = inflate(&z, Z_NO_FLUSH); ret == Z_STREAM_END)
					break;
				else if (ret == Z_MEM_ERROR)
					throw std::bad_alloc();
				else if (ret != Z_OK || z.avail_out == 0)
					throw std::runtime_error(z.msg ? std::format("Zlib error: {}", z.msg) : "Input file is invalid");
				/* If all input bytes are consumed, attempt to read more */
				if (z.avail_in == 0) {
					if (!iStream.read(reinterpret_cast<char*>(buff), sizeof(buff)) && iStream.gcount() == 0)
						throw std::runtime_error("Cannot read input file");
					z.avail_in = static_cast<uInt>(iStream.gcount());
					z.next_in = reinterpret_cast<Byte*>(buff);
				}
			}
		} catch (...) {
			/* If any exception occurs, cleanup the zlib stream before propagating the exception */
			inflateEnd(&z);
			throw;
		}

		/* Decompression is over, clean up the zlib stream */
		inflateEnd(&z);

		/* Also save GAME.DAT to disk */
		std::ofstream f(iPath.replace_extension("dat").filename(), std::ios::binary);
		if (!f.write(reinterpret_cast<const char*>(mem.data()), mem.size()))
			throw std::runtime_error("Cannot write to output file");
	}

	sResourceImage* pResourceImage = reinterpret_cast<sResourceImage*>(base::cRelocatableChunk::Load(mem.data()));

	/* Initialize pools */
	CPools::LoadPool(pResourceImage->buildingPool);
	CPools::LoadPool(pResourceImage->treadablePool);
	CPools::LoadPool(pResourceImage->dummyPool);
	CPools::LoadPool(pResourceImage->entryInfoNodePool);
	CPools::LoadPool(pResourceImage->ptrNodePool);

	/* Initialize stores */
	CTexListStore::Load(pResourceImage->storedTexList, pResourceImage->texListPool);
	CColStore::Load(pResourceImage->colOnlyBB, pResourceImage->colPool);

	/* Initialize modelinfo */
	CModelInfo::Load(pResourceImage->numModelInfos, pResourceImage->modelInfoPtrs);
	CModelInfo::Load2dEffects(pResourceImage->num2deffects, pResourceImage->p2deffects);
	CVehicleModelInfo::Load(pResourceImage->vehicleModelInfoInst);

	/* Initialize object data */
	CObjectData::Load(pResourceImage->objectInfo);

	/* Initialize cull zones */
	CCullZones::Init(pResourceImage->numAttributeZones, pResourceImage->attributeZones);

	/* Initialize Streaming */
	CStreaming::Initialize(pResourceImage->streamingInst);

	/* Initialize animations */
	CAnimManager::Load(pResourceImage->animManagerInst);

	/* Initialize ped stuff */
	CPed::LoadFightData(pResourceImage->fightMoves);
	CPedType::Initialize(pResourceImage->pedType);
	CPedStats::Load(pResourceImage->pedStats);

	CSurfaceTable::Load(pResourceImage->adhesiveLimitTable);
	CCutsceneMgr::Initialize(pResourceImage->cutsceneDir);
	CPopulation::LoadPedGroups(pResourceImage->pedGroups);
	CParticleSystemMgr::Load(pResourceImage->particleSystemManager);
	CWaterLevel::Load(pResourceImage->waterLevelInst);
	CPlane::Init(pResourceImage->planeInst);


	gpTheZones = pResourceImage->theZones;
	pTimeCycle = pResourceImage->timecycle;
	gpWeaponTables = pResourceImage->weaponTables;
#ifdef LCS
	CHandlingDataMgr::Load(pResourceImage->handlingManagerInst);
	CFerry::Init(pResourceImage->ferryInst);
	CTrain::Init(pResourceImage->trainInst);
#else
	gpColourTable = pResourceImage->RGBTable;
#endif
#ifdef PSP
	CSampleManager::LoadSamples(pResourceImage->soundSamples);
#endif
}