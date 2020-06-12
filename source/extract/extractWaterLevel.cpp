#include "Extract.h"
#include "WaterLevel.h"
#include "Utils.h"
#include <fstream>

bool ExtractWaterLevel()
{
	/* Open waterpro.dat */
	std::ofstream f("waterpro.dat", std::ios::binary);
	if (!f)
	{
		ErrorBoxCannotCreateFile("waterpro.dat");
		return false;
	}

	/* Dump waterlevel */
#define WRITEPTR(a) f.write(reinterpret_cast<const char*>(a), 48 * sizeof(*(a)));
#define WRITEARRAY(a) f.write(reinterpret_cast<const char*>(a), sizeof(a))

	f.write(reinterpret_cast<const char*>(&CWaterLevel::mspInst->m_nNoOfWaterLevels), sizeof(int32));
	WRITEPTR(CWaterLevel::mspInst->m_aWaterZs);
	WRITEPTR(CWaterLevel::mspInst->m_aWaterRects);
	WRITEARRAY(CWaterLevel::mspInst->aWaterBlockList);
	WRITEARRAY(CWaterLevel::mspInst->aWaterFineBlockList);
	return true;
}