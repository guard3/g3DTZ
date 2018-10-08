/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	Pool.h - Structs about pools
	Based on aap's nicely laid out struct
*/
#pragma once
#include "rsl.h"
#include "typedef.h"

struct Collision
{
	int32	unk;
	uint8	loaded;
	Rect	rect;
#ifdef vcs
	Rect	rect2;		//???
#endif
	char	name[20];
#ifdef lcs
	int16	firstIndex;
	int16	lastIndex;
#else
	int32	firstIndex;
	int32	lastIndex;
#endif
	uint32	*chunkData;	// pointer to relocatable chunk, includes header
};

struct Entity
{
	float	matrix[4][4];
	char	unk1[0x18];	//This shit... x(
	int16	modelIndex;
	uint8	level;
	uint8	area;		// seems uninitialized in VCS o_O
	void	*vtable;
};

struct Texture
{
	void	*texlist;
	int32	refCount;
	char	name[20];
};

template<class PoolItem>
struct Pool
{
	PoolItem	*items;
	uint8		*flags;
	int32		size;
	int32		allocPtr;
#if !defined(lcs) && !defined(psp)
	char		name[16];
#endif
};