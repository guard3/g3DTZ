#include <zlib.h>
#include "Win32.h"
#include "ResourceImage.h"
#include "RelocatableChunk.h"
#include "Utils.h"
#include "FileSystem.h"
#include <iostream>

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

/* The buffer were GAME.DAT is stored, freed automatically */
void* gResourceMem = nullptr;
class cResourceMemAutoClose final
{
public:
	~cResourceMemAutoClose() { free(gResourceMem); }
} __autoclose;

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

bool LoadResourceImage()
{
	/* Main variables */
	HANDLE hFile = INVALID_HANDLE_VALUE; // A file handle used for reading and writing files
	void* source = nullptr;              // The buffer that holds the input file's contents

	/* A lambda that handles all the reading and decompressing stuff */
	auto _loadResourceImage = [&hFile, &source]() {
		/* Lambdas for error messages */
		auto ErrorBoxInputFile = [](const char* str) {
			ErrorBox(L"%ls\n%s", CFileSystem::GetInputFilePath(), str);
		};
		auto ErrorBoxInputFileDecompression = [](const char* str) {
			ErrorBox(L"%ls\n%s\n%s", CFileSystem::GetInputFilePath(), "Cannot decompress file.", str);
		};

		/* Open file */
		hFile = CreateFileW(
			CFileSystem::GetInputFilePath(),                   // Filename
			GENERIC_READ,                                      // Desired access
			0,                                                 // Share mode
			NULL,                                              // Security attributes
			OPEN_EXISTING,                                     // Creation disposition
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, // Flags and attributes
			NULL                                               // Template file
		);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			ErrorBoxInputFile("Cannot open file.");
			return false;
		}

		/* Get file size */
		LARGE_INTEGER large_size;
		if (!GetFileSizeEx(hFile, &large_size))
		{
			ErrorBoxInputFile("Cannot determine file size.");
			return false;
		}
		if (large_size.HighPart != 0)
		{
			ErrorBoxInputFile("File too arge to read.");
			return false;
		}

		/* Load file */
		DWORD sourceLen;
		if (!(source = malloc(large_size.LowPart)))
		{
		label_load_file:
			ErrorBoxInputFile("Cannot load file.");
			return false;
		}
		if (!ReadFile(hFile, source, large_size.LowPart, &sourceLen, NULL))
			goto label_load_file;
		CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;

		/* If loaded file ident is 'GTAG', then we have loaded a GAME.DAT */
		constexpr uint32 GTAGIDENT = 0x47544147;
		if (reinterpret_cast<cRelocChunk*>(source)->Ident == GTAGIDENT)
		{
			gResourceMem = source;
			return true;
		}

		/* Otherwise, we decompress GAME.DTZ */
		uLongf resourceSize = 0x650000;
		if (!(gResourceMem = malloc(0x650000)))
		{
			ErrorBoxInputFileDecompression("Memory allocation failed.");
			return false;
		}
		int result = uncompress(
			reinterpret_cast<Bytef*>(gResourceMem), // Destination buffer
			&resourceSize,                          // The size of the destination buffer; the size of decompressed data on return
			reinterpret_cast<const Bytef*>(source), // Source buffer
			sourceLen                               // Source buffer size
		);
		free(source);
		source = nullptr;
		switch (result)
		{
		case Z_MEM_ERROR:
			ErrorBoxInputFileDecompression("Out of memory.");
			return false;
		case Z_BUF_ERROR:
			ErrorBoxInputFileDecompression("File too large.");
			return false;
		case Z_DATA_ERROR:
			ErrorBoxInputFileDecompression("Invalid data.");
			return false;
		}

		/* Get output GAME.DAT file name */
		auto len = CFileSystem::GetInputFileNameNoExtensionLength();
		wchar* outputname = new wchar[len + 5];
		wcscpy(outputname, CFileSystem::GetInputFileNameNoExtension());
		wcscpy(outputname + len, L".dat");

		auto ErrorBoxOutput = [&outputname](const char* str) {
			ErrorBox(L"%ls\n%s", outputname, str);
		};

		/* Save GAME.DAT to disk */
		hFile = CreateFileW(
			outputname,                                        // Filename
			GENERIC_WRITE,                                     // Desired acces
			0,                                                 // Share mode
			NULL,                                              // Security attributes
			CREATE_ALWAYS,                                     // Creation disposition
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, // Flags and attributes
			NULL                                               // Template file
		);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			ErrorBoxOutput("Cannot create file.");
			delete[] outputname;
			return false;
		}
		result = WriteFile(hFile, gResourceMem, resourceSize, &sourceLen, NULL);
		CloseHandle(hFile);
		if (!result)
		{
			hFile = INVALID_HANDLE_VALUE;
			ErrorBoxOutput("Cannot write to file.");
			delete[] outputname;
			return false;
		}
		delete[] outputname;
		return true;
	};

	/* Run */
	if (!_loadResourceImage())
	{
		if (hFile != INVALID_HANDLE_VALUE)
			CloseHandle(hFile);
		gResourceMem = source; // Whether source is a valid pointer or nullptr, it'll be freed automatically
		return false;
	}

	/* Now that GAME.DTZ is fully loaded, create a ResourceImage reference */
	cRelocChunk& chunk = reinterpret_cast<cRelocChunk*>(gResourceMem)->Fixup();
	void* result = realloc(gResourceMem, chunk.Shrink ? chunk.DataSize : chunk.FileSize);
	if (!result)
	{
		ErrorBox("Reallocation error.");
		return false;
	}
	sResourceImage* pResourceImage = reinterpret_cast<sResourceImage*>(chunk.DataPtr);

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

	auto fileaddr = [](void* ptr)
	{
		return (uint32)ptr - (uint32)gResourceMem;
	};

	std::cout << std::hex << fileaddr(pResourceImage->planeInst) << std::dec << std::endl;

	return true;
}