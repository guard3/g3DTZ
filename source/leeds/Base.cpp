#include "Base.h"

void* base::cRelocatableChunk::Load(void* pData) noexcept {
	auto pHeader = reinterpret_cast<sChunkHeader*>(pData);
		
	/* Fixup */
	uint32 offset = reinterpret_cast<uint32>(pData);
	uint32* table = reinterpret_cast<uint32*>(pHeader->relocTab + offset);

	for (uint32 i = 0; i < pHeader->numRelocs; ++i)
		*reinterpret_cast<uint32*>(table[i] + offset) += offset;
		
	/* Return a pointer past the end of the header */
	return &pHeader[1];
}