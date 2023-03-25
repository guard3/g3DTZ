#pragma once
#include <cstdint>

typedef wchar_t wchar;

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

typedef long long llong;
typedef unsigned char      uchar;
typedef unsigned short     ushort;
typedef unsigned int       uint;
typedef unsigned long      ulong;
typedef unsigned long long ullong;

typedef uint8  bool8;
typedef uint16 bool16;
typedef uint32 bool32;

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

/* Configure the appropriate bool size for each platform: 8bit for PSP, 32bit for PS2 */
namespace detail {
#ifdef PS2
	typedef bool32 boolean;
#else
	typedef bool8  boolean;
#endif

	template<typename T, bool = sizeof(T) == sizeof(boolean)>
	struct platform_bool {
		typedef T type;
	};

	template<typename T>
	struct platform_bool<T, false> {
		typedef boolean type;
	};
}
typedef typename detail::platform_bool<bool>::type boolean;

#define _G3DTZ_STR2(value) #value
#define _G3DTZ_STR(value) _G3DTZ_STR2(value)

#if defined LCS && defined PSP
#define assert_size(type, size, _, __, ___) static_assert(sizeof(type) == (size), "The size of " #type " is not " _G3DTZ_STR(size))
#elif defined LCS && defined PS2
#define assert_size(type, _, size, __, ___) static_assert(sizeof(type) == (size), "The size of " #type " is not " _G3DTZ_STR(size))
#elif defined VCS && defined PSP
#define assert_size(type, _, __, size, ___) static_assert(sizeof(type) == (size), "The size of " #type " is not " _G3DTZ_STR(size))
#else
#define assert_size(type, _, __, ___, size) static_assert(sizeof(type) == (size), "The size of " #type " is not " _G3DTZ_STR(size))
#endif