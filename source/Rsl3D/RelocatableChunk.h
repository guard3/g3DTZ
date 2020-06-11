#include "Common.h"

class cRelocChunk final
{
private:
	uint32 ident;     // File signature, 'GTAG' for GAME.DAT
	uint32 shrink;    // True: clear relocation table
	uint32 fileEnd;   // File size
	uint32 dataEnd;   // Data size
	uint32 relocTab;  // Pointer to relocation table
	uint32 numRelocs; // Size of relocation table
	uint32 globalTab;
	uint16 numClasses;
	uint16 numFuncs;

public:
	/* Properties */
	inline uint32 __get_ident() { return ident; }
	inline bool __get_shrink() { return shrink; }
	inline uint32 __get_file_size() { return fileEnd; }
	inline uint32 __get_data_size() { return dataEnd; }
	inline void* __get_data_ptr() { return reinterpret_cast<uint8*>(this) + sizeof(cRelocChunk); }
	__declspec(property(get = __get_ident)) uint32 Ident;
	__declspec(property(get = __get_shrink)) bool Shrink;
	__declspec(property(get = __get_file_size)) uint32 FileSize;
	__declspec(property(get = __get_data_size)) uint32 DataSize;
	__declspec(property(get = __get_data_ptr)) void* DataPtr;

	/* Functions */
	cRelocChunk& Fixup();
};