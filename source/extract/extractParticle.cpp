#include "Extract.h"
#include "ParticleMgr.h"
#include <fstream>

bool ExtractParticle()
{
	/* Open particle.cfg */
	std::ofstream f("particle.cfg");
	if (!f)
	{
		ErrorBoxCannotCreateFile("particle.cfg");
		return false;
	}
	f	<< ';' << ' ' << G3DTZ_MESSAGE << std::endl
		<< ';' << "\tA\tB\tC\tD\tCV\tB2\tC2\tD2\tFT\tE"
#ifdef LCS
		"\tF"
#endif
		"\tG\tH\tI\tGA\tHA\tIA"
#ifdef LCS
		"\tGZA\tHZA\tIZA\tGZR\tHZR"
#endif
		"\tIZR";
	for (char c = 'J'; c < 'W'; ++c) f << '\t' << c;
	f << "\tWX\tWY\tWI\tCR\tZ";

	/* Print lines */
	for (int i = 0; i < CParticleSystemMgr::NUM_PARTICLEDATA; ++i)
	{
		auto& p = CParticleSystemMgr::GetParticle(i);
		f
			<< std::endl << p.GetName()
			<< '\t' << static_cast<int>(p.GetRenderColouring().r)
			<< '\t' << static_cast<int>(p.GetRenderColouring().g)
			<< '\t' << static_cast<int>(p.GetRenderColouring().b)
			<< '\t' << p.GetInitialColourVariation()
			<< '\t' << static_cast<int>(p.GetFadeDestinationColour().r)
			<< '\t' << static_cast<int>(p.GetFadeDestinationColour().g)
			<< '\t' << static_cast<int>(p.GetFadeDestinationColour().b)
			<< '\t' << p.GetColourFadeTime()
			<< '\t' << p.GetDefaultInitialRadius()
#ifdef LCS
			<< '\t' << p.GetExpansionRate()
#endif
			<< '\t' << p.GetFadeToBlackInitialIntensity()
			<< '\t' << p.GetFadeToBlackTime()
			<< '\t' << p.GetFadeToBlackAmount()
			<< '\t' << p.GetFadeAlphaInitialIntensity()
			<< '\t' << p.GetFadeAlphaTime()
			<< '\t' << p.GetFadeAlphaAmount()
#ifdef LCS
			<< '\t' << p.GetZRotationInitialAngle()
			<< '\t' << p.GetZRotationChangeTime()
			<< '\t' << p.GetZRotationAngleChangeAmount()
			<< '\t' << p.GetInitialZRadius()
			<< '\t' << p.GetZRadiusChangeTime()
#endif
			<< '\t' << p.GetZRadiusChangeAmount()
			<< '\t' << p.GetAnimationSpeed()
			<< '\t' << p.GetStartAnimationFrame()
			<< '\t' << p.GetFinalAnimationFrame()
			<< '\t' << p.GetRotationSpeed()
			<< '\t' << p.GetGravitationalAcceleration()
			<< '\t' << p.GetFrictionDecceleration()
			<< '\t' << p.GetLifeSpan()
			<< '\t' << p.GetPositionRandomError()
			<< '\t' << p.GetVelocityRandomError()
			<< '\t' << p.GetExpansionRateError()
			<< '\t' << p.GetRotationRateError()
			<< '\t' << p.GetLifeSpanError()
			<< '\t' << p.GetTrailLengthMultiplier()
			<< '\t' << p.GetstretchX()
			<< '\t' << p.GetstretchY()
			<< '\t' << p.GetWindFactor()
			<< '\t' << p.GetCreateRange()
			<< '\t' << p.GetFlags();
	}
	f << std::endl << ";the end";

	return true;
}