#ifndef G3DTZ_RESOURCEIMAGE_H
#define G3DTZ_RESOURCEIMAGE_H
#include "Base.h"
#include <filesystem>
#include <istream>

void
LoadResourceImage(std::filesystem::path, const base::sChunkHeader&, std::istream&);
#endif /* G3DTZ_RESOURCEIMAGE_H */