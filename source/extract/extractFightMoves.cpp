#ifdef LCS
#include "Extract.h"
#include "Ped.h"
#include "Utils.h"
#include "AnimManager.h"
#include <fstream>

bool ExtractFightMoves()
{
	/* Open fistfite.dat */
	std::ofstream f("fistfite.dat");
	if (!f)
	{
		ErrorBoxCannotCreateFile("fistfite.dat");
		return false;
	}
	f << "# " << G3DTZ_MESSAGE << std::endl << '#';

	/* Print lines*/
	static const char* const names[]{
		"Null",
		"Idle",
		"Shuffle_f",
		"ComboA_1",
		"ComboA_2",
		"ComboA_3",
		"ComboB_1",
		"ComboB_2",
		"ComboB_3",
		"Attack1",
		"Attack2",
		"Attack3",
		"GroundKick",
		"HitFront",
		"HitBack",
		"HitRight",
		"HitLeft",
		"HitOnFloor",
		"HitBehind",
		"Idle2Norm"
	};

	for (char c = 'A'; c < 'K'; ++c) f << '\t' << c;
	for (int i = 0; i < 20; ++i)
	{
		auto& m = CPed::GetFightMove(i);
		f	<< std::endl << names[i]
			<< '\t' << m.GetStartFireTime()
			<< '\t' << m.GetEndFireTime()
			<< '\t' << m.GetComboFollowOnTime()
			<< '\t' << m.GetStrikeRadius()
			<< '\t' << m.GetExtendReachMultiplier()
			<< '\t' << m.GetHitLevel()
			<< '\t' << m.GetAnimationName()
			<< '\t' << m.GetDamage()
			<< '\t' << m.GetFlags();
	}
	f << std::endl << "ENDWEAPONDATA";
	return true;
}
#endif