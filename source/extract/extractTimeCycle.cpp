#include "Extract.h"
#include "TimeCycle.h"
#include "Utils.h"
#include <fstream>

bool ExtractTimeCycle()
{
	/* Weather names */
	static const char* const weathers[]{
		"SUNNY",
		"CLOUDY",
		"RAINY",
		"FOGGY",
		"EXTRASUNNY",
		"HURRICANE",
		"EXTRACOLOURS",
#ifdef LCS
		"SNOW"
#else
		"ULTRASUNNY"
#endif
	};

	/* Field names */
	static const char* const fields[]{
		"Amb",
		"Amb_Obj",
		"Amb_bl",
		"Amb_Obj_bl",
		"Dir",
		"Sky top",
		"Sky bot",
		"SunCore",
		"SunCorona",
		"SunSz",
		"SprSz",
		"SprBght",
		"Shdw",
		"LightShd",
		"PoleShd",
		"FarClip",
		"FogSt",
#if defined VCS && defined PS2
		"Rad limit",
		"Rad Intensity"
#endif
		"LightOnGround",
		"LowCloudsRGB",
		"TopCloudRGB",
		"BottomCloudRGB",
		"BlurRGB",
		"WaterRGBA",
#if defined VCS && defined PS2
		"Blur strength",
		"Blur offset"
#endif
	};

	/* Open timecyc.dat */
	std::ofstream f("timecyc.dat");
	if (!f)
	{
		ErrorBoxCannotCreateFile("timecyc.dat");
		return false;
	}
	f << "//" << ' ' << G3DTZ_MESSAGE;

	/* Print data for all weathers */
	for (int i = 0; i < 8; ++i)
	{
		/* Print weather name */
		f << std::endl << "//" << std::endl;
		for (int a = 0; a < 20; ++a) f << "//";
		f << ' ' << weathers[i];

		/* Print lines for all hours of the day */
		for (int j = 0; j < 24; ++j)
		{
			/* Print hour */
			static char time[]{ '\0', 'M', '\0' };
			f << std::endl << "//";
			if (j % 12 == 0)
			{
				time[0] = time[0] == 'A' ? 'P' : 'A';
				f << std::endl << "//";
				for (auto& s : fields) f << '\t' << s;
				f << std::endl << "//" << ' ' << (j > 0 ? "Midday" : "Midnight");
			}
			else
				f << ' ' << j % 12 << time;
				
			/* Print line */
			f	<< std::endl << static_cast<int>(pTimeCycle->m_nAmbientRed[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nAmbientGreen[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nAmbientBlue[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nAmbientRed_Obj[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nAmbientGreen_Obj[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nAmbientBlue_Obj[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nAmbientRed_Bl[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nAmbientGreen_Bl[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nAmbientBlue_Bl[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nAmbientRed_Obj_Bl[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nAmbientGreen_Obj_Bl[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nAmbientBlue_Obj_Bl[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nDirectionalRed[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nDirectionalGreen[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nDirectionalBlue[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nSkyTopRed[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nSkyTopGreen[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nSkyTopBlue[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nSkyBottomRed[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nSkyBottomGreen[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nSkyBottomBlue[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nSunCoreRed[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nSunCoreGreen[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nSunCoreBlue[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nSunCoronaRed[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nSunCoronaGreen[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nSunCoronaBlue[j][i])
				<< '\t'      << Precision(0.1f * static_cast<float>(pTimeCycle->m_nSunSize[j][i]))
				<< '\t'      << Precision(0.1f * static_cast<float>(pTimeCycle->m_nSpriteSize[j][i]))
				<< '\t'      << Precision(0.1f * static_cast<float>(pTimeCycle->m_nSpriteBrightness[j][i]))
				<< '\t'      << static_cast<int>(pTimeCycle->m_nShadowStrength[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nLightShadowStrength[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nPoleShadowStrength[j][i])
				<< '\t'      << pTimeCycle->m_nFarClip[j][i] << ".0"
				<< '\t'      << pTimeCycle->m_nFogStart[j][i] << ".0"
#if defined VCS && defined PS2
				<< '\t'      << static_cast<int>(pTimeCycle->m_nRadiosityLimit[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nRadiosityIntensity[j][i])
#endif
				<< '\t'      << Precision(0.1f * static_cast<float>(pTimeCycle->m_nLightsOnGroundBrightness[j][i]))
				<< '\t'      << static_cast<int>(pTimeCycle->m_nLowCloudsRed[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nLowCloudsGreen[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nLowCloudsBlue[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nFluffyCloudsTopRed[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nFluffyCloudsTopGreen[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nFluffyCloudsTopBlue[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nFluffyCloudsBottomRed[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nFluffyCloudsBottomGreen[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nFluffyCloudsBottomBlue[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nBlurRed[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nBlurGreen[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nBlurBlue[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nWaterRed[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nWaterGreen[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nWaterBlue[j][i])
				<< '\t'      << static_cast<int>(pTimeCycle->m_nWaterAlpha[j][i]);
#if defined VCS && defined PS2
			f	<< '\t' << PrecisionAny(pTimeCycle->m_fBlurAlpha[j][i])
				<< '\t' << PrecisionAny(pTimeCycle->m_fBlurOffset[j][i]);
#endif
		}
	}
	return true;
}