#pragma once
#include "Common.h"

struct RslV3d
{
	float x, y, z;
};

struct RslMatrix
{
	RslV3d right;
	float  rightw;
	RslV3d up;
	float  upw;
	RslV3d at;
	float  atw;
	RslV3d pos;
	float  posw;
};

struct RslRGBA
{
	uint8 r, g, b, a;

	operator uint32() { return *reinterpret_cast<uint32*>(this); }
};

struct RslRGB
{
	uint8 r, g, b;

	operator uint32() { return RslRGBA{ r, g, b, 0 }; }
};

struct RslMaterial;
struct RslObject;
struct RslTexList;
struct RslRaster;
struct RslLLLink
{
	RslLLLink* next;
	RslLLLink* prev;
};
struct RslTexture
{
	RslRaster  *raster;
	RslTexList *dict;
	RslLLLink   lInDictionary;
	char        name[32];
	char        mask[32];
};