#pragma once
#include "Common.h"
#include "RslEngine.h"
#include "Utils.h"

class CParticle;

class CParticleSystemData final
{
private:
	int32 m_Type;
	char m_aName[20];
	float m_fCreateRange;
	float m_fDefaultInitialRadius;
#ifdef LCS
	float m_fExpansionRate;
	uint16 m_nZRotationInitialAngle;
	uint16 m_nZRotationAngleChangeAmount;
	uint16 m_nZRotationChangeTime;
	uint16 m_nZRadiusChangeTime;
	float m_fInitialZRadius;
#endif
	float m_fZRadiusChangeAmount;
	uint16 m_nFadeToBlackTime;
	uint16 m_nFadeToBlackInitialIntensity;
	int16 m_nFadeToBlackAmount;
	uint16 m_nFadeAlphaInitialIntensity;
	uint16 m_nFadeAlphaTime;
	uint16 m_nFadeAlphaAmount;
	uint8 m_nStartAnimationFrame;
	uint8 m_nFinalAnimationFrame;
	uint16 m_nAnimationSpeed;
	int32 m_nRotationSpeed;
	float m_fGravitationalAcceleration;
	int32 m_nFrictionDecceleration;
	int32 m_nLifeSpan;
	float m_fPositionRandomError;
	float m_fVelocityRandomError;
	float m_fExpansionRateError;
	int32 m_nRotationRateError;
	int32 m_nLifeSpanError;
	float m_fTrailLengthMultiplier;
	uint32 m_Flags;
	RslRGBA m_RenderColouring;
	int32 m_InitialColourVariation;
	RslRGBA m_FadeDestinationColour;
	int32 m_ColourFadeTime;
	float stretchX;
	float stretchY;
	float m_fWindFactor;
	RslRaster** m_ppRaster;
	CParticle* m_pParticles;

public:
	const char* GetName() { return m_aName; }
	auto GetDefaultInitialRadius() { return Precision5(m_fDefaultInitialRadius); }
#ifdef LCS
	auto GetExpansionRate() { return Precision3(m_fExpansionRate); }
	int GetZRotationInitialAngle() { return m_nZRotationInitialAngle; }
	int GetZRotationChangeTime() { return m_nZRotationChangeTime; }
	int GetZRotationAngleChangeAmount() { return m_nZRotationAngleChangeAmount; }
	auto GetInitialZRadius() { return Precision(m_fInitialZRadius); }
	int GetZRadiusChangeTime() { return m_nZRadiusChangeTime; }
#endif
	auto GetZRadiusChangeAmount() { return Precision(m_fZRadiusChangeAmount); }
	int GetFadeToBlackTime() { return m_nFadeToBlackTime; }
	int GetFadeToBlackInitialIntensity() { return m_nFadeToBlackInitialIntensity; }
	int GetFadeToBlackAmount() { return m_nFadeToBlackAmount; }
	int GetFadeAlphaInitialIntensity() { return m_nFadeAlphaInitialIntensity; }
	int GetFadeAlphaTime() { return m_nFadeAlphaTime; }
	int GetFadeAlphaAmount() { return m_nFadeAlphaAmount; }
	int GetStartAnimationFrame() { return m_nStartAnimationFrame; }
	int GetFinalAnimationFrame() { return m_nFinalAnimationFrame; }
	int GetAnimationSpeed() { return m_nAnimationSpeed; }
	int GetRotationSpeed() { return m_nRotationSpeed; }
	auto GetGravitationalAcceleration() { return PrecisionAny(m_fGravitationalAcceleration); }
	int GetFrictionDecceleration() { return m_nFrictionDecceleration; }
	int GetLifeSpan() { return m_nLifeSpan; }
	auto GetPositionRandomError() { return Precision3(m_fPositionRandomError); }
	auto GetVelocityRandomError() { return Precision3(m_fVelocityRandomError); }
	auto GetExpansionRateError() { return Precision3(m_fExpansionRateError); }
	int GetRotationRateError() { return m_nRotationRateError; }
	int GetLifeSpanError() { return m_nLifeSpanError; }
	auto GetTrailLengthMultiplier() { return Precision(m_fTrailLengthMultiplier); }
	int GetFlags() { return m_Flags; }
	RslRGBA GetRenderColouring() { return m_RenderColouring; }
	int32 GetInitialColourVariation() { return m_InitialColourVariation; }
	RslRGBA GetFadeDestinationColour() { return m_FadeDestinationColour; }
	int32 GetColourFadeTime() { return m_ColourFadeTime; }
	auto GetstretchX() { return Precision(stretchX); }
	auto GetstretchY() { return Precision(stretchY); }
	auto GetWindFactor() { return Precision(m_fWindFactor); }

	const char* GetCreateRange();
};

class CParticleSystemMgr final
{
public:
#ifdef LCS
	inline static constexpr int NUM_PARTICLEDATA = 82;
#else
	inline static constexpr int NUM_PARTICLEDATA = 90;
#endif
private:
	inline static CParticleSystemMgr* mspInst;
	CParticleSystemData m_aParticles[NUM_PARTICLEDATA];

public:
	static void Load(CParticleSystemMgr* data) { mspInst = data; }
	static CParticleSystemData& GetParticle(int index) { return mspInst->m_aParticles[index]; }
};