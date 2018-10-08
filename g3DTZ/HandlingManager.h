/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	HandlingManager.h - Structs about handing.cfg
*/

//TODO: check the padding at the end in the vcs version
//TODO: document jetski and 6atv handling

#pragma once
#include "typedef.h"
#include "Vector.h"

const char* handlingNames_lcs[] = {
	"LANDSTAL",
	"IDAHO",
	"STINGER",
	"LINERUN",
	"PEREN",
	"SENTINEL",
	"PATRIOT",
	"FIRETRUK",
	"TRASH",
	"STRETCH",
	"MANANA",
	"INFERNUS",
	"PONY",
	"MULE",
	"CHEETAH",
	"AMBULAN",
	"FBICAR",
	"MOONBEAM",
	"ESPERANT",
	"TAXI",
	"KURUMA",
	"BOBCAT",
	"MRWHOOP",
	"BFINJECT",
	"POLICE",
	"ENFORCER",
	"SECURICA",
	"BANSHEE",
	"BUS",
	"RHINO",
	"BARRACKS",
	"TRAIN",
	"FERRY",
	"HELI",
	"DODO",
	"COACH",
	"CABBIE",
	"STALLION",
	"RUMPO",
	"RCBANDIT",
	"MAFIA",
	"AIRTRAIN",
	"DEADDODO",
	"FLATBED",
	"YANKEE",
	"BLISTA",
	"BELLYUP",
	"MRWONGS",
	"YARDIE",
	"YAKUZA",
	"DIABLOS",
	"COLUMB",
	"HOODS",
	"PANLANT",
	"BORGNINE",
	"CAMPVAN",
	"BALLOT",
	"SPIDER",
	"SHELBY",
	"PONTIAC",
	"ESPRIT",
	"MINI",
	"HOTROD",
	"SINDACCO",
	"FORELLI",
	"BIKE",
	"MOPED",
	"DIRTBIKE",
	"ANGEL",
	"DIRTBIK2",
	"ANGE2",
	"FREEWAY",
	"PREDATOR",
	"SPEEDER",
	"REEFER",
	"MAVERICK",
	"COASTMAV",
	"POLMAV",
	"HUNTER",
	"RCGOBLIN",
	"RCCOPTER",
};

struct Gear
{
	float unk1, unk2, unk3;
};

struct Transmission
{
#ifdef lcs
	char	driveType;
	char	engineType;
	uint8	numGears;
#endif
	float	engineAcceleration; //engineAcceleration * 2500 * 5 (*2  for 4wd)
	float	engineInertia;
	float	maxVelocity;		//fMaxVelocity = fMaxVelocity * 180.0 <- is this right???
	float	unk1;				// fMaxVelocity / 1.2;
	float	unk2;				//-0.2 for cars, -0.05 for bikes
#ifdef vcs
	char	driveType;
	char	engineType;
	uint8	numGears;
#endif
};

/*
Unknowns so far
MaxVelocity: dunno how to get actual value
SuspensionHighSpdComDamp: dunno where the damn value is
ABS: no idea, especially for VCS
*/

struct GeneralHandling
{
#ifdef lcs
	float			mass;
	float			turnMass;
	float			tractionMultiplier;
	float			collisionDamageMultiplier;
	int32			handlingIndex;
	float			unk1;					// 1/fMass
	float			dragMult;
	char			padding[4];				//Padding for Vector4D
	Vector4D		centreOfMass;
	int32			percentSubmerged_file;	//Direct copy of the value from the original ASCII file
	float			percentSubmerged;		//Value actually used by the game; = mass * 0.8 / percentSubmerged_file
#endif
	Gear			gears[6];				//Reverse - 1 - 2 - 3 - 4 - 5
	Transmission	transmission;
#ifdef lcs
	float			unk2;
#endif
	float			brakeDeceleration;
	float			brakeBias;
#ifdef lcs
	float			bABS;					//this must be wrong, like 100%
#endif
	float			steeringLock;
	float			tractionLoss;
	float			tractionBias;
#ifdef lcs
	float			unk3;
#endif
	float			suspensionForceLevel;
	float			suspensionDampingLevel;
	float			suspensionUpperLimit;
	float			suspensionLowerLimit;
	float			suspensionBias;
	float			suspensionAntiDive;
#ifdef lcs
	uint32			flags;
#endif
	float			seatOffsetDistance;
	int32			monetaryValue;
	uint8			frontLights;
	uint8			rearLights;
#ifdef lcs
	char			padding2[18];
#else
	float			dragMult;
	char			padding[4];				//Padding for Vector4D
	Vector4D		centreOfMass;
	int32			percentSubmerged_file;	//Direct copy of the value from the original ASCII file
	float			percentSubmerged;		//Value actually used by the game; = mass * 0.8 / percentSubmerged_file
	float			maxVelocity_file;		//Direct copy of the value from the original ASCII file
	float			mass;
	float			turnMass;
	float			tractionMultiplier;
	float			collisionDamageMultiplier;
	uint32			handlingFlags;
	uint32			modelFlags;
	char			padding2[12];
#endif
};

struct BikeHandling
{
#ifdef lcs
	uint32	handlingIndex;
#endif
	float	leanFwdCOM;
	float	leanFwdForce;
	float	leanBakCOM;
	float	leanBackForce;
	float	maxLean;		//sine
	float	fullAnimLean;	//sine
	float	desLean;
	float	speedSteer;
	float	slipSteer;
	float	noPlayerCOMz;
	float	wheelieAng;		//sine
	float	stoppieAng;		//sine
	float	wheelieSteer;
	float	wheelieStabMult;
	float	stoppieStabMult;
	float	unk;			//Padding for... no reason?
};

struct PlaneHandling
{
#ifdef lcs
	uint32		handlingIndex;
#endif
	float		thrust;
	float		thrustFallOff;
	float		yaw;
	float		yawStab;
	float		sideSlip;
	float		roll;
	float		rollStab;
	float		pitch;
	float		pitchStab;
	float		formLift;
	float		attackLift;
	float		moveRes;
#ifdef lcs
	char		padding[12];	//Padding for Vector4D
#endif
	Vector4D	turnRes;
	Vector4D	speedRes;
	char		padding2[16];	//Padding for... no reason?
};

struct BoatHandling
{
#ifdef lcs
	uint32		handlingIndex;
#endif
	float		thrustY;
	float		thrustZ;
	float		thrustAppZ;
	float		aqPlaneForce;
	float		aqPlaneLimit;
	float		aqPlaneOffset;
	float		waveAudioMult;
	float		behindCamHeight;
#ifdef lcs
	char		padding[12];	//Padding for Vector4D
#endif
	Vector4D	moveRes;
	Vector4D	turnRes;
	char		padding2[16];	//Padding for... no reason? - not the case with vcs, have to check
};

struct HandlingManager
{
	float			unk[8];					//Probably 5 floats (unknown) + 12b padding for general handling
	GeneralHandling generalHandlings[81];	//General handling
	BikeHandling	bikeHandlings[7];		//Bike handling
	char			padding[4];				//Padding for plane handling
	PlaneHandling	planeHandlings[6];		//Plane handling
	BoatHandling	boatHandlings[3];		//Boat handling - interestingly, there's no PREDATOR there :O
};