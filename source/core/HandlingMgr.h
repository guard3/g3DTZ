#pragma once
#include "Common.h"
#include "Maths.h"
#include "Utils.h"

class CTransmission final
{
private:
	struct tGear
	{
		float fMaxVelocity;
		float fShiftUpVelocity;
		float fShiftDownVelocity;
	};

	tGear m_gears[6]; // Reverse - 1 - 2 - 3 - 4 - 5
#ifdef LCS
	char  nDriveType;
	char  nEngineType;
	uint8 nNumberOfGears;
	uint8 flags;
#endif
	float fEngineAcceleration;
	float fEngineInertia;
	float fMaxVelocity;        // fMaxVelocity = fMaxAIVelocity * 1.2
	float fMaxAIVelocity;      // max velocity devided by 180, minus some multiple of 0.01
	float fMaxReverseVelocity; // -0.2 for cars, -0.05 for bikes, -fMaxVelocity for rc bandit
#ifdef VCS
	char  nDriveType;
	char  nEngineType;
	uint8 nNumberOfGears;
	uint8 flags;
#endif

public:
	int         GetNumberOfGears()      { return nNumberOfGears; }
	const char* GetEngineAcceleration() { return Precision(fEngineAcceleration * (nDriveType == '4' ? 25000.0f : 12500.0f)); }
	const char* GetEngineInertia()      { return Precision(fEngineInertia); }
	char        GetDriveType()          { return nDriveType;     }
	char        GetEngineType()         { return nEngineType;    }
	const char* GetMaxVelocity();
};

class CHandlingData final
{
private:
	friend class CTransmission;

#ifdef LCS
	float     fMass;
	float     fTurnMass;
	float     fTractionMultiplier;
	float     fCollisionDamageMultiplier;
	int32     nIdentifier; // Handling ID
	float     fInvMass;    // fInvMass = 1 / fMass
	float     fDragMult;
	uint8     padding[4];  // padding for CVuVector... maybe?
	CVuVector centreOfMass;
	int8      nPercentSubmerged;
	float     fBuoyancy;   // fBuoyancy = fMass * 0.8 / nPercentSubmerged
#endif
public:
	CTransmission transmission;
private:
#ifdef LCS
	float unk2;
#endif
	float fBrakeDeceleration;
	float fBrakeBias;
#ifdef LCS
	bool  bABS;
#endif
	float fSteeringLock;
	float fTractionLoss;
	float fTractionBias;
#ifdef LCS
	float unk3;
#endif
	float fSuspensionForceLevel;
	float fSuspensionDampingLevel;
	float fSuspensionUpperLimit;
	float fSuspensionLowerLimit;
	float fSuspensionBias;
	float fSuspensionAntiDiveMultiplier;
#ifdef LCS
	uint32 modelFlags;
#endif
	float fSeatOffsetDistance;
	int32 nMonetaryValue;
	int8  frontLights;
	int8  rearLights;
#ifdef LCS
	uint8 padding2[18];
#else
	float fDragMult;
	char padding[4]; //Padding for Vector4D
	CVuVector centreOfMass;
	int32 nPercentSubmerged; //Direct copy of the value from the original ASCII file
	float fBuoyancy; //Value actually used by the game; = mass * 0.8 / percentSubmerged_file
	float fMaxVelocity; // The HANDLING.CFG value
	float fMass;
	float fTurnMass;
	float fTractionMultiplier;
	float fCollisionDamageMultiplier;
	uint32 handlingFlags;
	uint32 modelFlags;
	uint8 padding2[12];
#endif

public:
	const char* GetMass()               { return Precision(fMass); }
	const char* GetTurnMass()           { return Precision(fTurnMass); }
	const char* GetDragMult()           { return Precision(fDragMult); }
	const char* GetCentreOfMassX()      { return Precision(centreOfMass.x); }
	const char* GetCentreOfMassY()      { return Precision(centreOfMass.y); }
	const char* GetCentreOfMassZ()      { return Precision(centreOfMass.z); }
	int         GetPercentSubmerged()   { return nPercentSubmerged; }
	const char* GetTractionMultiplier() { return Precision(fTractionMultiplier); }
	const char* GetTractionLoss()       { return Precision(fTractionLoss); }
	const char* GetTractionBias()       { return Precision(fTractionBias); }
	const char* GetBrakeDeceleration()  { return Precision(fBrakeDeceleration * 2500.0f); }
	const char* GetBrakeBias()          { return Precision(fBrakeBias); }
	const char* GetSteeringLock()       { return Precision(fSteeringLock); }
	const char* GetSuspensionForceLevel()   { return Precision(fSuspensionForceLevel); }
	const char* GetSuspensionDampingLevel() { return Precision(fSuspensionDampingLevel); }
	const char* GetSuspensionUpperLimit()   { return Precision(fSuspensionUpperLimit); }
	const char* GetSuspensionLowerLimit()   { return Precision(fSuspensionLowerLimit); }
	const char* GetSuspensionBias()         { return Precision(fSuspensionBias); }
	const char* GetSuspensionAntiDiveMultiplier() { return Precision(fSuspensionAntiDiveMultiplier); }
	const char* GetSeatOffsetDistance()           { return Precision(fSeatOffsetDistance); }
	const char* GetCollisionDamageMultiplier()    { return Precision(fCollisionDamageMultiplier * fMass * 0.0005f); }
	int32       GetMonetaryValue()                { return nMonetaryValue; }
	char        GetFrontLights()                  { return '0' + frontLights; }
	char        GetRearLights()                   { return '0' + rearLights; }

	const char* GetModelFlags();

#ifdef LCS
	char GetABS() { return '0' + bABS; }
	const char* GetHandlingName();
	const char* GetSuspensionHighSpdComDamp();
#else
	/* bABS seems to not exist in VCS, so we'll just return 0 */
	char GetABS() { return '0'; }
	/* fSuspensionHighSpdComDamp is ignored when parsing the file, so we just print out 0.0 */
	const char* GetSuspensionHighSpdComDamp() { return "0.0"; }

	const char* GetHandlingFlags();
#endif
};

class CHandlingFlying final
{
private:
#ifdef LCS
	int32 nIdentifier;
#endif
	float fThrust;
	float fThrustFallOff;
	float fYaw;
	float fYawStab;
	float fSideSlip;
	float fRoll;
	float fRollStab;
	float fPitch;
	float fPitchStab;
	float fFormLift;
	float fAttackLift;
	float fMoveRes;
#ifdef LCS
	uint8 padding[12]; // Padding for CVuVector
#endif
	CVuVector turnRes;
	CVuVector speedRes;
	char padding2[16]; //Padding for... no reason?

public:
	const char* GetThrust()        { return Precision3(fThrust);    }
	float       GetThrustFallOff() { return fThrustFallOff;         }
	float       GetYaw()           { return fYaw;                   }
	float       GetYawStab()       { return fYawStab;               }
	float       GetSideSlip()      { return fSideSlip;              }
	float       GetRoll()          { return fRoll;                  }
	const char* GetRollStab()      { return Precision3(fRollStab);  }
	float       GetPitch()         { return fPitch;                 }
	const char* GetPitchStab()     { return Precision3(fPitchStab); }
	const char* GetFormLift()      { return Precision3(fFormLift);  }
	float       GetAttackLift()    { return fAttackLift;            }
	const char* GetMoveRes()       { return Precision3(fMoveRes);   }
	const char* GetTurnResX()      { return Precision3(turnRes.x);  }
	const char* GetTurnResY()      { return Precision3(turnRes.y);  }
	const char* GetTurnResZ()      { return Precision3(turnRes.z);  }
	const char* GetSpeedResX()     { return Precision(speedRes.x);  }
	const char* GetSpeedResY()     { return Precision(speedRes.y);  }
	const char* GetSpeedResZ()     { return Precision(speedRes.z);  }
#ifdef LCS
	const char* GetHandlingName();
#endif
};

class CHandlingBike final
{
private:
#ifdef LCS
	int32 nIdentifier;
#endif
	float fLeanFwdCOM;
	float fLeanFwdForce;
	float fLeanBakCOM;
	float fLeanBackForce;
	float fMaxLean;
	float fFullAnimLean;
	float fDesLean;
	float fSpeedSteer;
	float fSlipSteer;
	float fNoPlayerCOMz;
	float fWheelieAng;
	float fStoppieAng;
	float fWheelieSteer;
	float fWheelieStabMult;
	float fStoppieStabMult;
	float unk; // Padding?

public:
	const char* GetLeanFwdCOM()      { return Precision3(fLeanFwdCOM);     }
	const char* GetLeanFwdForce()    { return Precision3(fLeanFwdForce);   }
	const char* GetLeanBakCOM()      { return Precision3(fLeanBakCOM);     }
	const char* GetLeanBackForce()   { return Precision3(fLeanBackForce);  }
	const char* GetDesLean()         { return Precision3(fDesLean);        }
	const char* GetSpeedSteer()      { return Precision(fSpeedSteer);      }
	const char* GetSlipSteer()       { return Precision(fSlipSteer);       }
	const char* GetNoPlayerCOMz()    { return Precision(fNoPlayerCOMz);    }
	const char* GetWheelieSteer()    { return Precision3(fWheelieSteer);   }
	const char* GetWheelieStabMult() { return Precision(fWheelieStabMult); }
	const char* GetStoppieStabMult() { return Precision(fStoppieStabMult); }
#ifdef LCS
	const char* GetHandlingName();
#endif
	const char* GetMaxLean();
	const char* GetFullAnimLean();
	const char* GetWheelieAng();
	const char* GetStoppieAng();
};

class CHandlingBoat final
{
private:
#ifdef LCS
	int32 nIdentifier;
#endif
	float fThrustY;
	float fThrustZ;
	float fThrustAppZ;
	float fAqPlaneForce;
	float fAqPlaneLimit;
	float fAqPlaneOffset;
	float fWaveAudioMult;
	float fLook_L_R_BehindCamHeight;
#ifdef LCS
	uint8 padding[12]; // Padding for CVuVector
#endif
	CVuVector moveRes;
	CVuVector turnRes;
	float     unk[4];  // All 0 in LCS (padding?), in VCS usually values { 0.75, 0.9, 0.75, 0.95 } (???)

public:
	const char* GetThrustY()         { return Precision(fThrustY);       }
	const char* GetThrustZ()         { return Precision(fThrustZ);       }
	const char* GetThrustAppZ()      { return Precision(fThrustAppZ);    }
	const char* GetAqPlaneForce()    { return Precision(fAqPlaneForce);  }
	const char* GetAqPlaneLimit()    { return Precision(fAqPlaneLimit);  }
	const char* GetAqPlaneOffset()   { return Precision(fAqPlaneOffset); }
	const char* GetWaveAudioMult()   { return Precision(fWaveAudioMult); }
	const char* GetBehindCamHeight() { return Precision(fLook_L_R_BehindCamHeight); }
	const char* GetMoveResX()        { return Precision3(moveRes.x); }
	const char* GetMoveResY()        { return Precision3(moveRes.y); }
	const char* GetMoveResZ()        { return Precision3(moveRes.z); }
	const char* GetTurnResX()        { return Precision3(turnRes.x); }
	const char* GetTurnResY()        { return Precision3(turnRes.y); }
	const char* GetTurnResZ()        { return Precision3(turnRes.z); }
#ifdef LCS
	const char* GetHandlingName();
#endif
};

#ifdef LCS
class CHandlingDataMgr final
{
public:
	static constexpr int
		NUM_HANDLING_DATA   = 81,
		NUM_HANDLING_BIKE   = 7,
		NUM_HANDLING_FLYING = 6,
		NUM_HANDLING_BOAT   = 3;

private:
	float           unk[8];              // 5 floats + padding
	CHandlingData   m_handlingData[81];  // General handlings
	CHandlingBike   m_handlingBike[7];   // Bike handlings
	uint8           padding[4];          //
	CHandlingFlying m_handlingFlying[6]; // Flying handlings
	CHandlingBoat   m_handlingBoat[3];   // Boat handlings

	inline static CHandlingDataMgr* inst;

public:
	static void Load(CHandlingDataMgr* mgr) { inst = mgr; }

	static CHandlingData   &GetHandlingData(int index)   { return inst->m_handlingData[index];   }
	static CHandlingBike   &GetHandlingBike(int index)   { return inst->m_handlingBike[index];   }
	static CHandlingFlying &GetHandlingFlying(int index) { return inst->m_handlingFlying[index]; }
	static CHandlingBoat   &GetHandlingBoat(int index)   { return inst->m_handlingBoat[index];   }
};
#else
inline const char* CTransmission::GetMaxVelocity() { return Precision(reinterpret_cast<CHandlingData*>(this)->fMaxVelocity); }
#endif