#include "Extract.h"
#include "ModelInfo.h"
#include "ColStore.h"
#include "Utils.h"
#include "HandlingMgr.h"
#include "FileSystem.h"
#include "SampMan.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

bool ExtractModelInfoAndStuff()
{
#ifdef VCS
	/* Prepare pedcols.dat for VCS */
	std::ofstream pedcolsFile("pedcols.dat");
	{
		if (!pedcolsFile)
		{
			ErrorBoxCannotCreateFile("pedcols.dat");
			return false;
		}
		pedcolsFile << "# " << G3DTZ_MESSAGE << std::endl << "col" << std::endl;
		for (int i = 0; i < 128; ++i)
		{
			RslRGB& c = gpColourTable[0][i];
			pedcolsFile
				<< static_cast<int>(c.r) << '\t'
				<< static_cast<int>(c.g) << '\t'
				<< static_cast<int>(c.b) << '\t'
				<< "# " << i << std::endl;
		}
	}
	pedcolsFile << "end" << std::endl << "ped" << std::endl;
#else
	/* Otherwise, set a dummy variable that won't be used when dealing with LCS */
	void* pedcolsFile;
#endif

	/*
	 * A vector that stores the vehicle model infos we encounter
	 * I will be used later for:
	 *     - carcols (we need to sort them alphabetically by modelname)
	 *     - handling (in VCS)
	 */
	std::vector<CVehicleModelInfo*> vehicleModelInfos;

	/* Since ide files are expected to be many, create their own folder */
	if (!CFileSystem::CreateAndChangeFolder("ide"))
	{
		ErrorBoxCannotCreateFolder("ide");
		return false;
	}

	/* A lambda that extracts modelinfos in a range of ids */
	auto ExtractShit = [&vehicleModelInfos, &pedcolsFile](const char* name, int first, int last) -> bool
	{
		/* String stream array */
		enum
		{
			STREAM_PEDS,
			STREAM_CARS,
			STREAM_OBJS,
			STREAM_WEAP,
			STREAM_HIER,
			STREAM_TOBJ,
			STREAM_2DFX,
			COUNT_STREAMS
		};
		static std::stringstream sstreams[COUNT_STREAMS];
		static const char* const idents[]{ "peds", "cars", "objs", "weap", "hier", "tobj", "2dfx" };

		/* The holy loop */
		for (int i = first; i <= last; ++i)
		{
			if (auto mi = CModelInfo::GetModelInfo(i))
			{
				/* First, get 2dfx entries for current modelinfo */
				auto effects = mi->Get2dEffects();
				for (int j = 0; j < mi->GetNum2dEffects(); ++j)
				{
					auto& fx = effects[j];
					auto& s = sstreams[STREAM_2DFX];
					s	<< i << ", "
						<< fx.position.x << ", "
						<< fx.position.y << ", "
						<< fx.position.z << ", "
						<< static_cast<int>(fx.colour.r) << ", "
						<< static_cast<int>(fx.colour.g) << ", "
						<< static_cast<int>(fx.colour.b) << ", "
						<< static_cast<int>(fx.colour.a) << ", "
						<< static_cast<int>(fx.type) << ", ";
					switch (fx.type)
					{
					case EFFECT_LIGHT:
						s	<< '"' << fx.light.corona->name << '"' << ", "
							<< '"' << fx.light.shadow->name << '"' << ", "
							<< fx.light.distance << ", "
							<< fx.light.outerRange << ", "
							<< fx.light.size << ", "
							<< fx.light.innerRange << ", "
							<< static_cast<int>(fx.light.shadowIntensity) << ", "
							<< static_cast<int>(fx.light.flash) << ", "
							<< static_cast<int>(fx.light.wet) << ", "
							<< static_cast<int>(fx.light.flare) << ", "
							<< static_cast<int>(fx.light.flags);
						break;
					case EFFECT_PARTICLE:
						s	<< fx.particle.particleType << ", "
							<< fx.particle.strength.x << ", "
							<< fx.particle.strength.y << ", "
							<< fx.particle.strength.z << ", "
							<< fx.particle.scale;
						break;
					case EFFECT_ATTRACTOR:
						s	<< static_cast<int>(fx.attractor.subtype) << ", "
							<< fx.attractor.direction.x << ", "
							<< fx.attractor.direction.y << ", "
							<< fx.attractor.direction.z << ", "
							<< static_cast<int>(fx.attractor.probability);
						break;
					default:
						s	<< static_cast<int>(fx.pedbehaviour.behaviour) << ", "
							<< fx.pedbehaviour.direction.x << ", "
							<< fx.pedbehaviour.direction.y << ", "
							<< fx.pedbehaviour.direction.z << ", "
							<< fx.pedbehaviour.rotation.x << ", "
							<< fx.pedbehaviour.rotation.y << ", "
							<< fx.pedbehaviour.rotation.z;
					}
					s << std::endl;
				}

				/* Find which stringstream to print to depending on the modelinfo type */
				auto miType = mi->GetType();
				std::stringstream* ps;
				switch (miType)
				{
				case MITYPE_SIMPLE:
					ps = &sstreams[STREAM_OBJS];
					break;
				case MITYPE_TIME:
					ps = &sstreams[STREAM_TOBJ];
					break;
				case MITYPE_WEAPON:
					ps = &sstreams[STREAM_WEAP];
					break;
				case MITYPE_CLUMP:
					ps = &sstreams[STREAM_HIER];
					break;
				case MITYPE_VEHICLE:
					ps = &sstreams[STREAM_CARS];
					break;
				default:
					ps = &sstreams[STREAM_PEDS];
				}
				std::stringstream& s = *ps;

				/* Print IDE line and some colour stuff */
				s	<< i << ", "
					<< mi->GetModelName() << ", "
					<< mi->GetTexListName();
				switch (miType)
				{
				case MITYPE_CLUMP:
					break;
				case MITYPE_VEHICLE:
				{
					CVehicleModelInfo* m = reinterpret_cast<CVehicleModelInfo*>(mi);
					vehicleModelInfos.push_back(m);

					s	<< ", " << m->GetVehicleTypeName()
						<< ", " << m->GetHandlingName()
						<< ", " << m->GetGameName()
						<< ", " << m->GetAnimBlockName()
						<< ", " << m->GetVehicleClass()
						<< ", " << m->GetFrequency()
						<< ", " << m->GetLevel()
						<< ", " << std::hex << m->GetCompRules() << std::dec << ", ";
					switch (m->GetVehicleType())
					{
					case VEHICLE_TYPE_CAR:
						s << m->GetWheelId() << ", ";
					wheel_scale_label:
						s << m->GetWheelScale() << ", ";
#ifdef VCS
						s << m->GetWheelScaleRear() << ", ";
#endif
						goto normals_label;
					case VEHICLE_TYPE_BIKE:
#ifdef VCS
					case VEHICLE_TYPE_BMX:
					case VEHICLE_TYPE_QUAD:
#endif
						s << m->GetBikeSteerAngle() << ", ";
						goto wheel_scale_label;
					case VEHICLE_TYPE_PLANE:
						s << m->GetPlaneLodId() << ", ";
						goto ignored_label;
					default:
						s << "0, ";
					ignored_label:
						s << "0, ";
#ifdef VCS
						s << "0, ";
#endif
					normals_label:
						s << m->GetNormalSplay();
					}
					break;
				}
				case MITYPE_PED:
				{
					auto& m = *reinterpret_cast<CPedModelInfo*>(mi);
#ifdef VCS
					/* Print pedcols.dat lines */
					if (m.GetNumColours())
					{
						pedcolsFile << m.GetModelName();
						for (int n = 0; n < m.GetNumColours(); ++n)
						{
							auto& c = m.GetColours();
							pedcolsFile
								<< ", " << static_cast<int>(c[n][0])
								<< ','  << static_cast<int>(c[n][1])
								<< ','  << static_cast<int>(c[n][2])
								<< ','  << static_cast<int>(c[n][3]);
						}
						pedcolsFile << std::endl;
					}
#endif
					s	<< ", " << m.GetPedType()
						<< ", " << m.GetPedStatType()
						<< ", " << m.GetAnimGroup()
						<< ", " << std::hex << m.GetCarsCanDriveMask() << std::dec
						<< ", " << m.GetAnimBlock()
						<< ", " << m.GetRadio1()
						<< ", " << m.GetRadio2();
					break;
				}
				case MITYPE_WEAPON:
					s << ", " << reinterpret_cast<CWeaponModelInfo*>(mi)->GetAnimBlockName();
				default:
				{
					auto& m = *reinterpret_cast<CSimpleModelInfo*>(mi);
					s << ", " << m.GetNumObjects();
					for (int n = 0; n < m.GetNumObjects(); ++n)
						s << ", " << m.GetLodDistance(n);
					s << ", " << m.GetFlags();
					if (miType == MITYPE_TIME)
					{
						auto& t = *reinterpret_cast<CTimeModelInfo*>(mi);
						s << ", " << t.GetTimeOn() << ", " << t.GetTimeOff();
					}
				}
				}
				s << std::endl;
			}
		}

		/* Append IDE extension to name */
		char filename[24]; // 20 + 4 for the extension
		int len;
		for (len = 0; name[len]; ++len)
			filename[len] = name[len];
		strcpy(filename + len, ".ide");

		/* Open output ide file */
		std::ofstream f(filename);
		if (!filename)
		{
			ErrorBoxCannotCreateFile(filename);
			return false;
		}
		f << "# " << G3DTZ_MESSAGE << std::endl;

		/* Print string streams to output file */
		for (int i = 0; i < COUNT_STREAMS; ++i)
		{
			if (!sstreams[i].str().empty())
			{
				f << idents[i] << std::endl << sstreams[i].str() << "end" << std::endl;
				sstreams[i].str(std::string());
				sstreams[i].clear();
			}
		}

		return true;
	};

	/*
	 * First, we want to extract the basic ide definitions for buildings and such
	 * Typically, there's a .col file for each .ide in the source files,
	 * so we can use CColStore as a guide to split all those IDEs as accurately as possible!
	 */
	int genericLastIndex = CColStore::GetSlot(0)->GetFirstIndex(); // INT_MAX
	for (int i = 1; i < CColStore::GetSize(); ++i)
	{
		/* --^^^^^-- we skip the first collision, which is "generic" and its index ranges are off */
		if (auto c = CColStore::GetSlot(i))
		{
			if (c->GetFirstIndex() < genericLastIndex)
				genericLastIndex = c->GetFirstIndex();

			if (!ExtractShit(c->GetName(), c->GetFirstIndex(), c->GetLastIndex()))
				return false;
		}
	}
	--genericLastIndex;
#ifdef LCS
	constexpr int defaultLastIndex = 299;
#else
	constexpr int defaultLastIndex = 395;
#endif
	if (!ExtractShit("default", 0, defaultLastIndex))
		return false;
	if (!ExtractShit("generic", defaultLastIndex + 1, genericLastIndex))
		return false;

	/* We're done writing ide files, so we reset the working directory */
	CFileSystem::ResetFolder();

#ifdef VCS
	/* We're done writing to pedcols.dat, so we can close the file now */
	pedcolsFile << "end";
	pedcolsFile.close();
#endif

	/* Open handling.cfg for writing */
	std::ofstream handlingFile("handling.cfg");
	if (!handlingFile)
	{
		ErrorBoxCannotCreateFile("handling.cfg");
		return false;
	}
	handlingFile << ';' << ' ' << G3DTZ_MESSAGE << std::endl << ';';

	/* Print out data */
	char c;
	for (c = 'A'; c < 'E'; ++c) handlingFile << '\t' << c;
	for (c = 'F'; c < 'W'; ++c) handlingFile << '\t' << c;
	for (c = 'a'; c < 'h'; ++c) handlingFile << '\t' << c;
	for (c = 'a'; c < 'd'; ++c) handlingFile << '\t' << 'a' << c;
#ifdef VCS
	for (c = 'f'; c < 'j'; ++c) handlingFile << '\t' << 'a' << c;
	handlingFile << std::endl;

	/* Prepare handling stringstreams for non-car vehicles */
	enum { STREAM_BOAT, STREAM_BIKE, STREAM_FLYING, COUNT_STREAMS };
	std::stringstream sstreams[COUNT_STREAMS];
	sstreams[STREAM_BOAT] << ';';
	sstreams[STREAM_BIKE] << ';';
	sstreams[STREAM_FLYING] << ';';
	for (c = 'A'; c < 'P'; ++c) sstreams[STREAM_BOAT] << '\t' << c;
	for (c = 'A'; c < 'Q'; ++c) sstreams[STREAM_BIKE] << '\t' << c;
	for (c = 'A'; c < 'W'; ++c) sstreams[STREAM_FLYING] << '\t' << c;
	sstreams[STREAM_BOAT] << std::endl;
	sstreams[STREAM_BIKE] << std::endl;
	sstreams[STREAM_FLYING] << std::endl;

	for (auto& m : vehicleModelInfos)
	{
		if (CHandlingData* p = m->GetHandlingData())
		{
			CHandlingData& h = *p;
			handlingFile << m->GetModelName()
#else
	for (c = 'g'; c < 'j'; ++c) handlingFile << '\t' << 'a' << c;
	handlingFile << std::endl;
	for (int i = 0; i < CHandlingDataMgr::NUM_HANDLING_DATA; ++i)
	{
		CHandlingData& h = CHandlingDataMgr::GetHandlingData(i);
		handlingFile << h.GetHandlingName()
#endif
			<< '\t' << h.GetMass()
			<< '\t' << h.GetTurnMass()
			<< '\t' << h.GetDragMult()
			<< '\t' << h.GetCentreOfMassX()
			<< '\t' << h.GetCentreOfMassY()
			<< '\t' << h.GetCentreOfMassZ()
			<< '\t' << h.GetPercentSubmerged()
			<< '\t' << h.GetTractionMultiplier()
			<< '\t' << h.GetTractionLoss()
			<< '\t' << h.GetTractionBias()
			<< '\t' << h.transmission.GetNumberOfGears()
			<< '\t' << h.transmission.GetMaxVelocity()
			<< '\t' << h.transmission.GetEngineAcceleration()
			<< '\t' << h.transmission.GetEngineInertia()
			<< '\t' << h.transmission.GetDriveType()
			<< '\t' << h.transmission.GetEngineType()
			<< '\t' << h.GetBrakeDeceleration()
			<< '\t' << h.GetBrakeBias()
			<< '\t' << h.GetABS()
			<< '\t' << h.GetSteeringLock()
			<< '\t' << h.GetSuspensionForceLevel()
			<< '\t' << h.GetSuspensionDampingLevel()
			<< '\t' << h.GetSuspensionHighSpdComDamp()
			<< '\t' << h.GetSuspensionUpperLimit()
			<< '\t' << h.GetSuspensionLowerLimit()
			<< '\t' << h.GetSuspensionBias()
			<< '\t' << h.GetSuspensionAntiDiveMultiplier()
			<< '\t' << h.GetSeatOffsetDistance()
			<< '\t' << h.GetCollisionDamageMultiplier()
			<< '\t' << h.GetMonetaryValue()
			<< '\t' << h.GetModelFlags()
			<< '\t' << h.GetFrontLights()
			<< '\t' << h.GetRearLights()
			<< std::endl;
#ifdef VCS
		}
		if (CHandlingBoat* p = m->GetHandlingBoat())
		{
			CHandlingBoat& h = *p;
			sstreams[STREAM_BOAT] << '%' << '\t' << m->GetModelName()
#else
	}
	handlingFile << ';' << std::endl << ';';
	for (c = 'A'; c < 'P'; ++c) handlingFile << '\t' << c;
	handlingFile << std::endl;
	for (int i = 0; i < CHandlingDataMgr::NUM_HANDLING_BOAT; ++i)
	{
		CHandlingBoat& h = CHandlingDataMgr::GetHandlingBoat(i);
		handlingFile << '%' << '\t' << h.GetHandlingName()
#endif
			<< '\t' << h.GetThrustY()
			<< '\t' << h.GetThrustZ()
			<< '\t' << h.GetThrustAppZ()
			<< '\t' << h.GetAqPlaneForce()
			<< '\t' << h.GetAqPlaneLimit()
			<< '\t' << h.GetAqPlaneOffset()
			<< '\t' << h.GetWaveAudioMult()
			<< '\t' << h.GetMoveResX()
			<< '\t' << h.GetMoveResY()
			<< '\t' << h.GetMoveResZ()
			<< '\t' << h.GetTurnResX()
			<< '\t' << h.GetTurnResY()
			<< '\t' << h.GetTurnResZ()
			<< '\t' << h.GetBehindCamHeight()
			<< std::endl;
#ifdef VCS
		}
		if (CHandlingBike* p = m->GetHandlingBike())
		{
			CHandlingBike& h = *p;
			sstreams[STREAM_BIKE] << '!' << '\t' << m->GetModelName()
#else
	}
	handlingFile << ';' << std::endl << ';';
	for (c = 'A'; c < 'Q'; ++c) handlingFile << '\t' << c;
	handlingFile << std::endl;
	for (int i = 0; i < CHandlingDataMgr::NUM_HANDLING_BIKE; ++i)
	{
		CHandlingBike& h = CHandlingDataMgr::GetHandlingBike(i);
		handlingFile << '!' << '\t' << h.GetHandlingName()
#endif
			<< '\t' << h.GetLeanFwdCOM()
			<< '\t' << h.GetLeanFwdForce()
			<< '\t' << h.GetLeanBakCOM()
			<< '\t' << h.GetLeanBackForce()
			<< '\t' << h.GetMaxLean()
			<< '\t' << h.GetFullAnimLean()
			<< '\t' << h.GetDesLean()
			<< '\t' << h.GetSpeedSteer()
			<< '\t' << h.GetSlipSteer()
			<< '\t' << h.GetNoPlayerCOMz()
			<< '\t' << h.GetWheelieAng()
			<< '\t' << h.GetStoppieAng()
			<< '\t' << h.GetWheelieSteer()
			<< '\t' << h.GetWheelieStabMult()
			<< '\t' << h.GetStoppieStabMult()
			<< std::endl;
#ifdef VCS
		}
		if (CHandlingFlying* p = m->GetHandlingFlying())
		{
			CHandlingFlying& h = *p;
			sstreams[STREAM_FLYING] << '$' << '\t' << m->GetModelName()
#else
	}
	handlingFile << ';' << std::endl << ';';
	for (c = 'A'; c < 'W'; ++c) handlingFile << '\t' << c;
	handlingFile << std::endl;
	for (int i = 0; i < CHandlingDataMgr::NUM_HANDLING_FLYING; ++i)
	{
		CHandlingFlying& h = CHandlingDataMgr::GetHandlingFlying(i);
		handlingFile << '$' << '\t' << h.GetHandlingName()
#endif
			<< '\t' << h.GetThrust()
			<< '\t' << h.GetThrustFallOff()
			<< '\t' << h.GetYaw()
			<< '\t' << h.GetYawStab()
			<< '\t' << h.GetSideSlip()
			<< '\t' << h.GetRoll()
			<< '\t' << h.GetRollStab()
			<< '\t' << h.GetPitch()
			<< '\t' << h.GetPitchStab()
			<< '\t' << h.GetFormLift()
			<< '\t' << h.GetAttackLift()
			<< '\t' << h.GetMoveRes()
			<< '\t' << h.GetTurnResX()
			<< '\t' << h.GetTurnResY()
			<< '\t' << h.GetTurnResZ()
			<< '\t' << h.GetSpeedResX()
			<< '\t' << h.GetSpeedResY()
			<< '\t' << h.GetSpeedResZ()
			<< std::endl;
#ifdef LCS
	}
#else
		}
	}
	
	/* Print the contents of the stringstreams to file */
	for (auto& ss : sstreams)
	{
		handlingFile << ';' << std::endl;
		handlingFile << ss.str();
		ss.str(std::string());
	}
#endif

	/* Close handling.cfg */
	handlingFile << ';' << std::endl;
	handlingFile << ';' << "the end";
	handlingFile.close();

	/* Sort the vehicle modelinfo vector by model name alphabetically for carcols */
	std::sort(
		vehicleModelInfos.begin(),
		vehicleModelInfos.end(),
		[](CVehicleModelInfo* v1, CVehicleModelInfo* v2) {
#ifdef LCS
#define compare _stricmp
#else
#define compare strcmp
#endif
			return compare(v1->GetModelName(), v2->GetModelName()) < 0;
		}
	);

	/* Open carcols.dat */
	std::ofstream carcolsFile("carcols.dat");
	if (!carcolsFile)
	{
		ErrorBoxCannotCreateFile("carcols.dat");
		return false;
	}
	carcolsFile << "# " << G3DTZ_MESSAGE << std::endl << "col" << std::endl;

	/* Print colours to carcols.dat */
#ifdef LCS
	for (int i = 0; i < 256; ++i)
	{
		if (RslRGBA& c = *CVehicleModelInfo::GetColourFromTable(i))
#else
	for (int i = 0; i < 128; ++i)
	{
		if (RslRGB& c = gpColourTable[1][i])
#endif
		{
			carcolsFile
				<< static_cast<int>(c.r) << '\t'
				<< static_cast<int>(c.g) << '\t'
				<< static_cast<int>(c.b) << '\t'
				<< "# " << i << std::endl;
		}
	}
	carcolsFile << "end" << std::endl << "car" << std::endl;

	/* Print vehicle lines to carcols.dat */
	for (auto& mi : vehicleModelInfos)
	{
		if (mi->GetNumColours())
		{
			carcolsFile << mi->GetModelName();
			for (int i = 0; i < mi->GetNumColours(); ++i)
			{
#ifdef LCS
				carcolsFile << ", " << mi->GetColour1(i) << ',' << mi->GetColour2(i);
#else
				auto c = mi->GetColours();
				carcolsFile << ", " << static_cast<int>(c[i][0]) << ',' << static_cast<int>(c[i][1]);
#endif
			}
			carcolsFile << std::endl;
		}
	}
	carcolsFile << "end";
	carcolsFile.close();

#ifdef PSP
	/*
	 * If we're on PSP, extract SFX.SDT stuff while we're at it
	 * First create a new sfx folder
	 */
	if (!CFileSystem::CreateAndChangeFolder("sfx"))
	{
		ErrorBoxCannotCreateFolder("sfx");
		return false;
	}

	/* Extract sfx sets */
	int sfxFileCounter = 0;
	char f_name[] = "SET\0\0SFX\0_PSP.SDT\0";
	std::ofstream f;
	for (int i = 0; i < CSampleManager::TOTAL_AUDIO_SAMPLES; ++i)
	{
		tSample& sample = CSampleManager::m_aSamples[i];
		if (sample.nOffset == 0)
		{
			/*
			 * If offset of the sample is 0, then we're looking into a "new" file,
			 * so we need to open a new file at the proper folder
			 * So, first, we create the folder for the current set
			 */
			if (sfxFileCounter % 10 == 0)
			{
				f_name[3] = '0' + sfxFileCounter / 10;
				f_name[4] = '\0';
				if (!CFileSystem::CreateFolder(f_name))
				{
					ErrorBoxCannotCreateFolder(f_name);
					return false;
				}
			}
			
			/* ...then open the file */
			if (sfxFileCounter == 10)
				for (int j = 17; j > 9; --j)
					f_name[j] = f_name[j - 1];
			f_name[4] = '\\';
			if (f_name[3] == '0')
				f_name[8] = '0' + sfxFileCounter % 10;
			else
			{
				f_name[8] = f_name[3];
				f_name[9] = '0' + sfxFileCounter % 10;
			}
			f.close();
			f.open(f_name, std::ios::binary);
			if (!f)
			{
				ErrorBoxCannotCreateFile(f_name);
				return false;
			}

			++sfxFileCounter;
		}
		f.write(reinterpret_cast<const char*>(&sample), sizeof(sample));
	}
	f.close();

	CFileSystem::ResetFolder();
#endif

	return true;
}