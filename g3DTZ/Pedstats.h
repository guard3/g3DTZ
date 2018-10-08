/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	Pedstats.h - Structs about pedstats.dat
	Big thanks to aap for his nice struct
*/
#pragma once
#include "typedef.h"

struct PedStat
{
#ifdef lcs
	int32	index;
	char	name[24];
	float	fleeDistance;
	float	headingChangeRate;
	uint8	fear;
	uint8	temper;
	uint8	lawfulness;
	uint8	sexiness;
	float	attackStrength;
	float	defendWeakness;
	uint16	flags;
#else
	int32	index;
	float	fleeDistance;
	float	headingChangeRate;
	float	attackStrength;
	float	defendWeakness;
	uint16	flags;
	uint8	fear;
	uint8	temper;
	uint8	lawfulness;
	uint8	sexiness;
	char	name[24];
#endif
};