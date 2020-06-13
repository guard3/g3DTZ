#include "Extract.h"
#include "Zones.h"
#include "Utils.h"
#include "FileSystem.h"
#include <fstream>

bool ExtractZones()
{
	/* A lambda that extracts a zone array to a file */
	auto extract = [](const char* filename, CZone* z, int num) {
		/* Open file */
		std::ofstream f(filename);
		if (!f)
		{
			ErrorBoxCannotCreateFile(filename);
			return false;
		}
		f << "# " << G3DTZ_MESSAGE << std::endl << "zone";

		/* Print lines */
		for (int i = 1; i < num; ++i)
		{
			/* We skip the first zone because it's a hardcoded one */
			f	<< std::endl << z[i].name
				<< '\t'      << z[i].type
				<< '\t'      << PrecisionAny(z[i].min.x)
				<< '\t'      << PrecisionAny(z[i].min.y)
				<< '\t'      << PrecisionAny(z[i].min.z)
				<< '\t'      << PrecisionAny(z[i].max.x)
				<< '\t'      << PrecisionAny(z[i].max.y)
				<< '\t'      << PrecisionAny(z[i].max.z)
				<< '\t'      << z[i].level;
		}
		f << std::endl << "end";

		return true;
	};
	
#define CHECK(a) if (!(a)) return false;

	/* Create a directory for zones */
	CHECK(CFileSystem::CreateAndChangeFolder("zones"));

	/* Extract files */
	CHECK(extract("info.zon",  gpTheZones->InfoZoneArray,       gpTheZones->TotalNumberOfInfoZones      ));
	CHECK(extract("map.zon",   gpTheZones->MapZoneArray,        gpTheZones->TotalNumberOfMapZones       ));
	CHECK(extract("navig.zon", gpTheZones->NavigationZoneArray, gpTheZones->TotalNumberOfNavigationZones));

	/* Reset directory */
	CFileSystem::ResetFolder();

	return true;
}