/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	Streaming.h - Structs about streaming data
	Based on aap's nicely laid out structs
*/
#pragma once
#include "typedef.h"

struct dir
{
	uint32	start;
	uint32	size;
	char	name[0x18];
};

struct ExtraDir
{
	dir		*extraObjectDirs;
	int32	unk;
	int32	numExtraDirs;
};

struct StreamingInfo
{
#ifdef lcs
	StreamingInfo	*nextRequest;
	StreamingInfo	*prevRequest;
	uint8			loadStatus;
	uint8			loadFlags;
	int16			modelIndex;
#elif defined(vcs) && defined(ps2)
	int32	field_0;	//uninitialized
	int32	field_4;	//0
	int32	field_8;	//0
	int16	field_C;	//0
	int16	field_E;	//uninitialized
#else
	char	unk[12];
#endif
	int32	cdPosn;
	int32	cdSize;
};

struct Streaming
{
#ifdef lcs
	//Many unknowns :(
	int32			field_0;
	StreamingInfo	mdlStreamingInfos[4900];
	StreamingInfo	texStreamingInfos[1200];
	StreamingInfo	colStreamingInfos[15];
	StreamingInfo	anmStreamingInfos[60];
#ifdef ps2
	uint8			unk[0xb8];
#else
	uint8			unk[0x88];
#endif
	ExtraDir		*extraDir;
	StreamingInfo	startLoadedList;
	StreamingInfo	endLoadedList;
	StreamingInfo	startRequestedList;
	StreamingInfo	endRequestedList;
	int32 IslandLODIndID;
	int32 IslandLODcomINDId;
	int32 IslandLODcomSUBID;
	int32 IslandLODsubINDID;
	int32 IslandLODsubCOMID;
	int32 field_1E360;
	int32 field_1E364;
	int32 field_1E368;
	int32 field_1E36C;
	int32 field_1E370;
#else
	int32			unk0;
	int32			unk1;			//0x74000
	int32			texIdOffset;	//Index in the streaming table where the textures are listed
	int32			colIdOffset;	//Index in the streaming table where the collisions are listed
	int32			anmIdOffset;	//Indef in the streaming table where the animations are listed
	int32			numStreamInfos;	//Number of streaming infos in the streaming table;
	int32			unk2;			//0
	int32			unk3;			//0xC
	uint8			unk4[0x50];
#ifdef ps2
	uint8			unk5[0x58];
#else
	uint8			unk5[0x28];
#endif
	StreamingInfo	*streamingInfos;
#ifdef ps2
	uint32			unk6[6];
#else
	uint32			unk6[4];
#endif
	dir				*extraObjectDirs;
	int32			numExtraDirs;
	int32			numExtraDirs2;	//Looks like it's the same
	//Maybe more shit...
#endif
};