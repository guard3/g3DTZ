#pragma once
#include "Maths.h"

class CZone final
{
public:
	char    name[8];
	CVector min;
	CVector max;
	int32   type;
	int32   level;
	int16   zoneinfoDay;
	int16   zoneinfoNight;
	CZone  *child;
	CZone  *parent;
	CZone  *next;
};

class CZoneInfo;

class CTheZones
{
public:
	int32 m_CurrLevel;
#ifdef LCS
	int32 FindIndex;
#else
	int32 unk[2];
#endif
	CZone     *NavigationZoneArray;
	CZone     *InfoZoneArray;
	CZoneInfo *ZoneInfoArray;
	int16      TotalNumberOfNavigationZones;
	int16      TotalNumberOfInfoZones;
	int16      TotalNumberOfZoneInfos;
	CZone     *MapZoneArray;
	int16      AudioZoneArray[36];
	int16      TotalNumberOfMapZones;
	int16      NumberOfAudioZones;
};

inline CTheZones* gpTheZones;