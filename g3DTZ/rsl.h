/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	rsl.h - general rsl structs
	Based on aap's nicely laid out structs
*/
#pragma once
#include "typedef.h"

struct RGBA
{
	uint8 r, g, b, a;
};

struct RGB
{
	uint8 r, g, b;
};

struct RslLLLink
{
	RslLLLink	*next;
	RslLLLink	*prev;
};

struct RslTexture
{
	void		*raster;
	void		*dict;
	RslLLLink	lInDictionary;
	char		name[32];
	char		mask[32];
};

struct Rect
{
	float left;
	float top;
	float right;
	float bottom;
};