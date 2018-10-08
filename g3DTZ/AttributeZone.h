/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	AttributeZone.h - Structs about cull.ipl
*/
#pragma once
#include "typedef.h"

struct AtributeZone
{
	int16 lowerX;
	int16 upperX;
	int16 lowerY;
	int16 upperY;
	int16 lowerZ;
	int16 upperZ;
	int16 attribute;
	int16 wantedLevelDrop;
};