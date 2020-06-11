#pragma once
#include "Common.h"

struct tSample
{
	int32 nOffset;
	int32 nSize;
	int32 nFrequency;
};

class CSampleManager final
{
public:
#ifdef LCS
	inline static constexpr int TOTAL_AUDIO_SAMPLES = 0x161D;
#else
	inline static constexpr int TOTAL_AUDIO_SAMPLES = 0x1E63;
#endif
	inline static tSample* m_aSamples;
	static void LoadSamples(tSample* samples) { m_aSamples = samples; }
};