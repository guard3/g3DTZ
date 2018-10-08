/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	AnimManager.h - Structs about animation data
	Big thanks to aap for his structs; this thing is terrible x(
*/
#pragma once
#include <map>
#include "typedef.h"

std::map<int, const char*> animGroups_lcs = {
	{ 0, "man" },
	{ 7, "unarmed" },
	{ 8, "screwdrv" },
	{ 9, "knife" },
	{ 10, "baseball" },
	{ 12, "chainsaw"},
	{ 13, "python" },
	{ 14, "colt45" },
	{ 15, "shotgun"},
	{ 16, "buddy" },
	{ 17, "tec" },
	{ 18, "uzi"}, 
	{ 19, "rifle"},
	{ 20, "m60"},
	{ 21, "sniper" },
	{ 22, "grenade" },
	{ 23, "flame" },
	{ 24, "rocketla" },
	{ 31, "player" },
	{ 38, "shuffle" },
	{ 39, "oldman" },
	{ 40, "gang1" },
	{ 41, "gang2" },
	{ 42, "fatman" },
	{ 45, "woman" },
	{ 47, "busywoman" },
	{ 48, "sexywoman" },
	{ 49, "fatwoman" },
	{ 50, "oldwoman" }
};

struct AnimBlock
{
	char name[20];
#ifdef ps2
	int32 unknown; //A placeholder value, probably wrong, just so that I can get name correctly :P
#endif
	int8 isLoaded;
	int16 refCount;
	int32 animBase;	// into the blend tree array
	int32 numAnims;
	void *chunkData;	// pointer to relocatable chunk, includes header
#ifdef vcs
	int32 unk0;
	int32 unk1;
#endif
};

struct AnimBlendAssocGroup
{
	AnimBlock	*animBlock;
	void		*assocList;
	int32		numAssociations;
	int32		baseIndex;	// index of first assoc in assocList
	int32		groupId;	// index in CAnimManager::m_aAnimAssocGroups
};

struct AnimAssoc_vcs
{
	int32 id;
	char name[44];	// this is most certainly too long but the data is uninitialized
	int8 unk1;
	// 3 bytes uninitialized
	int16 unk2;
	int16 unk3;
};

struct AnimAssocGroup_vcs
{
	char groupname[24];
	char blockname[20];
	int32 animBase;	// first ID, index into CAnimManager_vcs::associations
	int32 numAnims;
};

struct AnimManager
{
#ifdef vcs
	AnimAssocGroup_vcs assocGroups[200];
	AnimAssoc_vcs associations[990];
	int32 numAssocGroups;
	int32 numAssocs;
	int32 numUnk;
#endif
	void		*animations;
	AnimBlock	*animBlocks;
	int32		numAnimations;
	int32		numAnimBlocks;
	void		*animAssocGroups;	// LCS: [84]
};