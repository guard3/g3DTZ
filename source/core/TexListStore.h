#pragma once
#include "RslEngine.h"
#include "Pools.h"

class TexListDef final
{
private:
	RslTexList* m_texList;
	int32       m_refCount;
	char        m_name[20];

public:
	inline const char* GetName() { return m_name; }
};

class CTexListStore final
{
private:
	inline static CPool<TexListDef> *ms_pTexListPool;
	inline static RslTexList        *ms_pStoredTexList;

public:
	static void Load(RslTexList* storedTexList, CPool<TexListDef>* texListPool)
	{
		ms_pTexListPool   = texListPool;
		ms_pStoredTexList = storedTexList;
	}

	static TexListDef* GetSlot(int index) { return ms_pTexListPool->GetSlot(index); }
	static int         GetSize()          { return ms_pTexListPool->GetSize();      }
};