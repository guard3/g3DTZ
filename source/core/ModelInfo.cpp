#include "ModelInfo.h"
#include "TexListStore.h"
#include "AnimManager.h"
#include "HandlingMgr.h"
#include "PedStats.h"
#include <map>
#include <vector>

/* Static variables of CModelInfo */
CBaseModelInfo **CModelInfo::ms_modelInfoPtrs;
uint32           CModelInfo::ms_numModelInfos;
C2dEffect       *CModelInfo::ms_2dEffects;
uint32           CModelInfo::ms_num2dEffects;

#ifdef LCS
/* CVehicleModelInfo instance */
CVehicleModelInfo::inst* CVehicleModelInfo::mspInfo;
#else
RslRGB(*gpColourTable)[128];
#endif

/* A custom container for names */
class cNameContainer final
{
private:
#pragma warning(suppress: 6262)
	std::map<uint32, const char*> m_nameMap = {
#ifdef LCS
#include "lcsnames.inc"
#else
#include "vcsnames.inc"
#include "bruteforcedvcsnames.inc"
#endif
	};
	std::vector<const char*> m_nameVector;

public:
	~cNameContainer()
	{
		/* Delete all extra names */
		for (auto& a : m_nameVector)
			delete[] a;
	}

	const char* operator[](uint32 hashname)
	{
		/* Get a name from the name map */
		const char*& result = m_nameMap[hashname];
		if (!result)
		{
			/* If it doesn't exist, make one based on its hash */
			char* temp = new char[14];
			sprintf(temp, "hash_%.8X", hashname);
			m_nameVector.push_back(temp);
			result = temp;
		}
		return result;
	}
} names;

const char* CBaseModelInfo::GetModelName()
{
	return names[m_hashname];
}

const char* CBaseModelInfo::GetTexListName()
{
	return CTexListStore::GetSlot(m_texlistSlot)->GetName();
}

C2dEffect* CBaseModelInfo::Get2dEffects()
{
	return m_num2dEffects == 0 ? nullptr : CModelInfo::ms_2dEffects + m_first2dEffect;
}

CObjectInfo* CBaseModelInfo::GetObjectInfo()
{
	return m_objectId == -1 ? nullptr : CObjectData::GetSlot(m_objectId);
}

const char* CWeaponModelInfo::GetAnimBlockName()
{
	return m_animBlockId == -1 ? "null" : CAnimManager::GetAnimationBlock(m_animBlockId)->m_name;
}

const char* CVehicleModelInfo::GetVehicleTypeName()
{
	static const char* const vehicleTypes[] = {
		"car",
		"boat",
#ifdef VCS
		"jetski",
#endif
		"train",
		"heli",
		"plane",
		"bike",
		"ferry",
#ifdef VCS
		"bmx",
		"quad"
#endif
	};
	return vehicleTypes[m_vehicleType];
}

const char* CVehicleModelInfo::GetAnimBlockName()
{
	return m_animBlockId == -1 ? "null" : CAnimManager::GetAnimationBlock(m_animBlockId)->m_name;
}

const char* CVehicleModelInfo::GetVehicleClass()
{
	static const char* const vehicle_classes[] {
		"normal",
		"poorfamily",
		"richfamily",
		"executive",
		"worker",
		"big",
		"taxi",
		"moped",
		"motorbike",
		"leisureboat",
		"workerboat",
#ifdef VCS
		"smallfunboat",
		"bigfunboat"
#endif
	};
	return m_vehicleClass == -1 ? "ignore" : vehicle_classes[m_vehicleClass];

}

#ifdef LCS
const char* CVehicleModelInfo::GetHandlingName()
{
	return CHandlingDataMgr::GetHandlingData(m_handlingId).GetHandlingName();
}
#endif

const char* CPedModelInfo::GetAnimGroup()
{
	return CAnimManager::GetAssocGroup(m_animGroup)->GetName();
}

const char* CPedModelInfo::GetPedType()
{
	static const char* const ped_types[] = {
		"PLAYER1",
		"PLAYER2",
		"PLAYER3",
		"PLAYER4",
		"CIVMALE",
		"CIVFEMALE",
		"COP",
		"GANG1",
		"GANG2",
		"GANG3",
		"GANG4",
		"GANG5",
		"GANG6",
		"GANG7",
		"GANG8",
		"GANG9",
		"EMERGENCY",
		"FIREMAN",
		"CRIMINAL",
		"SPECIAL",
		"PROSTITUTE"
	};
	return ped_types[m_pedType];
}

const char* CPedModelInfo::GetAnimBlock()
{
	return m_animGroupId == -1 ? "null" : CAnimManager::GetAnimationBlock(m_animGroupId)->m_name;
}

const char* CPedModelInfo::GetPedStatType()
{
	return CPedStats::GetPedStats(m_pedStatType)->GetName();
}