#pragma once
#include "Maths.h"

class KeyFrame
{
private:
	int16 x, y, z, w, dt;

protected:
	static float HalfToFloat(int16 x)
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
	CQuaternion GetRotation()  { return { HalfToFloat(x), HalfToFloat(y), HalfToFloat(z), HalfToFloat(w) }; }
	float       GetDeltaTime() { return HalfToFloat(dt); }
};

class KeyFrameTrans : public KeyFrame
{
private:
	int16 x, y, z;

public:
	CVector GetTranslation() { return { HalfToFloat(x), HalfToFloat(y), HalfToFloat(z) }; }
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
	char    m_name[20];
	boolean m_loaded;
	int16   m_numRefs;
	int32   firstIndex; // into the blend tree array; CAnimManager::m_aAnimations
	int32   numAnims;
	void*   chunkData; // pointer to relocatable chunk, includes header
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
	int flags;
	int field_C;
	float m_fBlendAmount;
	int field_14;
	int32 m_iNumAnimBlendNodes;
	CAnimBlendNode* m_pAnimBlendNodes;
	CAnimBlendTree* hierarchy;
	float m_fBlendDelta;
	float m_fCurrentTime;
	float speed;
	int16 animId;
	int16 groupId;
	int32 callbackType;
	void* callback; // pointer to callback function; void (*callback)(CAnimBlendAssociation*, void*);
	void* callbackArg;
	int field_40;
};
assert_size(CAnimBlendAssociation,
/* LCS PSP */ 0x44,
/* LCS PS2 */ 0x44,
/* VCS PSP */ 0x44,
/* VCS PS2 */ 0x44);

class CAnimBlendAssocGroup
{
public:
	CAnimBlock* m_pAnimBlock;
	CAnimBlendAssociation* m_aAssociationArray;
	int32 m_numAssociations;
	int32 m_idOffset; // index of first assoc in assocList
	int32 m_grpId;    // index in CAnimManager::m_aAnimAssocGroups

	const char* GetName();
};
assert_size(CAnimBlendAssocGroup,
/* LCS PSP */ 0x14,
/* LCS PS2 */ 0x14,
/* VCS PSP */ 0x14,
/* VCS PS2 */ 0x14);

enum AnimationId : int32 {};
assert_size(AnimationId,
/* LCS PSP */ 4,
/* LCS PS2 */ 4,
/* VCS PSP */ 4,
/* VCS PS2 */ 4);

class CAnimManager
{
public:
#ifdef LCS
	struct AnimDescriptor;
	struct AnimAssocDefinition {
		const char* pName;
		const char* pBlockName;
		int32 associatedClumpId; // doubt that "clump" is part on the name on stories; names are from SA anyway...
		int32 numReqAnims;
		const char** aReqAnims;
		AnimDescriptor* aAnimDesc;
	};

	static const AnimAssocDefinition ms_aAnimAssocDefinitions[];
#else
	/* Needs more reversing - Name taken from SA */
	struct AnimAssocDefinition {
		char pName[24];
		char pBlockName[20];
		int32 firstAnim;
		int32 numAnims;
	};
	/* Needs more reversing too */
	struct AnimDescriptor { 
		AnimationId id;
		char name[45];
		uint32 defaultFlags;
	};
	assert_size(AnimDescriptor, 0, 0,
	/* VCS PSP */ 0x38,
	/* VCS PS2 */ 0x38);

	AnimAssocDefinition m_aAnimAssocDefinitions[200];
	AnimDescriptor      m_aAnimDescriptors[990];
	int32               m_numAnimAssocDefinitions;
	int32               m_numAnimDescriptors;
	int32               field_10138;
#endif
	CAnimBlendTree*       m_aAnimations;
	CAnimBlock*           m_aAnimBlocks;
	int32                 m_numAnimations;
	int32                 m_numAnimBlocks;
	CAnimBlendAssocGroup* m_aAnimAssocGroups; // LCS: [84]

	static CAnimManager* mspInst;

public:
	static void Load(CAnimManager* inst) { mspInst = inst; }

	static CAnimBlendTree* GetAnimation(int index) { return mspInst->m_aAnimations + index; }
	static CAnimBlock* GetAnimationBlock(int index) { return mspInst->m_aAnimBlocks + index; }
	static int32 GetNumAnimations() { return mspInst->m_numAnimations; }
	static int32 GetNumAnimBlocks() { return mspInst->m_numAnimBlocks; }
	static CAnimBlendAssocGroup* GetAssocGroup(int index) { return mspInst->m_aAnimAssocGroups + index; }
};
assert_size(CAnimManager::AnimAssocDefinition,
/* LCS PSP */ 0x18,
/* LCS PS2 */ 0x18,
/* VCS PSP */ 0x34,
/* VCS PS2 */ 0x34);
assert_size(CAnimManager,
/* LCS PSP */ 0x14,
/* LCS PS2 */ 0x14,
/* VCS PSP */ 0x10150,
/* VCS PS2 */ 0x10150);