#pragma once
#include "Streaming.h"

class CCutsceneMgr final
{
private:
	inline static CDirectory* ms_pCutsceneDir;

public:
	static void Initialize(CDirectory* cutsceneDir) { ms_pCutsceneDir = cutsceneDir; }
	static CDirectory* GetDirectory() { return ms_pCutsceneDir; }
};