/*
	g3DTZ - a DTZ extraction utility - by guard3
	Don't delete this comment block; respect my work
	HashNames.h - The hash-name dictionary
*/
#pragma once
#include <map>
#include "typedef.h"
std::map<uint32, const char*> names = {
#ifdef lcs
#include "lcsnames.inc"
#else
#include "bruteforcedvcsnames.inc"
#include "vcsnames.inc"
#endif
	{0, "no_name"}
};