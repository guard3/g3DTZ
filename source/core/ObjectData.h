#pragma once
#include "Common.h"
#include "Utils.h"

class CObjectInfo final
{
private:
	float m_fMass;
	float m_fTurnMass;
	float m_fAirResistance;
	float m_fElasticity;
	float m_fPercentSubmerged;
	float m_fUprootLimit;
	float m_fCollisionDamageMultiplier;
	uint8 m_nCollisionDamageEffect;
	uint8 m_nSpecialCollisionResponseCases;
	bool  m_bCameraToAvoidThisObject;
#ifdef VCS
	uint8 unk1, unk2;
#endif

public:
	const char* GetMass()          { return Precision(m_fMass);          }
	const char* GetTurnMass()      { return Precision(m_fTurnMass);      }
	const char* GetAirResistance() { return Precision(m_fAirResistance); }
	const char* GetElasticity()    { return Precision(m_fElasticity);    }
	const char* GetBuoyancy()      { return Precision(m_fMass * 0.8f / m_fPercentSubmerged); }
	const char* GetUprootLimit()   { return Precision(m_fUprootLimit);   }
	const char* GetCollisionDamageMultiplier()     { return Precision(m_fCollisionDamageMultiplier); }
	int         GetCollisionDamageEffect()         { return m_nCollisionDamageEffect;                }
	int         GetSpecialCollisionResponseCases() { return m_nSpecialCollisionResponseCases;        }
	int         GetCameraToAvoidThisObject()       { return m_bCameraToAvoidThisObject;              }
#ifdef VCS
	int GetUnk1() { return unk1; }
	int GetUnk2() { return unk2; }
#endif
};

class CObjectData final
{
private:
	inline static CObjectInfo* ms_aObjectInfo;

public:
	static void Load(CObjectInfo* objectInfo) { ms_aObjectInfo = objectInfo; }
	static CObjectInfo* GetSlot(int index) { return ms_aObjectInfo + index; }
};