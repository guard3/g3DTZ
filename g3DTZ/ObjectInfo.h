/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	ObjectInfo.h - Structs about object.dat
*/
#pragma once
#include "typedef.h"

struct ObjectInfo
{
	float	mass;
	float	turnMass;
	float	airResistance;
	float	elasticity;
	float	percentSubmerged;
	float	uprootLimit;
	float	collisionDamageMultiplier;
	uint8	collisionDamageEffect;	//dunno if this is correct for VCS
	uint8	collisionResponseCases;
	bool	cameraAvoid;
#ifdef lcs
	char	unk;					//0xAA, could be padding
#else
	uint8	unk1, unk2;				//Probably has to do with damage effects
	uint8	unk[3];					//0xAAAAAA, could be padding
#endif
};