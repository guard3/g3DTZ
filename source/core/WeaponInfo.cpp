#include "WeaponInfo.h"
#include "AnimManager.h"
#include <stdio.h>

const char* CWeaponInfo::GetFireType()
{
	static const char* const fire_types[] = {
		"MELEE",
		"INSTANT_HIT",
		"PROJECTILE",
		"AREA_EFFECT",
		"CAMERA",
#ifdef VCS
		"BINOCULARS"
#endif
	};
	return fire_types[m_fireType];
}

const char* CWeaponInfo::GetAnimName()
{
	return CAnimManager::GetAssocGroup(m_AnimToPlay)->GetName();
}

const char* CWeaponInfo::GetFlags()
{
	static char flags[9];
	sprintf(flags, "%X", m_flags);
	return flags;
}