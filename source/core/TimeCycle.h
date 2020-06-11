#pragma once
#include "Common.h"
#include "Maths.h"

class CTimeCycle final
{
private:
	CVuVector m_VectorToSun[16];      // *
	float m_fShadowFrontX[16];        // *
	float m_fShadowFrontY[16];        // *
	float m_fShadowSideX[16];         // * filled at runtime
	float m_fShadowSideY[16];         // *
	float m_fShadowDisplacementX[16]; // *
	float m_fShadowDisplacementY[16]; // *
public:
	uint8 m_nAmbientRed[24][8];
	uint8 m_nAmbientGreen[24][8];
	uint8 m_nAmbientBlue[24][8];
	uint8 m_nAmbientRed_Obj[24][8];
	uint8 m_nAmbientGreen_Obj[24][8];
	uint8 m_nAmbientBlue_Obj[24][8];
	uint8 m_nAmbientRed_Bl[24][8];
	uint8 m_nAmbientGreen_Bl[24][8];
	uint8 m_nAmbientBlue_Bl[24][8];
	uint8 m_nAmbientRed_Obj_Bl[24][8];
	uint8 m_nAmbientGreen_Obj_Bl[24][8];
	uint8 m_nAmbientBlue_Obj_Bl[24][8];
	uint8 m_nDirectionalRed[24][8];
	uint8 m_nDirectionalGreen[24][8];
	uint8 m_nDirectionalBlue[24][8];
	uint8 m_nSkyTopRed[24][8];
	uint8 m_nSkyTopGreen[24][8];
	uint8 m_nSkyTopBlue[24][8];
	uint8 m_nSkyBottomRed[24][8];
	uint8 m_nSkyBottomGreen[24][8];
	uint8 m_nSkyBottomBlue[24][8];
	uint8 m_nSunCoreRed[24][8];
	uint8 m_nSunCoreGreen[24][8];
	uint8 m_nSunCoreBlue[24][8];
	uint8 m_nSunCoronaRed[24][8];
	uint8 m_nSunCoronaGreen[24][8];
	uint8 m_nSunCoronaBlue[24][8];
	uint8 m_nSunSize[24][8];
	uint8 m_nSpriteSize[24][8];
	uint8 m_nSpriteBrightness[24][8];
	uint8 m_nShadowStrength[24][8];
	uint8 m_nLightShadowStrength[24][8];
	uint8 m_nPoleShadowStrength[24][8];
	int16 m_nFarClip[24][8];
	int16 m_nFogStart[24][8];
#if defined(VCS) && defined(PS2)
	uint8 m_nRadiosityIntensity[24][8];
	uint8 m_nRadiosityLimit[24][8];
#endif
	uint8 m_nLightsOnGroundBrightness[24][8];
	uint8 m_nLowCloudsRed[24][8];
	uint8 m_nLowCloudsGreen[24][8];
	uint8 m_nLowCloudsBlue[24][8];
	uint8 m_nFluffyCloudsTopRed[24][8];
	uint8 m_nFluffyCloudsTopGreen[24][8];
	uint8 m_nFluffyCloudsTopBlue[24][8];
	uint8 m_nFluffyCloudsBottomRed[24][8];
	uint8 m_nFluffyCloudsBottomGreen[24][8];
	uint8 m_nFluffyCloudsBottomBlue[24][8];
	uint8 m_nBlurRed[24][8];
	uint8 m_nBlurGreen[24][8];
	uint8 m_nBlurBlue[24][8];
	uint8 m_nWaterRed[24][8];
	uint8 m_nWaterGreen[24][8];
	uint8 m_nWaterBlue[24][8];
	uint8 m_nWaterAlpha[24][8];
#if defined(VCS) && defined(PS2)
	float m_fBlurAlpha[24][8];
	float m_fBlurOffset[24][8];
#endif
private:
	/* Those below could be wrong */
	int32 m_nCurrentAmbientRed;
	int32 m_nCurrentAmbientGreen;
	int32 m_nCurrentAmbientBlue;
	int32 m_nCurrentAmbientRed_Obj;
	int32 m_nCurrentAmbientGreen_Obj;
	int32 m_nCurrentAmbientBlue_Obj;
	int32 m_nCurrentAmbientRed_Bl;
	int32 m_nCurrentAmbientGreen_Bl;
	int32 m_nCurrentAmbientBlue_Bl;
	int32 m_nCurrentAmbientRed_Obj_Bl;
	int32 m_nCurrentAmbientGreen_Obj_Bl;
	int32 m_nCurrentAmbientBlue_Obj_Bl;
	int32 m_nCurrentDirectionalRed;
	int32 m_nCurrentDirectionalGreen;
	int32 m_nCurrentDirectionalBlue;
	int32 m_nCurrentSkyTopRed;
	int32 m_nCurrentSkyTopGreen;
	int32 m_nCurrentSkyTopBlue;
	int32 m_nCurrentSkyBottomRed;
	int32 m_nCurrentSkyBottomGreen;
	int32 m_nCurrentSkyBottomBlue;
	int32 m_nCurrentFogColourRed;
	int32 m_nCurrentFogColourGreen;
	int32 m_nCurrentFogColourBlue;
	int32 m_nCurrentSunCoreRed;
	int32 m_nCurrentSunCoreGreen;
	int32 m_nCurrentSunCoreBlue;
	int32 m_nCurrentSunCoronaRed;
	int32 m_nCurrentSunCoronaGreen;
	int32 m_nCurrentSunCoronaBlue;
	int32 m_nCurrentSunSize;
	int32 m_nCurrentSpriteSize;
	int32 m_nCurrentSpriteBrightness;
	int16 m_nCurrentShadowStrength;
	int16 m_nCurrentLightShadowStrength;
	int16 m_nCurrentPoleShadowStrength;
	int32 m_nCurrentFarClip;
	int32 m_nCurrentFogStart;
#if defined(VCS) && defined(PS2)
	int32 m_nCurrentRadiosityIntensity;
	int32 m_nCurrentRadiosityLimit;
#endif
	int32 m_nCurrentLightsOnGroundBrightness;
	int32 m_nCurrentLowCloudsRed;
	int32 m_nCurrentLowCloudsGreen;
	int32 m_nCurrentLowCloudsBlue;
	int32 m_nCurrentFluffyCloudsTopRed;
	int32 m_nCurrentFluffyCloudsTopGreen;
	int32 m_nCurrentFluffyCloudsTopBlue;
	int32 m_nCurrentFluffyCloudsBottomRed;
	int32 m_nCurrentFluffyCloudsBottomGreen;
	int32 m_nCurrentFluffyCloudsBottomBlue;
	int32 m_nCurrentBlurRed;
	int32 m_nCurrentBlurGreen;
	int32 m_nCurrentBlurBlue;
	int32 m_nCurrentWaterRed;
	int32 m_nCurrentWaterGreen;
	int32 m_nCurrentWaterBlue;
	int32 m_nCurrentWaterAlpha;
#if defined(VCS) && defined(PS2)
	float m_nCurrentBlurAlpha;
	float m_nCurrentBlurOffset;
#endif
	int32 m_nCurrentStoredValue;
	int32 m_nFogReduction;
	int32 m_nExtraColour;
	int32 m_nExtraColourOn;
	int32 m_nExtraColourInter;
	int32 unk;
};

inline CTimeCycle* pTimeCycle;