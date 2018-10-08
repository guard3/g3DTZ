/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	ColourTable.h - Structs about carcols.dat col section for LCS
	Big thanks to aap for his nice struct
*/
#pragma once
#include "typedef.h"
#include "rsl.h"

struct ColourTable
{
	void *unk;	//Probably ms_pEnvironmentMaps
	RGBA vehicleColours[256];
	char compsUsed[2];
	char compsToUse[2];
};