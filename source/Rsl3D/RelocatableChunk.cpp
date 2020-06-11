#include "RelocatableChunk.h"

cRelocChunk& cRelocChunk::Fixup()
{
	uint32 offset = reinterpret_cast<uint32>(this);
	uint32* table = reinterpret_cast<uint32*>(relocTab + offset);
	for (uint32 i = 0; i < numRelocs; ++i)
		*reinterpret_cast<uint32*>(table[i] + offset) += offset;
	return *this;
}