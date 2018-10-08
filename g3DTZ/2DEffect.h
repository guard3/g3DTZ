/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	2DEffect.h - Structs about 2dfx data
	Based on aap's nicely laid out struct
*/
#pragma once
#include "typedef.h"
#include "Vector.h"
#include "rsl.h"

struct _2dEffect
{
	Vector4D	position;
	RGBA		colour;
	uint8		type;
	union
	{
		//Type 0
		struct
		{
			float		distance;
			float		outerRange;
			float		size;
			float		innerRange;
			uint8		flash;
			uint8		wet;
			uint8		flare;
			uint8		shadowIntensity;
			uint8		flags;
			RslTexture	*corona;
			RslTexture	*shadow;
			char		padding[8];
		} light;

		//Type 1
		struct
		{
			int32		particleType;
			Vector3D	strength;
			float		scale;
			char		padding[20];
		} particle;

		//Type 2
		struct
		{
			Vector3D	direction;
			uint8		subtype;	//Unknown
			uint8		probability;
			char		padding[26];
		} attractor;

		//Type 3
		struct
		{
			Vector3D	direction;
			Vector3D	rotation;
			uint8		behaviour;
			char		padding[12];
		} pedbehaviour;
	};
};