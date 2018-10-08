/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	ParticleManager.h - Structs about particle.cfg
*/
#pragma once
#include "typedef.h"
#include "rsl.h"

struct ParticleManager
{
	uint32		particleIndex;
	char		name[20];
	float		createRange;
	float		defaultInitialRadius;
#ifdef lcs
	float		expansionRate;
	uint16		initialAngle;
	uint16		angleChangeTime;
	uint16		angleChangeAmount;
	uint16		initialZRadius;
	float		zRadiusChangeTime;
#endif
	float		zRadiusChangeAmount;
	uint16		fadeTime_black;
	uint16		initialIntensity_black;
	uint16		fadeAmount_black;
	uint16		initialIntensity_alpha;
	uint16		fadeTime_alpha;
	uint16		fadeAmount_alpha;
	uint8		startAnimFrame;
	uint8		finalAnimFrame;
	uint8		animSpeed;
	int32		rotationSpeed;
	float		gravitationalAcceleration;
	int32		dragFrictionDecceleration;
	int32		defaultLifeSpan;
	float		positionRandomError;
	float		velocityRandomError;
	float		expansionRateError;
	int32		rotationRateError;
	int32		lifeSpanError;
	float		trailLengthMultiplier;
	uint32		flags;
	RGB			renderColouring;
	int32		initialColourVariation;
	RGB			fadeDestinationColour;
	int32		colourFadeTime;
	float		stretchX;
	float		stretchY;
	float		windFactor;
	int			unk[2];
};