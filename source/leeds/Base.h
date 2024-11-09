#ifndef G3DTZ_BASE_H
#define G3DTZ_BASE_H
#include "Common.h"

namespace base {
	struct sChunkHeader {
		uint32 ident;     // File signature, 'GTAG' for GAME.DAT
		uint32 shrink;    // True: clear relocation table
		uint32 fileEnd;   // File size
		uint32 dataEnd;   // Data size
		uint32 relocTab;  // Pointer to relocation table
		uint32 numRelocs; // Size of relocation table
		uint32 globalTab;
		uint16 numClasses;
		uint16 numFuncs;
	};

	class cRelocatableChunk {
	public:
		/* This function is non-static originally, but we don't need a relocatable chunk instance anyway */
		static void* Load(void*) noexcept;
	};
}
#endif /* G3DTZ_BASE_H */