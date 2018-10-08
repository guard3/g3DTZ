/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	WeaponInfo.h - Structs about weapon data
*/
#pragma once
#include "typedef.h"
#include "Vector.h"

const char* fireTypes[] = {
	"MELEE",
	"INSTANT_HIT",
	"PROJECTILE",
	"AREA_EFFECT",
	"CAMERA"
};

const char* weaponNames[] = {
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
#ifdef vcs
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
#ifdef vcs
	"Binoculars"
#endif
};

struct WeaponAnim
{
	float loopStart;
	float loopEnd;
	float weaponFired;
};

struct WeaponInfo
{
#ifdef vcs
	uint32		flags;
#endif
	int32		fireType;
	float		range;
	int32		firingRate;
	int32		reload;
	int32		amountAmmo;
	int32		damage;
	float 		speed;
	float 		radius;
	float 		lifeSpan;
	float 		spread;
#ifdef lcs
	char		padding[8];	//Padding for Vector4D
#else
	char		padding[4];	//Padding for Vector4D
#endif
	Vector4D	fireOffset;
	int32		animIndex;
	WeaponAnim	anim1;
	WeaponAnim	anim2;
	float		animBreakOut;
	int32		modelIndex;
	int32		modelIndex2;
	int32		slot;
#ifdef lcs
	uint32		flags;
#else
	char		padding2[4];
#endif
};