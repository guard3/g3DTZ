#pragma once
#include "Common.h"

class CDirectoryInfo final
{
public:
	uint32 offset;
	uint32 size;
	char   name[24];
};

class CDirectory final
{
public:
	CDirectoryInfo* entries;
	int32 maxEntries;
	int32 numEntries;
};

class CStreamingInfo final
{
private:
#if defined VCS && defined PS2
	void* field_0; // Uninitialized
#endif
	CStreamingInfo* m_next;
	CStreamingInfo* m_prev;
	uint8           m_status;
	uint8           m_flags;
	int16           m_nextModelOnCd; // Uninitialized on VCS PS2
	uint32          m_cdPosn;
	uint32          m_cdSize;
public:
	auto GetPosition() { return m_cdPosn; }
	auto GetSize()     { return m_cdSize; }
};

/* CStreaming is a mess... */
class CStreaming final
{
private:
	inline static CStreaming* mspInst;
#ifdef LCS
	inline static constexpr int NUM_MDLSTREAMINFO = 4900;
	inline static constexpr int NUM_TEXSTREAMINFO = 1200;
	inline static constexpr int NUM_COLSTREAMINFO = 15;
	inline static constexpr int NUM_ANMSTREAMINFO = 60;

	int32          field_0;
	CStreamingInfo m_aMdlStreamingInfos[NUM_MDLSTREAMINFO];
	CStreamingInfo m_aTexStreamingInfos[NUM_TEXSTREAMINFO];
	CStreamingInfo m_aColStreamingInfos[NUM_COLSTREAMINFO];
	CStreamingInfo m_aAnmStreamingInfos[NUM_ANMSTREAMINFO];
#ifdef PS2
	uint8 unk[0xb8];
#else
	uint8 unk[0x88];
#endif
	CDirectory*    m_pExtraObjectsDir;
	CStreamingInfo m_startLoadedList;
	CStreamingInfo m_endLoadedList;
	CStreamingInfo m_startRequestedList;
	CStreamingInfo m_endRequestedList;
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
	int32 unk0;
	int32 unk1;             // 0x74000
	int32 m_texOffset;      // Offset in the streaming table where the textures are listed
	int32 m_colOffset;      // Offset in the streaming table where the collisions are listed
	int32 m_anmOffset;      // Offset in the streaming table where the animations are listed
	int32 m_numStreamInfos; // Number of streaming infos in the streaming table;
	int32 unk2;             // 0
	int32 unk3;             // 0xC
	uint8 unk4[0x50];
#ifdef PS2
	uint8 unk5[0x58];
#else
	uint8 unk5[0x28];
#endif
	CStreamingInfo* m_aStreamingInfos;
#ifdef PS2
	uint32 unk6[6];
#else
	uint32 unk6[4];
#endif
	CDirectory m_extraObjectsDir;
	// Maybe more stuff x(
#endif
public:
#ifdef LCS
	static constexpr int GetNumMdlStreamingInfos() { return NUM_MDLSTREAMINFO; }
	static constexpr int GetNumTexStreamingInfos() { return NUM_TEXSTREAMINFO; }
	static constexpr int GetNumColStreamingInfos() { return NUM_COLSTREAMINFO; }
	static constexpr int GetNumAnmStreamingInfos() { return NUM_ANMSTREAMINFO; }
	static CStreamingInfo& GetMdlStreamingInfo(int index) { return mspInst->m_aMdlStreamingInfos[index]; }
	static CStreamingInfo& GetTexStreamingInfo(int index) { return mspInst->m_aTexStreamingInfos[index]; }
	static CStreamingInfo& GetColStreamingInfo(int index) { return mspInst->m_aColStreamingInfos[index]; }
	static CStreamingInfo& GetAnmStreamingInfo(int index) { return mspInst->m_aAnmStreamingInfos[index]; }
	static CDirectory& GetExtraObjectDirectory() { return *mspInst->m_pExtraObjectsDir; }
#else
	static auto GetNumMdlStreamingInfos() { return mspInst->m_texOffset;                             }
	static auto GetNumTexStreamingInfos() { return mspInst->m_colOffset - mspInst->m_texOffset;      }
	static auto GetNumColStreamingInfos() { return mspInst->m_anmOffset - mspInst->m_colOffset;      }
	static auto GetNumAnmStreamingInfos() { return mspInst->m_numStreamInfos - mspInst->m_anmOffset; }
	static CStreamingInfo& GetMdlStreamingInfo(int index) { return mspInst->m_aStreamingInfos[index]; }
	static CStreamingInfo& GetTexStreamingInfo(int index) { return (mspInst->m_aStreamingInfos + mspInst->m_texOffset)[index]; }
	static CStreamingInfo& GetColStreamingInfo(int index) { return (mspInst->m_aStreamingInfos + mspInst->m_colOffset)[index]; }
	static CStreamingInfo& GetAnmStreamingInfo(int index) { return (mspInst->m_aStreamingInfos + mspInst->m_anmOffset)[index]; }
	static CDirectory& GetExtraObjectDirectory() { return mspInst->m_extraObjectsDir; }
#endif
	static void Initialize(CStreaming* inst) { mspInst = inst; }
};