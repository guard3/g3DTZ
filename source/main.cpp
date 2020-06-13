#include "Utils.h"
#include "FileSystem.h"
#include "ResourceImage.h"
#include "Extract.h"

int wmain(int argc, const wchar** argv)
{
	/* An enum of error return codes */
	enum
	{
		ERROR_OK,
		ERROR_ARGS,
		ERROR_FILESYSTEM,
		ERROR_RESOURCEIMAGE
	};

	/* Check that only one argument is specified */
	if (argc != 2)
	{
		/* tba */
		ErrorBox("");
		return ERROR_ARGS;
	}

	/* Initialize filesystem */
	if (!CFileSystem::Initialize(argv[1]))
		return ERROR_FILESYSTEM;

	/* Load GAME.DTZ*/
	if (!LoadResourceImage())
		return ERROR_RESOURCEIMAGE;

#if 1
	//ExtractAnimations();
	ExtractIPLs();
	ExtractModelInfoAndStuff();
	ExtractObjectData();
	ExtractFightMoves();
	ExtractPedType();
	ExtractPedStats();
	ExtractPedGroups();
	ExtractWeaponInfo();
	ExtractTimeCycle();
	ExtractSurfaceTable();
	ExtractDIRs();
	ExtractParticle();
	ExtractWaterLevel();
	ExtractZones();
	ExtractPathData();
#else
	
#endif

	return ERROR_OK;
}