#include "Extract.h"
#include "Streaming.h"
#include "ModelInfo.h"
#include "TexListStore.h"
#include "ColStore.h"
#include "AnimManager.h"
#include "CutsceneMgr.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

bool ExtractDIRs()
{
	/* First, extract cutscene dir */
#ifdef LCS
	constexpr const char* cutsfilename = "cuts.dir";
#else
#ifdef PSP
	constexpr const char* cutsfilename = "mocappsp.dir";
#else
	constexpr const char* cutsfilename = "mocapps2.dir";
#endif
#endif
	std::ofstream f(cutsfilename, std::ios::binary);
	if (!f)
	{
		ErrorBoxCannotCreateFile(cutsfilename);
		return false;
	}
#pragma warning(suppress: 26451)
	f.write(reinterpret_cast<const char*>(CCutsceneMgr::GetDirectory()->entries), CCutsceneMgr::GetDirectory()->numEntries * sizeof(CDirectoryInfo));
	f.close();

	/*
	 * And now... extract GTA3.DIR, juicy stuff!
	 * First, get extra objects .DIR in a vector
	 */
	CDirectory& extraObjectDir = CStreaming::GetExtraObjectDirectory();
	std::vector<CDirectoryInfo> dir_vector(extraObjectDir.numEntries);
	int i;
	for (i = 0; i < extraObjectDir.numEntries; ++i)
	{
#ifdef PSP
		constexpr const char* extension = ".MDL";
#else
		constexpr const char* extension = ".mdl";
#endif
		dir_vector[i] = extraObjectDir.entries[i];
		strcat(dir_vector[i].name, extension);
		
	}

	/* A lambda that creates a new .DIR entry in the vector */
	auto push_new_dir = [&dir_vector](uint32 offset, uint32 size, const char* name, const char* extension) {
		static CDirectoryInfo dir_info;
		dir_info.offset = offset;
		dir_info.size = size;
		int len1, len2;
		for (len1 = 0; name[len1]; ++len1)
			dir_info.name[len1] = name[len1];
		for (len2 = 0; extension[len2]; ++len2)
			dir_info.name[len1 + len2] = extension[len2];
		for (len1 += len2; len1 < 24; ++len1)
			dir_info.name[len1] = '\0';
		dir_vector.push_back(dir_info);
	};

	/* Generate DIR entries from streaming */
	for (i = 0; i < CStreaming::GetNumMdlStreamingInfos(); ++i)
	{
		auto& s = CStreaming::GetMdlStreamingInfo(i);
		if (s.GetSize())
			push_new_dir(s.GetPosition(), s.GetSize(), CModelInfo::GetModelInfo(i)->GetModelName(), ".mdl");
	}
	for (i = 0; i < CStreaming::GetNumTexStreamingInfos(); ++i)
	{
		auto& s = CStreaming::GetTexStreamingInfo(i);
		if (s.GetSize())
#ifdef LCS
			push_new_dir(s.GetPosition(), s.GetSize(), CTexListStore::GetSlot(i)->GetName(), ".chk");
#else
			push_new_dir(s.GetPosition(), s.GetSize(), CTexListStore::GetSlot(i)->GetName(), ".xtx");
#endif
	}
	for (i = 0; i < CStreaming::GetNumColStreamingInfos(); ++i)
	{
		auto& s = CStreaming::GetColStreamingInfo(i);
		if (s.GetSize())
			push_new_dir(s.GetPosition(), s.GetSize(), CColStore::GetSlot(i)->GetName(), ".col2");
	}
	for (i = 0; i < CStreaming::GetNumAnmStreamingInfos(); ++i)
	{
		auto& s = CStreaming::GetAnmStreamingInfo(i);
		if (s.GetSize())
			push_new_dir(s.GetPosition(), s.GetSize(), CAnimManager::GetAnimationBlock(i)->name, ".anim");
	}

	/* Sort the .DIR entry vector by offset */
	std::sort(
		dir_vector.begin(),
		dir_vector.end(),
		[](const CDirectoryInfo& i1, const CDirectoryInfo& i2) {
			return i1.offset < i2.offset;
		}
	);

	/* Open .DIR file */
#ifdef PSP
#ifdef LCS
	constexpr const char* gta3filename = "gta3psphr.dir";
#else
	constexpr const char* gta3filename = "gta3psp.dir";
#endif
#else
	constexpr const char* gta3filename = "gta3ps2.dir";
#endif
	f.open(gta3filename, std::ios::binary);
	if (!f)
	{
		ErrorBoxCannotCreateFile(gta3filename);
		return false;
	}

	/* Write .DIR entries to file */
	for (auto& d : dir_vector)
		f.write(reinterpret_cast<const char*>(&d), sizeof(d));

	return true;
}