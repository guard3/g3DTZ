#pragma once
#include "Common.h"
#include "Pools.h"

class ColDef final
{
private:
#ifdef LCS
	void* unk;
	bool  m_bIsLoaded;
	CRect m_rect;
	char  m_name[20];
	int16 m_firstIndex;
	int16 m_lastIndex;
#else
	void* unk;
	bool  m_bIsLoaded;
	CRect m_rect;
	CRect m_rect2;
	char  m_name[20];
	int32 m_firstIndex;
	int32 m_lastIndex;
#endif
	void* chk; // Pointer to relocatable chunk

public:
	const char* GetName()       { return m_name;       }
	int         GetFirstIndex() { return m_firstIndex; }
	int         GetLastIndex()  { return m_lastIndex;  }
};

class CColStore final
{
private:
	inline static CPool<ColDef>* ms_pColPool;
	inline static bool           m_onlyBB;

public:
	static void Load(bool onlyBB, CPool<ColDef>* colPool)
	{
		ms_pColPool = colPool;
		m_onlyBB    = onlyBB;
	}
	static ColDef* GetSlot(int index) { return ms_pColPool->GetSlot(index); }
	static int32   GetSize()          { return ms_pColPool->GetSize();      }
};