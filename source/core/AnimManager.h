#pragma once
#include "Maths.h"

class CAnimAssocGroup
{
public:
	char groupname[24];
	char blockname[20];
	int32 animBase;	// first ID, index into CAnimManager_vcs::associations
	int32 numAnims;
};

class CAnimAssoc
{
public:
	int32 id;
	char name[44];	// this is most certainly too long but the data is uninitialized
	int8 unk1;
	// 3 bytes uninitialized
	int16 unk2;
	int16 unk3;
};

class KeyFrame
{
private:
	int16 x, y, z, w, dt;

protected:
	inline static float HalfToFloat(int16 x)
	{
		/*
		 * The real numbers in key frames are 16-bit "half" floats
		 * The code below converts a 16-bit float to a standard 32-bit one.
		 * Guide on bitwise operators acquired from http://www.fox-toolkit.org/ftp/fasthalffloatconversion.pdf
		 */
		uint32 result = ((x & 0x8000) << 16) | (((x & 0x7C00) + 0x1C000) << 13) | ((x & 0x03FF) << 13);
		return reinterpret_cast<float&>(result);
	}

public:
	inline CQuaternion GetRotation()  { return { HalfToFloat(x), HalfToFloat(y), HalfToFloat(z), HalfToFloat(w) }; }
	inline float       GetDeltaTime() { return HalfToFloat(dt); }
};

class KeyFrameTrans : public KeyFrame
{
private:
	int16 x, y, z;

public:
	inline CVector GetTranslation() { return { HalfToFloat(x), HalfToFloat(y), HalfToFloat(z) }; }
};

enum eSequenceFlag : uint16
{
	SEQ_HAS_ROTATION    = 0x01,
	SEQ_HAS_TRANSLATION = 0x02,
	SEQ_UNK_0x04        = 0x04,
	SEQ_UNK_0x08        = 0x08,
	SEQ_HAS_BONETAG     = 0x10 // Not sure...
};

struct CAnimBlendSequence
{
	eSequenceFlag flag;
	int16         numFrames;
	KeyFrame*     keyFrames;
	int16         boneTag;
	int16         unk;
};

struct CAnimBlendTree
{
	CAnimBlendSequence* blendSequences;
	char name[24];
	int16 numSequences;
	bool loadSpecial;     // still not sure about those two...copied from vc_anim
	bool compressed;      // where I already didn't know where they came from
	float totalLength;
#ifdef VCS
	int unknown;
#endif
};

struct CAnimBlock
{
	char  name[20];
	bool  isLoaded; // *
#ifdef PSP          // *
	int16 refCount; // * On PS2 this could be some 32-bit bool and a 16-bit refCount. But this setup here works too...
#else               // *
	int32 refCount; // *
#endif
	int32 firstIndex; // into the blend tree array; CAnimManager::m_aAnimations
	int32 numAnims;
	void* chunkData; // pointer to relocatable chunk, includes header
#ifdef VCS
	int32 unk0; // maybe ids to the extra structures
	int32 unk1;
#endif
};

class CAnimBlendNode;

/* Needs proper reversing */
struct CAnimBlendAssociation
{
	CAnimBlendAssociation* next;
	CAnimBlendAssociation* prev;
	float unk1, unk2, unk3, unk4;
	//int16 flags;
	//float timeStep;
	//float blendAmount;
	//int8 field_14;
	int32 numNodes;
	CAnimBlendNode* nodes;
	CAnimBlendTree* hierarchy;
	float blendDelta;
	float currentTime;
	float speed;
	int16 animId;
	int16 groupId;
	int32 callbackType;
	void* callback; // pointer to callback function; void (*callback)(CAnimBlendAssociation*, void*);
	void* callbackArg;
	//int8 field_40;
	float unk5;
};

class CAnimBlendAssocGroup
{
public:
	CAnimBlock* animBlock;
	CAnimBlendAssociation* assocList;
	int32 numAssociations;
	int32 baseIndex; // index of first assoc in assocList
	int32 groupId;   // index in CAnimManager::m_aAnimAssocGroups

	const char* GetName();
};

class CAnimManager
{
private:
#ifdef VCS
	friend class CAnimBlendAssocGroup;

	CAnimAssocGroup assocGroups[200];  // * 
	CAnimAssoc      associations[990]; // *
	int32           numAssocGroups;    // * Extra VCS stuff, interesting...
	int32           numAssocs;         // *
	int32           numUnk;            // *
#endif
	CAnimBlendTree*       m_aAnimations;
	CAnimBlock*           m_aAnimBlocks;
	int32                 m_numAnimations;
	int32                 m_numAnimBlocks;
	CAnimBlendAssocGroup* m_aAnimAssocGroups; // LCS: [84]

	static CAnimManager* mspInst;

public:
	inline static void Load(CAnimManager* inst) { mspInst = inst; }

	inline static CAnimBlendTree* GetAnimation(int index) { return mspInst->m_aAnimations + index; }
	inline static CAnimBlock* GetAnimationBlock(int index) { return mspInst->m_aAnimBlocks + index; }
	inline static int32 GetNumAnimations() { return mspInst->m_numAnimations; }
	inline static int32 GetNumAnimBlocks() { return mspInst->m_numAnimBlocks; }
	inline static CAnimBlendAssocGroup* GetAssocGroup(int index) { return mspInst->m_aAnimAssocGroups + index; }
};