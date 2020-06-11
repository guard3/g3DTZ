#pragma once
#include "Common.h"
#include "2dEffect.h"
#include "ObjectData.h"
#include "RslEngine.h"
#include "Utils.h"

#pragma warning(disable: 26812)

#ifdef VCS
extern RslRGB(*gpColourTable)[128];
#endif

enum eModelInfoType : uint8
{
	MITYPE_NA,
	MITYPE_SIMPLE,
	MITYPE_MLO,
	MITYPE_TIME,
	MITYPE_WEAPON,
	MITYPE_CLUMP,
	MITYPE_VEHICLE,
	MITYPE_PED,
	MITYPE_XTRACOMPS,
};

class CColModel;

class CBaseModelInfo
{
protected:
	char            unknown[8];  // all zero
	uint32          m_hashname;
	RslObject      *m_rslObject; //pointer to model chunk (filled at runtime)
	eModelInfoType  m_type;
	uint8           m_num2dEffects;
	bool            m_bOwnsColModel;
	CColModel      *m_colModel;
	int16           m_first2dEffect;
	int16           m_objectId;
	int16           m_refCount;
	int16           m_texlistSlot;
#ifdef VCS
	int16           unkId; // Some id, no idea what it's referencing
#endif
	void           *vtable;

public:
	eModelInfoType GetType()         { return m_type;         }
	int            GetNum2dEffects() { return m_num2dEffects; }
	const char    *GetModelName();
	const char    *GetTexListName();
	C2dEffect     *Get2dEffects();
	CObjectInfo   *GetObjectInfo();
};

class CSimpleModelInfo : public CBaseModelInfo
{
protected:
	RslObject       **m_objects;
	float             m_lodDistances[3];
	uint8             m_numObjects;
	uint16            m_flags;
	CSimpleModelInfo *m_relatedObject;

public:
	float GetLodDistance(int i) { return m_lodDistances[i]; }
	int   GetNumObjects()       { return m_numObjects;      }
	int   GetFlags()            { return ((m_flags >> 2) & 1) | ((m_flags & 0xFFE0) >> 4); }
};

class CTimeModelInfo final : public CSimpleModelInfo
{
private:
	int32 m_timeOn;
	int32 m_timeOff;
	int16 m_otherTimeModelID;

public:
	int GetTimeOn() { return m_timeOn; }  
	int GetTimeOff() { return m_timeOff; }
};

class CWeaponModelInfo final : public CSimpleModelInfo
{
private:
	// m_relatedObject is "int32 weaponType"
	int32 m_animBlockId;

public:
	int         GetWeaponType() { return reinterpret_cast<int32&>(m_relatedObject); }
	const char* GetAnimBlockName();
};

class CElementGroupModelInfo : public CBaseModelInfo
{
protected:
	void* m_pElementGroup;
	int   m_animGroupId;
};

class CHandlingData;
class CHandlingBike;
class CHandlingFlying;
class CHandlingBoat;
class CHandlingJetski;
class CHandling6atv;

enum eVehicleType : int32
{
	VEHICLE_TYPE_CAR,
	VEHICLE_TYPE_BOAT,
#ifdef VCS
	VEHICLE_TYPE_JETSKI,
#endif
	VEHICLE_TYPE_TRAIN,
	VEHICLE_TYPE_HELI,
	VEHICLE_TYPE_PLANE,
	VEHICLE_TYPE_BIKE,
#ifdef VCS
	VEHICLE_TYPE_BMX,
	VEHICLE_TYPE_QUAD
#endif
};

class CVehicleModelInfo final : public CElementGroupModelInfo
{
private:
#ifdef LCS
	uint8        m_lastColour1;
	uint8        m_lastColour2;
	char         m_gameName[8];
	eVehicleType m_vehicleType;
	float        m_wheelScale;
	union
	{
		int16 m_wheelId;
		int16 m_planeLodId;
	};
	int16        m_handlingId;
	uint8        m_numDoors;
	int8         m_vehicleClass;
	uint8        m_level;
	uint8        numExtras;
	uint16       m_frequency;
	uint8        padding[4];     // padding for CVuVector
	CVuVector    m_positions[5]; // dummy positions
	uint32       m_compRules;
	float        m_bikeSteerAngle;
	RslMaterial *m_materials1[25];
	RslMaterial *m_materials2[25];
	uint8        m_colours1[8];  // Primary colour IDs
	uint8        m_colours2[8];  // Secondary colour IDs
	uint8        m_numColours;
	uint8        m_lastColourVariation;
	uint8        m_currentColour1;
	uint8        m_currentColour2;
	float        m_normalSplay;  // How much the normals are splayed by to improve the environment mapping on PSP
	void       **extras;
	int32        m_animBlockId;

	/* For LCS we also have a static instance of CVehicleModelInfo*/
	struct inst
	{
		void*   unk; // probably ms_pEnvironmentMaps; nullptr even while the game is running...
		RslRGBA vehicleColourTable[256];
		int8    compsUsed[2];
		int8    compsToUse[2];
	};
	static inst* mspInfo;

public:
	static RslRGBA* GetColourFromTable(int index) { return mspInfo->vehicleColourTable + index; }
	int GetColour1(int index) { return m_colours1[index]; }
	int GetColour2(int index) { return m_colours2[index]; }
#else
	/*
	still looking for:
	uint8 m_numExtras;
	*/
	char             unk0[8];
	CHandlingData   *m_pHandlingData;
	CHandlingBike   *m_pHandlingBike;
	CHandlingFlying *m_pHandlingFlying;
	CHandlingBoat   *m_pHandlingBoat;
	CHandlingJetski *m_pHandlingJetski;
	CHandling6atv   *m_pHandling6atv;
	float            m_normalSplay;   // How much the normals are splayed by to improve the environment mapping on PSP
	eVehicleType     m_vehicleType;
	float            m_wheelScale;
	float            m_wheelScaleRear;
	CVuVector        m_aDummyPos[15];
	uint32           m_compRules;
	float            m_bikeSteerAngle;
	char             m_gameName[8];   // GXT Name
	uint8            unk2;            // lastColour, numExtras (???)
	uint8            m_numColours;
	uint8            unk3;            // Maybe numUnkTable
	int8             m_colours[8][2]; // Colour IDs
	char             unk4[25];        // Maybe there's a "xxx by 2" table in there, similar to peds' one, unknown purpose
	RslMaterial     *m_materials1[30];
	RslMaterial     *m_materials2[25];
	void           **extras;
	int              m_animBlockId;
	union
	{
		int16 m_wheelId;
		int16 m_planeLodId;
	};
	uint16           m_frequency;
	uint8            m_numDoors;
	int8             m_vehicleClass;
	uint8            m_level;
	char             unk5[13];
	int32            engineFarSample;  // *
	int32            engineNearSample; // *
	int32            hornSample;       // *
	int32            hornFrequency;    // * Vehicle sound info, not hardcoded in VCS???
	int32            sirenSample;      // *
	int32            sirenFrequency;   // *
	int32            unk6;             // *

public:
	CHandlingData   *GetHandlingData()   { return m_pHandlingData;             }
	CHandlingBike   *GetHandlingBike()   { return m_pHandlingBike;             }
	CHandlingBoat   *GetHandlingBoat()   { return m_pHandlingBoat;             }
	CHandlingFlying *GetHandlingFlying() { return m_pHandlingFlying;           }
	const char      *GetWheelScaleRear() { return Precision(m_wheelScaleRear); }
	int8(*GetColours())[2]{ return m_colours; }
#endif
	const char*  GetGameName()       { return m_gameName;              }
	float        GetNormalSplay()    { return m_normalSplay;           }
	int          GetFrequency()      { return m_frequency;             }
	int          GetLevel()          { return m_level;                 }
	uint32       GetCompRules()      { return m_compRules;             }
	int          GetWheelId()        { return m_wheelId;               }
	float        GetBikeSteerAngle() { return m_bikeSteerAngle;        }
	int          GetPlaneLodId()     { return m_planeLodId;            }
	const char*  GetWheelScale()     { return Precision(m_wheelScale); }
	int          GetNumColours()     { return m_numColours;            }
	eVehicleType GetVehicleType()   { return m_vehicleType;           }
	const char*  GetVehicleTypeName();
	const char*  GetAnimBlockName();
	const char*  GetVehicleClass();

#ifdef LCS
	static void Load(void* vehicleModelInfoInst) { mspInfo = reinterpret_cast<inst*>(vehicleModelInfoInst); }
	const char* GetHandlingName();
#else
	static void Load(void*) {}
	const char* GetHandlingName() { return "HANDLING"; }
#endif

};

class CPedModelInfo final : public CElementGroupModelInfo
{
private:
	uint32     m_animGroup;
	int32      m_pedType;
	int32      m_pedStatType;
	uint32     m_carsCanDrive;
	CColModel* m_hitColModel;
	int8       m_radio1;
	int8       m_radio2;
#ifdef VCS            //Many unknowns, wouldn't be surprised if there's audio info somewhere
	uint8 unk1;
	uint8 m_numColours;
	uint8 m_numUnkTable;
	uint8 m_colours[16][4];
	uint8 m_unkTable[4][4]; // That's definetly wrong, must check with cars and in-game
	char unk2[27];
	struct {          // *
		void* mat;    // * Weird editable materials, filled at runtime
		int32 numX;   // *
	} materials[6];   // *
	char gameName[8]; // Maybe a game name equivalent, but for peds (???), same as the model name though
	uint32 unk3;      // 0x31 for many peds
	uint32 unk4;
	uint32 unk5;      // always 0x7ffe9f0, even at runtime
	uint32 unk6;      // always 0

public:
	int GetNumColours() { return m_numColours; }
	uint8(&GetColours())[16][4] { return m_colours; }
#endif
public:
	uint32 GetCarsCanDriveMask() { return m_carsCanDrive; }
	int    GetRadio1()           { return m_radio1;       }
	int    GetRadio2()           { return m_radio2;       }
	const char* GetAnimGroup();
	const char* GetAnimBlock();
	const char* GetPedType();
	const char* GetPedStatType();
};

class CModelInfo final
{
	friend class CBaseModelInfo;
private:
	static CBaseModelInfo **ms_modelInfoPtrs;
	static uint32           ms_numModelInfos;
	static C2dEffect       *ms_2dEffects;    //
	static uint32           ms_num2dEffects; // Not original names

public:
	static void Load(uint32 numModelInfos, CBaseModelInfo** modelInfoPtrs)
	{
		ms_modelInfoPtrs = modelInfoPtrs;
		ms_numModelInfos = numModelInfos;
	}
	static void Load2dEffects(uint32 num2dEffects, C2dEffect* _2dEffects)
	{
		ms_2dEffects    = _2dEffects;
		ms_num2dEffects = num2dEffects;
	}

	static auto GetModelInfo(uint32 id) { return ms_modelInfoPtrs[id]; }
	static auto GetNumModelInfos() { return ms_numModelInfos; }
};