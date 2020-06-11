#pragma once
#include "Common.h"

class CSurfaceTable final
{
private:
	inline static float(*ms_aAdhesiveLimitTable)[6];
public:
	static void Load(float(*table)[6])  { ms_aAdhesiveLimitTable = table; }
	static auto GetAdhesiveLimitTable() { return ms_aAdhesiveLimitTable;  }
};