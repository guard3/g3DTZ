#pragma once
#include "Common.h"
#include "Maths.h"
#include "Utils.h"

class CAttributeZone final
{
private:
	int16 x1;
	int16 x2;
	int16 y1;
	int16 y2;
	int16 z1;
	int16 z2;
	int16 attribute;
	int16 wantedLevel;

public:
	const char* GetPositionX() { return Precision((static_cast<float>(x1) + static_cast<float>(x2)) * 0.5f); }
	const char* GetPositionY() { return Precision((static_cast<float>(y1) + static_cast<float>(y2)) * 0.5f); }
	const char* GetPositionZ() { return Precision((static_cast<float>(z1) + static_cast<float>(z2)) * 0.5f); }
	int GetLowPointX()   { return x1;          }
	int GetLowPointY()   { return y1;          }
	int GetLowPointZ()   { return z1;          }
	int GetHighPointX()  { return x2;          }
	int GetHighPointY()  { return y2;          }
	int GetHighPointZ()  { return z2;          }
	int GetAttribute()   { return attribute;   }
	int GetWantedLevel() { return wantedLevel; }
};

class CCullZones final
{
private:
	inline static int             ms_numAttributeZones;
	inline static CAttributeZone* ms_aAttributeZones;

public:
	static void Init(int numAttrZones, CAttributeZone* attrZones)
	{
		ms_numAttributeZones = numAttrZones;
		ms_aAttributeZones   = attrZones;
	}
	static auto GetNumAttributeZones() { return ms_numAttributeZones; }
	static auto GetAttributeZone(int index) { return ms_aAttributeZones + index; }
};