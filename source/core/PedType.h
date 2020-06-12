#pragma once
#include "Common.h"
#include "Utils.h"

enum ePedFlag : uint32
{
	PED_FLAG_PLAYER1    = 1 << 0,
	PED_FLAG_PLAYER2    = 1 << 1,
	PED_FLAG_PLAYER3    = 1 << 2,
	PED_FLAG_PLAYER4    = 1 << 3,
	PED_FLAG_CIVMALE    = 1 << 4,
	PED_FLAG_CIVFEMALE  = 1 << 5,
	PED_FLAG_COP        = 1 << 6,
	PED_FLAG_GANG1      = 1 << 7,
	PED_FLAG_GANG2      = 1 << 8,
	PED_FLAG_GANG3      = 1 << 9,
	PED_FLAG_GANG4      = 1 << 10,
	PED_FLAG_GANG5      = 1 << 11,
	PED_FLAG_GANG6      = 1 << 12,
	PED_FLAG_GANG7      = 1 << 13,
	PED_FLAG_GANG8      = 1 << 14,
	PED_FLAG_GANG9      = 1 << 15,
	PED_FLAG_EMERGENCY  = 1 << 16,
	PED_FLAG_PROSTITUTE = 1 << 17,
	PED_FLAG_CRIMINAL   = 1 << 18,
	PED_FLAG_SPECIAL    = 1 << 19,
	PED_FLAG_GUN        = 1 << 20,
	PED_FLAG_COP_CAR    = 1 << 21,
	PED_FLAG_FAST_CAR   = 1 << 22,
	PED_FLAG_EXPLOSION  = 1 << 23,
	PED_FLAG_FIREMAN    = 1 << 24,
	PED_FLAG_DEADPEDS   = 1 << 25,
};

class CPedType final
{
private:
	uint32 m_nFlag;
#ifdef LCS
	float  m_fWalkSpeed;     // *
	float  m_fRunSpeed;      // *
	float  m_fFastRunSpeed;  // * Completely missing from VCS
	float  m_fFleeDistance;  // *
	float  m_fHeadingChange; // *
#endif
	uint32 m_nThreats;
	uint32 m_nAvoid;

	inline static CPedType** ms_apPedType;

public:
	static void Initialize(CPedType** pedTypes) { ms_apPedType = pedTypes; }
	static CPedType* GetPedType(int index) { return ms_apPedType[index]; }
	static const char* GetFlagName(int index);

	const char* GetFlagName();
#ifdef LCS
	/*
	 * In LCS, there are some ped types with "invalid" flag.
	 * Those ped types have all their floats set to 0 and the flag set to PED_FLAG_PLAYER1
	 * We don't need to extract those, so if just one of the floats is 0, we can "declare" the ped type invalid.
	 */
	bool IsValid() { return m_fWalkSpeed != 0.0f; }
	auto GetWalkSpeed() { return Precision(m_fWalkSpeed * 50.0f); }
	auto GetRunSpeed() { return Precision(m_fRunSpeed * 50.0f); }
	auto GetFastRunSpeed() { return Precision(m_fFastRunSpeed * 50.0f); }
	auto GetFleeDistance() { return Precision(m_fFleeDistance); }
	auto GetHeadingChange() { return Precision(m_fHeadingChange); }
#else
	/*
	 * In VCS, this is the same case, but since we don't store any floats from PED.DAT,
	 * the ped type flag is set to 0. If that's the case, we can "declate" the ped type invalid.
	 */
	bool IsValid() { return m_nFlag != 0; }
	auto GetWalkSpeed() { return "2.0"; }
	auto GetRunSpeed() { return m_nFlag == PED_FLAG_COP ? "2.0" : "6.0"; }
	auto GetFastRunSpeed() { return m_nFlag == PED_FLAG_COP ? "2.0" : "6.0"; }
	auto GetHeadingChange() { return m_nFlag < PED_FLAG_CIVMALE ? "15.0" : "7.5"; }
	auto GetFleeDistance()
	{
		if (m_nFlag < PED_FLAG_CIVMALE)
			return "0.0";
		if (m_nFlag == PED_FLAG_COP || m_nFlag == PED_FLAG_EMERGENCY)
			return "20.0";
		return "17.0";
	}
#endif
	uint32 GetThreats() { return m_nThreats; }
	uint32 GetAvoid() { return m_nAvoid; }
};