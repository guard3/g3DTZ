/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	Leeds.h - Structs about GAME.DAT header
	Based on aap's structs
*/
#pragma once
#include "typedef.h"
#include "Pedstats.h"
#include "ModelInfo.h"
#include "Pool.h"
#include "AnimManager.h"
#include "HandlingManager.h"
#include "2DEffect.h"
#include "AttributeZone.h"
#include "WeaponInfo.h"
#include "ColourTable.h"
#include "ObjectInfo.h"
#include "ParticleManager.h"
#include "TimeCycle.h"
#include "rsl.h"
#include "Streaming.h"
#include "SoundData.h"

#undef RGB // Important to undef in order avoid conflict between "rsl.h RBG" and "Windows.h RGB"

struct RelocChunk
{
	char	ident[4];	//Relocatable chunk signature - GATG for GAME.DAT
	bool	shrink;
	uint32	fileSize;	//File size
	uint32	dataSize;	//Data size
	uint32	**relocTab;	//Pointer to relocation table
	uint32	numRelocs;	//Number of relocations
	uint32	globalTab;	//Pointer to global table (not really sure what purpose it serves)
	uint16	numClasses;
	uint16	numFuncs;
};

struct ResourceImage
{
	void			*paths;
	Pool<Entity>	*buildingPool;
	Pool<Entity>	*treadablePool;
	Pool<Entity>	*dummyPool;
	void			*entryInfoNodePool;
	void			*ptrNodePool;
	int32			numModelInfos;
	BaseModelInfo	**modelInfos;
	void			*carArrays;
	void			*totalNumOfCarsOfRating;
	void			*theZones;	// gta3.zon
	void			*sectors;
	void			*bigBuildingList;
	int32			num2deffects;
	_2dEffect		*_2deffects;
	int16			*modelIndices;
	Pool<Texture>	*texList;
	void			*storedTexList;
	Pool<Collision>	*colPool;
	int32			colOnlyBB;
	void			*tempColModels;
	ObjectInfo		*objectInfo;		//OBJECT.DAT
	ColourTable		*colourTable;		//Colours from CARCOLS.DAT, LCS only (nullptr in VCS)
	Streaming		*streaming;			//Streaming info (contains hints of a gta3.dir)
	AnimManager		*animManager;
	void			*fightMoves;		// fistfite.dat
#ifdef lcs
	void			*pedAnimInfo;
#endif
	void			*pedType;		// ped.dat
	PedStat			**pedStats;			//42 elements
#ifdef vcs
	RGB				(*RGBTable)[128];	//Colours from PEDCOLS.DAT and CARCOLS.DAT [2][128]
	void			*unknown1;
#endif
	int32			numAttributeZones;	//number of CULL.IPL lines
	AtributeZone	*attributeZones;	//CULL.IPL
	int32			numOccluders;		//0
	void			*occluders;			//nullptr - no such file exists in LCS and VCS
	void			*waterLevelInst;	// waterpro.dat
#ifdef lcs
	HandlingManager	*handlingManager;	//HANDLING.CFG
#else
	void	*weatherTypeList;
#endif
	float			(*surface)[6];		//SURFACE.DAT [6][6]
	TimeCycle		*timecycle;			//TIMECYC.DAT
	int32			(*pedGroups)[16];	//PEDGRP.DAT [37][16] in LCS, [71][16] in VCS
	ParticleManager	*particleManager;	//PARTICLE.CFG [82] in LCS, [90] in VCS
	WeaponInfo		**weaponInfos;		//WEAPON.DAT [37] in LCS, [40] in VCS
#ifdef vcs
	int32			unknown2;
#endif
	void			**markers;	// [32] in LCS
	ExtraDir		*cutsceneDir;

#ifdef lcs
	void			*ferryInst;	// ferry.dat
	void			*trainInst;	// tracks(2).dat
	void			*planeInst;	// flight.dat
#ifdef psp
	SoundData		*soundData;
#endif
#else
	// one probably flight.dat
	void			*unknown3;
	void			*unknown4;	// 0 in PS2, 16 in PSP, some numSomething I suppose
	void			*unknown5;
	SoundData		*soundData;	//nullptr on VCS PS2
#endif
	void	*menuCompressedTextures;
#ifdef vcs
	void	*unknown7;
	void	*unknown8;
	void	*unknown9;
	int32	unknown10;
	void	*fontdef;
#endif
	int		fontTexListSize;
	void	*fontCompressedTexList;
#ifdef vcs
	void	*radarTextures;
#endif
};