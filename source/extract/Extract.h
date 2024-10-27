#pragma once
#include <cstdio>
#include <span>
#include <string>

#define G3DTZ_MESSAGE "Generated by g3DTZ v2.0 - by guard3"

bool ExtractModelInfoAndStuff();
bool ExtractIPLs();
bool ExtractObjectData();
bool ExtractPedType();
bool ExtractPedStats();
bool ExtractAnimations();
bool ExtractSurfaceTable();
bool ExtractTimeCycle();
#ifdef LCS
bool ExtractFightMoves();
#else
inline bool ExtractFightMoves() { return true; }
#endif
bool ExtractPedGroups();
bool ExtractWeaponInfo();
bool ExtractDIRs();
bool ExtractParticle();
bool ExtractWaterLevel();
bool ExtractZones();
bool ExtractPathData();

struct CAnimBlendTree;
void ExportAnimations(std::FILE* outFile, std::string_view blockName, std::span<CAnimBlendTree*> animTrees);