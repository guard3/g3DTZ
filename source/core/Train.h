#pragma once
#include "Maths.h"

class CTrainInterpolationLine;

class CTrainNode final
{
public:
	CVector m_position;
	float   m_distanceFromStartOfTrack;

public:
	CVector GetPosition() { return m_position; }
};

class CTrainTrack final
{
public:
	float                    totalLengthOfTrack;
	float                    totalDurationOfTrack;
	int16                    numTrackNodes;
	CTrainNode              *aTrainNodes;
	CTrainInterpolationLine *aLineBits;
};

class CTrain final
{
private:
	uint8 unk[0x70];
	CTrainTrack* m_pTrack;   // El Train
	CTrainTrack* m_pTrack_S; // Subway
	uint8 unk2[0x38];

	inline static CTrain* mspInst;

public:
	static void Init(CTrain* inst)   { mspInst = inst; }
	static int  GetNumTrackNodes()   { return mspInst->m_pTrack->numTrackNodes;   }
	static int  GetNumTrackNodes_S() { return mspInst->m_pTrack_S->numTrackNodes; }
	static CTrainNode* GetTrackNode(int index)   { return mspInst->m_pTrack->aTrainNodes + index;   }
	static CTrainNode* GetTrackNode_S(int index) { return mspInst->m_pTrack_S->aTrainNodes + index; }
};