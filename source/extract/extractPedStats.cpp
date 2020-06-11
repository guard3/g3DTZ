#include "Extract.h"
#include "Utils.h"
#include "PedStats.h"
#include <fstream>

bool ExtractPedStats()
{
	/* Open pedstats.dat */
	std::ofstream f("pedstats.dat");
	if (!f)
	{
		ErrorBoxCannotCreateFile("pedstats.dat");
		return false;
	}
	f << "# " << G3DTZ_MESSAGE << std::endl << '#';

	/* Write pedstats.dat lines */
	for (char c = 'A'; c < 'K'; ++c) f << '\t' << c;
	for (int i = 0; i < 42; ++i)
	{
		CPedStats* p = CPedStats::GetPedStats(i);
		f	<< std::endl << p->GetName()
			<< '\t'      << p->GetFleeDistance()
			<< '\t'      << p->GetHeadingChangeRate()
			<< '\t'      << p->GetFear()
			<< '\t'      << p->GetTemper()
			<< '\t'      << p->GetLawfulness()
			<< '\t'      << p->GetSexiness()
			<< '\t'      << p->GetAttackStrength()
			<< '\t'      << p->GetDefendWeakness()
			<< '\t'      << p->GetFlags();
	}

	return true;
}