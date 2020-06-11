#pragma once
#include "Common.h"
#include "Utils.h"

class CPedStats final
{
private:
#ifdef LCS
	int32 m_type;
	char  m_name[24];
	float m_fleeDistance;
	float m_headingChangeRate;
	int8  m_fear;
	int8  m_temper;
	int8  m_lawfulness;
	int8  m_sexiness;
	float m_attackStrength;
	float m_defendWeakness;
	int16 m_flags;
#else
	int32 m_type;
	float m_fleeDistance;
	float m_headingChangeRate;
	float m_attackStrength;
	float m_defendWeakness;
	int16 m_flags;
	int8  m_fear;
	int8  m_temper;
	int8  m_lawfulness;
	int8  m_sexiness;
	char  m_name[24];
#endif
	inline static CPedStats** ms_apPedStats;

public:
	static void       Load(CPedStats** stats) { ms_apPedStats = stats;       }
	static CPedStats* GetPedStats(int index)  { return ms_apPedStats[index]; }

	const char* GetName()              { return m_name;                         }
	const char* GetFleeDistance()      { return Precision(m_fleeDistance);      }
	const char* GetHeadingChangeRate() { return Precision(m_headingChangeRate); }
	int         GetFear()              { return m_fear;                         }
	int         GetTemper()            { return m_temper;                       }
	int         GetLawfulness()        { return m_lawfulness;                   }
	int         GetSexiness()          { return m_sexiness;                     }
	const char* GetAttackStrength()    { return Precision(m_attackStrength);    }
	const char* GetDefendWeakness()    { return Precision(m_defendWeakness);    }
	int         GetFlags()             { return m_flags;                        }
};