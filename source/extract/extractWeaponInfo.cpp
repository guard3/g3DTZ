#include "Extract.h"
#include "WeaponInfo.h"
#include <fstream>
bool ExtractWeaponInfo()
{
	/* Weapon names */
	static const char* const weapon_names[CWeaponInfo::TOTALWEAPONS] {
		"Unarmed",
		"BrassKnuckle",
		"ScrewDriver",
		"GolfClub",
		"NightStick",
		"Knife",
		"BaseballBat",
		"Hammer",
		"Cleaver",
		"Machete",
		"Katana",
		"Chainsaw",
		"Grenade",
		"DetonateGrenade",
#ifdef VCS
		"LandMine",
		"SeaMine",
#endif
		"TearGas",
		"Molotov",
		"Rocket",
		"Colt45",
		"Python",
		"Shotgun",
		"Spas12Shotgun",
		"StubbyShotgun",
		"Tec9",
		"Uzi",
		"SilencedIngram",
		"Mp5",
		"m4",
		"Ruger",
		"SniperRifle",
		"LaserScope",
		"RocketLauncher",
		"FlameThrower",
		"M60",
		"Minigun",
		"Detonator",
		"HeliCannon",
		"Camera",
#ifdef VCS
		"Binoculars"
#endif
	};

	/* A lambda that extracts an array of CWeaponInfo to file */
	auto extractWeaponInfo = [](CWeaponInfo* weaponInfos, const char* filename) -> bool {
		/* Open data file */
		std::ofstream f(filename);
		if (!f)
		{
			ErrorBoxCannotCreateFile(filename);
			return false;
		}
		f << "# " << G3DTZ_MESSAGE << std::endl << '#';

		/* Print lines */
		char c;
		for (c = 'A'; c < 'O'; ++c) f << '\t' << c;
		f << '\t' << 'P';
		for (c = 'R'; c <= 'Z'; ++c) f << '\t' << c;
		f << '\t' << 'a' << '\t' << 'b' << std::endl;
		for (int i = 0; i < CWeaponInfo::TOTALWEAPONS; ++i)
		{
			CWeaponInfo& w = weaponInfos[i];
			f	<< weapon_names[i] << '\t'
				<< w.GetFireType() << '\t'
				<< w.GetRange() << '\t'
				<< w.GetFiringRate() << '\t'
				<< w.GetReload() << '\t'
				<< w.GetAmountOfAmmunition() << '\t'
				<< w.GetDamage() << '\t'
				<< w.GetSpeed() << '\t'
				<< w.GetRadius() << '\t'
				<< w.GetLifeSpan() << '\t'
				<< w.GetSpread() << '\t'
				<< w.GetFireOffsetX() << '\t'
				<< w.GetFireOffsetY() << '\t'
				<< w.GetFireOffsetZ() << '\t'
				<< w.GetAnimName() << '\t'
				<< w.GetAnimLoopStart() << '\t'
				<< w.GetAnimLoopEnd() << '\t'
				<< w.GetAnimFrameFire() << '\t'
				<< w.GetAnim2LoopStart() << '\t'
				<< w.GetAnim2LoopEnd() << '\t'
				<< w.GetAnim2FrameFire() << '\t'
				<< w.GetAnimBreakOut() << '\t'
				<< w.GetModelId() << '\t'
				<< w.GetModel2Id() << '\t'
				<< w.GetFlags() << '\t'
				<< w.GetSlot() << std::endl;
		}
		f << "ENDWEAPONDATA";
		return true;
	};

	if (!extractWeaponInfo(gpWeaponTables[0], "weapon.dat"))
		return false;
	return extractWeaponInfo(gpWeaponTables[1], "weapon_multi.dat");
}