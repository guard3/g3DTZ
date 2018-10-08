/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	TimeCycle.h - Structs about timecycle data
	Big thanks to aap for his nice struct
*/
#pragma once
#include "typedef.h"
#include "Vector.h"

struct TimeCycle
{
	Vector4D vectorToSun[16];		//filled on runtime
	float shadowFrontX[16];			//filled on runtime
	float shadowFrontY[16];			//filled on runtime
	float shadowSideX[16];			//filled on runtime
	float shadowSideY[16];			//filled on runtime
	float shadowDisplacementX[16];	//filled on runtime
	float shadowDisplacementY[16];	//filled on runtime

	uint8 ambientRed[24][8];
	uint8 ambientGreen[24][8];
	uint8 ambientBlue[24][8];

	uint8 ambientRed_Obj[24][8];
	uint8 ambientGreen_Obj[24][8];
	uint8 ambientBlue_Obj[24][8];

	uint8 ambientRed_Bl[24][8];
	uint8 ambientGreen_Bl[24][8];
	uint8 ambientBlue_Bl[24][8];

	uint8 ambientRed_Obj_Bl[24][8];
	uint8 ambientGreen_Obj_Bl[24][8];
	uint8 ambientBlue_Obj_Bl[24][8];

	uint8 directionalRed[24][8];
	uint8 directionalGreen[24][8];
	uint8 directionalBlue[24][8];

	uint8 skyTopRed[24][8];
	uint8 skyTopGreen[24][8];
	uint8 skyTopBlue[24][8];

	uint8 skyBottomRed[24][8];
	uint8 skyBottomGreen[24][8];
	uint8 skyBottomBlue[24][8];

	uint8 sunCoreRed[24][8];
	uint8 sunCoreGreen[24][8];
	uint8 sunCoreBlue[24][8];

	uint8 sunCoronaRed[24][8];
	uint8 sunCoronaGreen[24][8];
	uint8 sunCoronaBlue[24][8];

	uint8 sunSize[24][8];
	uint8 spriteSize[24][8];
	uint8 spriteBrightness[24][8];
	uint8 shadowStrength[24][8];
	uint8 lightShadowStrength[24][8];
	uint8 poleShadowStrength[24][8];
	int16 farClip[24][8];
	int16 fogStart[24][8];
#if defined(vcs) && defined(ps2)
	uint8 radiosityIntensity[24][8];
	uint8 radiosityLimit[24][8];
#endif
	uint8 lightsOnGroundBrightness[24][8];

	uint8 lowCloudsRed[24][8];
	uint8 lowCloudsGreen[24][8];
	uint8 lowCloudsBlue[24][8];

	uint8 fluffyCloudsTopRed[24][8];
	uint8 fluffyCloudsTopGreen[24][8];
	uint8 fluffyCloudsTopBlue[24][8];

	uint8 fluffyCloudsBottomRed[24][8];
	uint8 fluffyCloudsBottomGreen[24][8];
	uint8 fluffyCloudsBottomBlue[24][8];

	uint8 blurRed[24][8];
	uint8 blurGreen[24][8];
	uint8 blurBlue[24][8];

	uint8 waterRed[24][8];
	uint8 waterGreen[24][8];
	uint8 waterBlue[24][8];
	uint8 waterAlpha[24][8];
#if defined(vcs) && defined(ps2)
	float blurAlpha[24][8];
	float blurOffset[24][8];
#endif
	int32 currentAmbientRed;
	int32 currentAmbientGreen;
	int32 currentAmbientBlue;
	int32 currentAmbientRed_Obj;
	int32 currentAmbientGreen_Obj;
	int32 currentAmbientBlue_Obj;
	int32 currentAmbientRed_Bl;
	int32 currentAmbientGreen_Bl;
	int32 currentAmbientBlue_Bl;
	int32 currentAmbientRed_Obj_Bl;
	int32 currentAmbientGreen_Obj_Bl;
	int32 currentAmbientBlue_Obj_Bl;
	int32 currentDirectionalRed;
	int32 currentDirectionalGreen;
	int32 currentDirectionalBlue;
	int32 currentSkyTopRed;
	int32 currentSkyTopGreen;
	int32 currentSkyTopBlue;
	int32 currentSkyBottomRed;
	int32 currentSkyBottomGreen;
	int32 currentSkyBottomBlue;
	int32 currentFogColourRed;
	int32 currentFogColourGreen;
	int32 currentFogColourBlue;
	int32 currentSunCoreRed;
	int32 currentSunCoreGreen;
	int32 currentSunCoreBlue;
	int32 currentSunCoronaRed;
	int32 currentSunCoronaGreen;
	int32 currentSunCoronaBlue;
	int32 currentSunSize;
	int32 currentSpriteSize;
	int32 currentSpriteBrightness;
	int16 currentShadowStrength;
	int16 currentLightShadowStrength;
	int16 currentPoleShadowStrength;
	int32 currentFarClip;
	int32 currentFogStart;
#if defined(vcs) && defined(ps2)
	int32 currentRadiosityIntensity;
	int32 currentRadiosityLimit;
#endif
	int32 currentLightsOnGroundBrightness;
	int32 currentLowCloudsRed;
	int32 currentLowCloudsGreen;
	int32 currentLowCloudsBlue;
	int32 currentFluffyCloudsTopRed;
	int32 currentFluffyCloudsTopGreen;
	int32 currentFluffyCloudsTopBlue;
	int32 currentFluffyCloudsBottomRed;
	int32 currentFluffyCloudsBottomGreen;
	int32 currentFluffyCloudsBottomBlue;
	int32 currentBlurRed;
	int32 currentBlurGreen;
	int32 currentBlurBlue;
	int32 currentWaterRed;
	int32 currentWaterGreen;
	int32 currentWaterBlue;
	int32 currentWaterAlpha;
#if defined(vcs) && defined(ps2)
	int32 currentBlurAlpha;
	int32 currentBlurOffset;
#endif
	int32 currentStoredValue;
	int32 fogReduction;
	int32 extraColour;
	int32 extraColourOn;
	int32 extraColourInter;
	int32 padding;
};