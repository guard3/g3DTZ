#include "Utils.h"
#include "FileSystem.h"
#include "ResourceImage.h"
#include "Extract.h"
#include <iostream>

int wmain(int argc, const wchar** argv)
{
	/* An enum of error return codes */
	enum
	{
		ERROR_OK,
		ERROR_ARGS,
		ERROR_FILESYSTEM,
		ERROR_RESOURCEIMAGE,
		ERROR_EXTRACT
	};

	/* Check that only one argument is specified */
	if (argc != 2)
	{
		ErrorBox("Invalid number of arguments.\nSimply drag n' drop a GAME.DTZ or GAME.DAT to this executable.");
		return ERROR_ARGS;
	}

	/* Initialize filesystem */
	if (!CFileSystem::Initialize(argv[1]))
		return ERROR_FILESYSTEM;

	/* Load GAME.DTZ*/
	if (!LoadResourceImage())
		return ERROR_RESOURCEIMAGE;

#if 1
	std::cout << "Extracting..." << std::endl;
#define CHECK(a) if (!(a)) return ERROR_EXTRACT
	CHECK(ExtractAnimations());
	CHECK(ExtractIPLs());
	CHECK(ExtractModelInfoAndStuff());
	CHECK(ExtractObjectData());
	CHECK(ExtractFightMoves());
	CHECK(ExtractPedType());
	CHECK(ExtractPedStats());
	CHECK(ExtractPedGroups());
	CHECK(ExtractWeaponInfo());
	CHECK(ExtractTimeCycle());
	CHECK(ExtractSurfaceTable());
	CHECK(ExtractDIRs());
	CHECK(ExtractParticle());
	CHECK(ExtractWaterLevel());
	CHECK(ExtractZones());
	CHECK(ExtractPathData());
	std::cout << "All done!" << std::endl;
#else
	ExtractAnimations();
#endif

	return ERROR_OK;
}