#include "Extract.h"
#include "Population.h"
#include "ModelInfo.h"
#include "Utils.h"
#include <fstream>

bool ExtractPedGroups()
{
	/* Open pedgrp.dat */
	std::ofstream f("pedgrp.dat");
	if (!f)
	{
		ErrorBoxCannotCreateFile("pedgrp.dat");
		return false;
	}
	f << "# " << G3DTZ_MESSAGE;

	/* Print lines */
	for (int i = 0; i < CPopulation::NUM_PEDGROUPS; ++i)
	{
		f << std::endl << CModelInfo::GetModelInfo(CPopulation::ms_pPedGroups[i][0])->GetModelName();
		for (int j = 1; j < 16; ++j)
			f << ',' << '\t' << CModelInfo::GetModelInfo(CPopulation::ms_pPedGroups[i][j])->GetModelName();
	}
	return true;
}