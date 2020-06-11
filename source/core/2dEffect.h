#pragma once
#include "Common.h"
#include "Maths.h"
#include "RslEngine.h"

enum e2dEffectType : uint8
{
	EFFECT_LIGHT,
	EFFECT_PARTICLE,
	EFFECT_ATTRACTOR,
	EFFECT_PEDBEHAVIOUR
};

class C2dEffect final
{
public:
	CVuVector     position;
	RslRGBA       colour;
	e2dEffectType type;
	union
	{
		/* EFFECT_LIGHT */
		struct
		{
			float       distance;
			float       outerRange;
			float       size;
			float       innerRange;
			uint8       flash;
			uint8       wet;
			uint8       flare;
			uint8       shadowIntensity;
			uint8       flags;
			RslTexture* corona;
			RslTexture* shadow;
			uint8       padding[8];
		} light;

		/* EFFECT_PARTICLE */
		struct
		{
			int32   particleType;
			CVector strength;
			float   scale;
			uint8   padding[20];
		} particle;

		/* EFFECT_ATTRACTOR */
		struct
		{
			CVector direction;
			uint8   subtype; //Unknown
			uint8   probability;
			uint8   padding[26];
		} attractor;

		/* EFFECT_PEDBEHAVIOUR */
		struct
		{
			CVector direction;
			CVector rotation;
			uint8   behaviour;
			uint8   padding[12];
		} pedbehaviour;
	};
};