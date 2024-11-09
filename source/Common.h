#ifndef G3DTZ_COMMON_H
#define G3DTZ_COMMON_H
#include <cstdint>
#include <type_traits>

typedef wchar_t wchar;

typedef std::int8_t  int8;
typedef std::int16_t int16;
typedef std::int32_t int32;
typedef std::uint8_t  uint8;
typedef std::uint16_t uint16;
typedef std::uint32_t uint32;

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

/* Configure the appropriate bool size for each platform: 8bit for PSP, 32bit for PS2 */
namespace detail {
	using platform_type =
#ifdef PS2
		bool32;
#else
		bool8;
#endif
	using boolean = std::conditional_t<sizeof(bool) == sizeof(platform_type), bool, platform_type>;
}
using detail::boolean;

#define G3DTZ_STR_IMPL(value) #value
#define G3DTZ_STR(value) G3DTZ_STR_IMPL(value)
#define G3DTZ_ASSERT_SIZE_IMPL(type, size) static_assert(sizeof(type) == (size), "The size of " #type " is not " G3DTZ_STR(size))

#if defined LCS && defined PSP
#define assert_size(type, size, _, __, ___) G3DTZ_ASSERT_SIZE_IMPL(type, size)
#elif defined LCS && defined PS2
#define assert_size(type, _, size, __, ___) G3DTZ_ASSERT_SIZE_IMPL(type, size)
#elif defined VCS && defined PSP
#define assert_size(type, _, __, size, ___) G3DTZ_ASSERT_SIZE_IMPL(type, size)
#else
#define assert_size(type, _, __, ___, size) G3DTZ_ASSERT_SIZE_IMPL(type, size)
#endif

#endif /* G3DTZ_COMMON_H */