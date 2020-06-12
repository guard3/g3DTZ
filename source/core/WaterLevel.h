#pragma once
#include "Maths.h"
#include "RslEngine.h"

class CWaterLevel final
{
public:
	int32       m_nNoOfWaterLevels;
	float      *m_aWaterZs;
	CRect      *m_aWaterRects;
	uint8       aWaterBlockList[64][64];       // 64x64 Large blocks 64x64 each
	uint8       aWaterFineBlockList[128][128]; // 128x128 Small blocks 32x32 each
	RslElement *m_pWavyAtomic;
	RslElement *m_pMaskAtomic;

	inline static CWaterLevel* mspInst;
	static void Load(CWaterLevel* inst) { mspInst = inst; }
};