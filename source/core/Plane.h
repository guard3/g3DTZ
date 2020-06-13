#pragma once
#include "Maths.h"

class CPlaneNode final
{
private:
	CVector m_position;
	float   m_distanceFromStartOfPath;
	bool    bOnGround;
	uint8   unk[3];
public:
	CVector GetPosition() { return m_position; }
};

class CPlaneInterpolationLine final
{
public:
	uint8 type;
	float time;
	float position;
	float speed;
	float acceleration;
};

class CPlane final
{
private:
	float                   unk1[3]; // Most likely related to unused flight paths, all 0.0
	float                   totalLengthOfFlightPath;
	float                   takeOffPoint;
	float                   landingPoint;
	float                   totalDurationOfFlightPath;
	float                   unk2[9]; // Most likely related to unused flight paths, all 0.0
	int32                   numPathNodes;
	CPlaneNode*             pPathNodes;
	CPlaneInterpolationLine aPlaneLineBits[6];

	inline static CPlane* mspInst;
public:
	static void Init(CPlane* inst) { mspInst = inst; }
	static int GetNumPlaneNodes() { return mspInst->numPathNodes; }
	static CPlaneNode* GetPlaneNode(int index) { return mspInst->pPathNodes + index; }
};