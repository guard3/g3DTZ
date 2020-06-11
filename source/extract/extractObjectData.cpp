#include "Extract.h"
#include "ModelInfo.h"
#include "Utils.h"
#include <fstream>

/*
 * Here we iterate through each ModelInfo and extract object data
 * The reason this isn't done in ExtractModelInfoAndStuff() is because
 * I want everything sorted by ID
 */
bool ExtractObjectData()
{
	/* Open object.dat */
	std::ofstream f("object.dat");
	if (!f)
	{
		ErrorBoxCannotCreateFile("object.dat");
		return false;
	}
	f << "; " << G3DTZ_MESSAGE << std::endl << ';';

	/* Print lines */
	for (char i = 'A'; i < 'L'; ++i) f << '\t' << i;
	f << std::endl;
	for (uint32 i = 0; i < CModelInfo::GetNumModelInfos(); ++i)
	{
		if (CBaseModelInfo* mi = CModelInfo::GetModelInfo(i))
		{
			if (CObjectInfo* obj = mi->GetObjectInfo())
			{
				f	<< mi->GetModelName() << ",\t"
					<< obj->GetMass() << ",\t"
					<< obj->GetTurnMass() << ",\t"
					<< obj->GetAirResistance() << ",\t"
					<< obj->GetElasticity() << ",\t"
					<< obj->GetBuoyancy() << ",\t"
					<< obj->GetUprootLimit() << ",\t"
					<< obj->GetCollisionDamageMultiplier() << ",\t"
					<< obj->GetCollisionDamageEffect() << ",\t"
					<< obj->GetSpecialCollisionResponseCases() << ",\t"
					<< obj->GetCameraToAvoidThisObject()
#ifdef VCS
					<< ",\t" << obj->GetUnk1()
					<< ",\t" << obj->GetUnk2()
#endif
					<< std::endl;
			}
		}
	}

	f << "* ;end of file"; // Ewwwwwwwwww...
	return true;
}