#pragma once
#include "Common.h"
#include "Maths.h"
#include "Utils.h"

class CWeaponInfo final
{
private:
#ifdef VCS
	uint32    m_flags;
#endif
	int32     m_fireType;
	float     m_fRange;
	uint32    m_nFiringRate;
	uint32    m_nReload;
	int32     m_nAmountOfAmmunition;
	uint32    m_nDamage;
	float     m_fSpeed;
	float     m_fRadius;
	float     m_fLifeSpan;
	float     m_fSpread;
#ifdef LCS
	uint8     padding[8]; // *
#else                     // * Padding for CVuVector
	uint8     padding[4]; // *
#endif
	CVuVector m_vecFireOffset;
	int32     m_AnimToPlay;
	float     m_fAnimLoopStart;
	float     m_fAnimLoopEnd;
	float     m_fAnimFrameFire;
	float     m_fAnim2LoopStart;
	float     m_fAnim2LoopEnd;
	float     m_fAnim2FrameFire;
	float     m_fAnimBreakOut;
	int32     m_nModelId;
	int32     m_nModel2Id;
	uint32    m_nWeaponSlot;
#ifdef LCS
	uint32    m_flags;
public:
	inline static constexpr int TOTALWEAPONS = 37;
#else
	uint8     padding2[4];
public:
	inline static constexpr int TOTALWEAPONS = 40;
#endif
	auto GetRange()              { return Precision(m_fRange);    }
	auto GetFiringRate()         { return m_nFiringRate;          }
	auto GetReload()             { return m_nReload;              }
	auto GetAmountOfAmmunition() { return m_nAmountOfAmmunition;  }
	auto GetDamage()             { return m_nDamage;              }
	auto GetSpeed()              { return Precision(m_fSpeed);    }
	auto GetRadius()             { return Precision(m_fRadius);   }
	auto GetLifeSpan()           { return Precision(m_fLifeSpan); }
	auto GetSpread()             { return Precision(m_fSpread);   }
	auto GetFireOffsetX()        { return Precision(m_vecFireOffset.x); }
	auto GetFireOffsetY()        { return Precision(m_vecFireOffset.y); }
	auto GetFireOffsetZ()        { return Precision(m_vecFireOffset.z); }
	auto GetAnimLoopStart()      { return static_cast<int>(m_fAnimLoopStart  * 30.0f); }
	auto GetAnimLoopEnd()        { return static_cast<int>(m_fAnimLoopEnd    * 30.0f); }
	auto GetAnimFrameFire()      { return static_cast<int>(m_fAnimFrameFire  * 30.0f); }
	auto GetAnim2LoopStart()     { return static_cast<int>(m_fAnim2LoopStart * 30.0f); }
	auto GetAnim2LoopEnd()       { return static_cast<int>(m_fAnim2LoopEnd   * 30.0f); }
	auto GetAnim2FrameFire()     { return static_cast<int>(m_fAnim2FrameFire * 30.0f); }
	auto GetAnimBreakOut()       { return static_cast<int>(m_fAnimBreakOut   * 30.0f); }
	auto GetModelId()            { return m_nModelId;    }
	auto GetModel2Id()           { return m_nModel2Id;   }
	auto GetSlot()               { return m_nWeaponSlot; }

	const char* GetFireType();
	const char* GetAnimName();
	const char* GetFlags();
};

inline CWeaponInfo** gpWeaponTables;