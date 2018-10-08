/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	ModelInfo.h - Structs about ide section
	Based on aap's structs
*/
#pragma once
#include "typedef.h"
#include "Vector.h"
#include "HandlingManager.h"

const char* vehicleTypes[] = {
	"car",
	"boat",
#ifdef vcs
	"jetski",
#endif
	"train",
	"heli",
	"plane",
	"bike",
	"ferry",
#ifdef vcs
	"bmx",
	"quad"
#endif
};

const char* vehicleClasses[] = {
	"normal",
	"poorfamily",
	"richfamily",
	"executive",
	"worker",
	"big",
	"taxi",
	"moped",
	"motorbike",
	"leisureboat",
	"workerboat",
	"unknownClass1",	//VCS exclusive, no known name
	"unknownClass2"		//VCS exclusive, no known name
};

const char* pedTypes[] = {
	"PLAYER1",
	"PLAYER2",
	"PLAYER3",
	"PLAYER4",
	"CIVMALE",
	"CIVFEMALE",
	"COP",
	"GANG1",
	"GANG2",
	"GANG3",
	"GANG4",
	"GANG5",
	"GANG6",
	"GANG7",
	"GANG8",
	"GANG9",
	"EMERGENCY",
	"FIREMAN",
	"CRIMINAL",
	"SPECIAL",
	"PROSTITUTE"
};

int processModelInfoFlags(uint16 _Flags)
{
	uint16 result = _Flags >> 4;
	if ((result & (uint16)1) == 1) result--;
	result += (_Flags >> 2) & (uint16)1;
	return result;
}

enum ModelInfoTypes
{
	TYPE_OBJS = 1,
	TYPE_TOBJ = 3,
	TYPE_WEAP = 4,
	TYPE_HIER = 5,
	TYPE_CARS = 6,
	TYPE_PEDS = 7
};

struct BaseModelInfo
{
	char	unknown[8];
	uint32	hashName;
	void	*mdlFile;	//pointer to model chunk (filled at runtime)
	uint8	type;
	int8	num2dfx;
	bool	ownsColModel;
	void	*colModel;
	int16	_2dfxIndex;
	int16	objectIndex;
	int16	refCount;
	int16	txdIndex;
#ifdef vcs
	int16	unknownIndex;
#endif
	void	*vtable;
};

struct SimpleModelInfo : BaseModelInfo
{
	void			**objects;
	float			drawDistances[3];
	uint8			numObjects;
	uint16			flags;
	SimpleModelInfo	*relatedObject;
};

struct TimeModelInfo : SimpleModelInfo
{
	int32	timeOn;
	int32	timeOff;
	int16	otherModel;
};

struct WeaponModelInfo : BaseModelInfo
{
	void	**objects;
	float	drawDistances[3];
	uint8	numObjects;
	uint16	flags;
	int32	weaponIndex;
	int32	animBlockIndex;
};

struct ElementGroupModelInfo : public BaseModelInfo
{
	void *elementGroup;
	int32 animFileIndex;
};

struct VehicleModelInfo : ElementGroupModelInfo
{
#ifdef lcs
	uint8		lastColours[2];
	char		gameName[8];	//GXT Name
	uint32		vehicleType;
	float		wheelScale;
	int16		wheelId;
	int16		handlingIndex;
	uint8		numDoors;
	int8		vehicleClass;
	uint8		level;
	uint8		numExtras;
	uint16		frequency;
	int32		unk0;			//probably pad for Vector4D
	Vector4D	dummyPos[5];
	uint32		compRules;
	float		bikeSteerAngle;
	void		*materialsPrimary[25];
	void		*materialsSecondary[25];
	uint8		colours[2][8];	//Colour IDs
	uint8		numColours;
	uint8		lastColour;
	int8		currentColours[2];
	float		normalSplay;	//How much the normals are splayed by to improve the environment mapping on PSP
	void		**extras;
	int32		animBlockIndex;
#else
	/*
	still looking for:
	uint8 m_numExtras;
	*/
	char			unk0[8];
	GeneralHandling	*generalHandling;
	BikeHandling	*bikeHandling;
	PlaneHandling	*planeHandling;
	BoatHandling	*boatHandling;
	void			*jetskiHandling;
	void			*_6atvHandling;
	float		normalSplay;	//How much the normals are splayed by to improve the environment mapping on PSP
	uint32		vehicleType;
	float		wheelScale;
	float		wheelScaleRear;
	Vector4D	dummyPos[15];
	uint32		compRules;
	float		bikeSteerAngle;
	char		gameName[8];	//GXT Name
	uint8		unk2;			//lastColour, numExtras (???)
	uint8		numColours;
	uint8		unk3;			//Maybe numUnkTable
	uint8		colours[8][2];	//Colour IDs
	char		unk4[25];		//Maybe there's a "xxx by 2" table in there, similar to peds' one, unknown purpose
	void		*materialsPrimary[30];
	void		*materialsSecondary[25];
	void		**extras;
	int32		animBlockIndex;
	int16		wheelId;
	uint16		frequency;
	uint8		numDoors;
	int8		vehicleClass;
	uint8		level;
	char		unk5[13];
	int32		engineFarSample;
	int32		engineNearSample;
	int32		hornSample;
	int32		hornFrequency;
	int32		sirenSample;
	int32		sirenFrequency;
	int32		unk6;			//Door Sample????? Looks different compared to VC :thonk:
#endif
};

struct PedModelInfo : ElementGroupModelInfo
{
	int32	animGroup;
	int32	pedType;
	int32	pedStatIndex;
	uint32	carsDriveMask;
	void	*hitColModel;
	int8	radio1;
	int8	radio2;
#ifdef vcs					//Many unknowns, wouldn't be surprised if there's audio info somewhere
	uint8	unk1;
	uint8	numColours;
	uint8	numUnkTable;
	uint8	colours[16][4];
	uint8	unkTable[4][4]; //That's definetly wrong, must check with cars and in-game
	char	unk2[27];
	struct {				//Weird editable materials
		void	*mat;		//filled at runtime
		int32	numX;
	} materials[6];
	char	gameName[8];	//Maybe a game name equivalent, but for peds (???), same as the model name though
	uint32	unk3;			//0x31 for many peds
	uint32	unk4;
	uint32	unk5;			//always 0x7ffe9f0, even at runtime
	uint32	unk6;			//always 0
#endif
};