#pragma once
#include "Maths.h"

class CFerryNode final
{
public:
	CVector m_position;
	float   m_distanceFromStartOfRoute;

public:
	CVector GetPosition() { return m_position; }
};

class CFerryInterpolationLine;

class CFerryRoute final
{
public:
	float                    totalLengthOfRoute;   // *
	float                    totalDurationOfRoute; // *
	int16                    numRouteNodes;        // * Copied from CTrain, seems to work nicely
	CFerryNode              *aFerryNodes;          // *
	CFerryInterpolationLine *aLineBits;            // *
};

class CFerry final
{
private:
	CFerryRoute* m_pRoute;
	uint8 unk[0x620];

	inline static CFerry* mspInst;

public:
	static void Init(CFerry* inst) { mspInst = inst; }
	static int GetNumNodes() { return mspInst->m_pRoute->numRouteNodes; }
	static CFerryNode* GetNode(int index) { return mspInst->m_pRoute->aFerryNodes + index; }
};