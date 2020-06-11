#pragma once
#include "Common.h"
#include "Entities.h"

template<typename T>
class CPool final
{
private:
	T* m_entries;
	union
	{
		struct
		{
			uint8 id : 7;
			uint8 free : 1;
		};
		uint8 u;
	} *m_flags;
	int32 m_size;
	int32 m_allocPtr;
#if defined VCS || defined PS2
	char  m_name[16];
#else
	template<typename, typename>
	inline static constexpr bool compare_types = false;
	template<typename T>
	inline static constexpr bool compare_types<T, T> = true;
#endif

public:
	int32 GetSize() { return m_size; }
	T* GetSlot(int32 index) { return m_flags[index].free ? nullptr : m_entries + index; }
	const char* GetName()
	{
		/* Magic O_o */
#if defined VCS || defined PS2
		return m_name;
#else
		if constexpr (compare_types<T, CBuilding>)
			return "Buildings";
		else if constexpr (compare_types<T, CTreadable>)
			return "Treadables";
		else
			return "Dummys";
#endif
	}
};

class CPtrNode;
class CEntryInfoNode;

typedef CPool<CBuilding>      CBuildingPool;
typedef CPool<CTreadable>     CTreadablePool;
typedef CPool<CDummy>         CDummyPool;
typedef CPool<CPtrNode>       CPtrNodePool;
typedef CPool<CEntryInfoNode> CEntryInfoNodePool;

class CPools final
{
private:
	inline static CBuildingPool      *ms_pBuildingPool;
	inline static CTreadablePool     *ms_pTreadablePool;
	inline static CDummyPool         *ms_pDummyPool;
	inline static CEntryInfoNodePool *ms_pEntryInfoNodePool;
	inline static CPtrNodePool       *ms_pPtrNodePool;

public:
	static void LoadPool(CBuildingPool      *pool) { ms_pBuildingPool      = pool; }
	static void LoadPool(CTreadablePool     *pool) { ms_pTreadablePool     = pool; }
	static void LoadPool(CDummyPool         *pool) { ms_pDummyPool         = pool; }
	static void LoadPool(CEntryInfoNodePool *pool) { ms_pEntryInfoNodePool = pool; }
	static void LoadPool(CPtrNodePool       *pool) { ms_pPtrNodePool       = pool; }

	static auto GetBuildingPool()      { return ms_pBuildingPool;      }
	static auto GetTreadablePool()     { return ms_pTreadablePool;     }
	static auto GetDummyPool()         { return ms_pDummyPool;         }
	static auto GetEntryInfoNodePool() { return ms_pEntryInfoNodePool; }
	static auto GetPtrNodePool()       { return ms_pPtrNodePool;       }
};