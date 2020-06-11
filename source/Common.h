#pragma once
typedef wchar_t wchar;

typedef __int8  int8;
typedef __int16 int16;
typedef __int32 int32;
typedef unsigned __int8  uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;

typedef long long llong;
typedef unsigned char      uchar;
typedef unsigned short     ushort;
typedef unsigned int       uint;
typedef unsigned long      ulong;
typedef unsigned long long ullong;

#ifdef LCS
#define GAME_NAME    "lcs"
#define GAME_NAME_W L"lcs"
#else
#define GAME_NAME    "vcs"
#define GAME_NAME_W L"vcs"
#endif
#ifdef PSP
#define PLATFORM_NAME    "psp"
#define PLATFORM_NAME_W L"psp"
#else
#define PLATFORM_NAME    "ps2"
#define PLATFORM_NAME_W L"ps2"
#endif
#define G3DTZ_NAME   GAME_NAME   "_" PLATFORM_NAME
#define G3DTZ_NAME_W GAME_NAME_W "_" PLATFORM_NAME

#define __property(func) __declspec(property(get=func))