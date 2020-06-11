#include "Extract.h"
#include "SurfaceTable.h"
#include "Utils.h"
#include <fstream>

bool ExtractSurfaceTable()
{
	/* Surface names */
	static const char* const surfaces[]{ "Rubber", "Hard", "Road", "Loose", "Sand", "Wet" };

	/* Open surface.dat */
	std::ofstream f("surface.dat");
	if (!f)
	{
		ErrorBoxCannotCreateFile("surface.dat");
		return false;
	}
	f << ';' << ' ' << G3DTZ_MESSAGE << std::endl << ';';

	/* Print lines */
	int i;
	for (i = 0; i < 6; ++i) f << '\t' << surfaces[i];
	for (i = 0; i < 6; ++i)
	{
		f << std::endl << surfaces[i];
		for (int j = 0; j <= i; ++j)
			f << '\t' << Precision(CSurfaceTable::GetAdhesiveLimitTable()[i][j]);
	}

	return true;
}