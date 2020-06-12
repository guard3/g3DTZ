#include "Extract.h"
#include "PedType.h"
#include <fstream>
#include <sstream>

bool ExtractPedType()
{
	/*
	 * There are some ped types that have no threats or avoids.
	 * To make the output file pretty, we keep those 2 types separate
	 */
	std::stringstream ss1, ss2;

	/* A string stream pointer, because we need to decide to which string stream we're gonna print! */
	std::stringstream* pss;
	
	/* A lambda that parses a ped type flag and prints the appropriate flag names */
	auto printFlags = [&ss2](uint32 flag) {
		for (int i = 0; i < 26; ++i)
		{
			if (flag & 1)
				ss2 << ' ' << CPedType::GetFlagName(i);
			flag >>= 1;
		}
	};

	/* Print lines to string streams */
	int i = 0;
	while (CPedType* p = CPedType::GetPedType(i++))
	{
		if (p->IsValid())
		{
			/* Decide which string stream to print to */
			if (p->GetThreats())
			{
				ss2 << std::endl;
				pss = &ss2;
			}
			else
				pss = &ss1;

			(*pss)
				<< std::endl << p->GetFlagName()
				<< '\t' << p->GetWalkSpeed()
				<< '\t' << p->GetRunSpeed()
				<< '\t' << p->GetFastRunSpeed()
				<< '\t' << p->GetFleeDistance()
				<< '\t' << p->GetHeadingChange();

			if (p->GetThreats())
			{
				ss2 << std::endl << '\t' << "Threat";
				printFlags(p->GetThreats());
				ss2 << std::endl << '\t' << "Avoid";
				printFlags(p->GetAvoid());
			}
		}
	}

	/* Open ped.dat */
	std::ofstream f("ped.dat");
	if (!f)
	{
		ErrorBoxCannotCreateFile("ped.dat");
		return false;
	}

	/* Print everything */
	f << "# " << G3DTZ_MESSAGE << ss1.str() << ss2.str();

	return true;
}