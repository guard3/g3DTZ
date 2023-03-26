#include "Ped.h"
#include "AnimManager.h"

const char* tFightMove::GetAnimationName()
{
	switch (animId)
	{
	case 0:
		return "null";
	case 201:
	case 202:
	case 205:
		return "default";
	default:
		return CAnimManager::GetAssocGroup(0)->m_aAssociationArray[animId].hierarchy->name;
	}
}