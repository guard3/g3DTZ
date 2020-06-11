#pragma once
#include "Common.h"

class CPopulation final
{
public:
	inline static int32(*ms_pPedGroups)[16];
#ifdef LCS
	inline static constexpr int NUM_PEDGROUPS = 37;
#else
	inline static constexpr int NUM_PEDGROUPS = 71;
#endif
	static void LoadPedGroups(int32(*pedgroups)[16]) { ms_pPedGroups = pedgroups; }
};