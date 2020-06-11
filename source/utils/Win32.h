#pragma once
#include "Common.h"

/* Remove unnecessary windows definitions */
#pragma push_macro("WIN32_LEAN_AND_MEAN")
#pragma push_macro("NOGDICAPMASKS")
#pragma push_macro("NOVIRTUALKEYCODES")
#pragma push_macro("NOWINMESSAGES")
#pragma push_macro("NOWINSTYLES")
#pragma push_macro("NOSYSMETRICS")
#pragma push_macro("NOMENUS")
#pragma push_macro("NOICONS")
#pragma push_macro("NOKEYSTATES")
#pragma push_macro("NOSYSCOMMANDS")
#pragma push_macro("NORASTEROPS")
#pragma push_macro("NOSHOWWINDOW")
#pragma push_macro("OEMRESOURCE")
#pragma push_macro("NOATOM")
#pragma push_macro("NOCLIPBOARD")
#pragma push_macro("NOCOLOR")
#pragma push_macro("NOCTLMGR")
#pragma push_macro("NODRAWTEXT")
#pragma push_macro("NOGDI")
#pragma push_macro("NOKERNEL")
#pragma push_macro("NOUSER")
#pragma push_macro("NONLS")
#pragma push_macro("NOMB")
#pragma push_macro("NOMEMMGR")
#pragma push_macro("NOMETAFILE")
#pragma push_macro("NOMINMAX")
#pragma push_macro("NOMSG")
#pragma push_macro("NOOPENFILE")
#pragma push_macro("NOSCROLL")
#pragma push_macro("NOSERVICE")
#pragma push_macro("NOSOUND")
#pragma push_macro("NOTEXTMETRIC")
#pragma push_macro("NOWH")
#pragma push_macro("NOWINOFFSETS")
#pragma push_macro("NOCOMM")
#pragma push_macro("NOKANJI")
#pragma push_macro("NOHELP")
#pragma push_macro("NOPROFILER")
#pragma push_macro("NODEFERWINDOWPOS")
#pragma push_macro("NOMCX")

#define WIN32_LEAN_AND_MEAN

#define NOGDICAPMASKS     // - CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOVIRTUALKEYCODES // - VK_*
#define NOWINMESSAGES     // - WM_*, EM_*, LB_*, CB_*
#define NOWINSTYLES       // - WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
#define NOSYSMETRICS      // - SM_*
#define NOMENUS           // - MF_*
#define NOICONS           // - IDI_*
#define NOKEYSTATES       // - MK_*
#define NOSYSCOMMANDS     // - SC_*
#define NORASTEROPS       // - Binary and Tertiary raster ops
#define NOSHOWWINDOW      // - SW_*
#define OEMRESOURCE       // - OEM Resource values
#define NOATOM            // - Atom Manager routines
#define NOCLIPBOARD       // - Clipboard routines
#define NOCOLOR           // - Screen colors
#define NOCTLMGR          // - Control and Dialog routines
#define NODRAWTEXT        // - DrawText() and DT_*
#define NOGDI             // - All GDI defines and routines
#define NOKERNEL          // - All KERNEL defines and routines
//#define NOUSER            // - All USER defines and routines
#define NONLS             // - All NLS defines and routines
//#define NOMB              // - MB_#define and MessageBox()
#define NOMEMMGR          // - GMEM_*, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE        // - typedef METAFILEPICT
#define NOMINMAX          // - Macros min(a,b) and max(a,b)
#define NOMSG             // - typedef MSG and associated routines
#define NOOPENFILE        // - OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL          // - SB_#define and scrolling routines
#define NOSERVICE         // - All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND           // - Sound driver routines
#define NOTEXTMETRIC      // - typedef TEXTMETRIC and associated routines
#define NOWH              // - SetWindowsHook and WH_*
#define NOWINOFFSETS      // - GWL_*, GCL_*, associated routines
#define NOCOMM            // - COMM driver routines
#define NOKANJI           // - Kanji support stuff.
#define NOHELP            // - Help engine interface.
#define NOPROFILER        // - Profiler interface.
#define NODEFERWINDOWPOS  // - DeferWindowPos routines
#define NOMCX             // - Modem Configuration Extensions

#include <Windows.h>

#undef near
#undef NEAR
#undef far
#undef FAR

#pragma pop_macro("WIN32_LEAN_AND_MEAN")
#pragma pop_macro("NOGDICAPMASKS")
#pragma pop_macro("NOVIRTUALKEYCODES")
#pragma pop_macro("NOWINMESSAGES")
#pragma pop_macro("NOWINSTYLES")
#pragma pop_macro("NOSYSMETRICS")
#pragma pop_macro("NOMENUS")
#pragma pop_macro("NOICONS")
#pragma pop_macro("NOKEYSTATES")
#pragma pop_macro("NOSYSCOMMANDS")
#pragma pop_macro("NORASTEROPS")
#pragma pop_macro("NOSHOWWINDOW")
#pragma pop_macro("OEMRESOURCE")
#pragma pop_macro("NOATOM")
#pragma pop_macro("NOCLIPBOARD")
#pragma pop_macro("NOCOLOR")
#pragma pop_macro("NOCTLMGR")
#pragma pop_macro("NODRAWTEXT")
#pragma pop_macro("NOGDI")
#pragma pop_macro("NOKERNEL")
#pragma pop_macro("NOUSER")
#pragma pop_macro("NONLS")
#pragma pop_macro("NOMB")
#pragma pop_macro("NOMEMMGR")
#pragma pop_macro("NOMETAFILE")
#pragma pop_macro("NOMINMAX")
#pragma pop_macro("NOMSG")
#pragma pop_macro("NOOPENFILE")
#pragma pop_macro("NOSCROLL")
#pragma pop_macro("NOSERVICE")
#pragma pop_macro("NOSOUND")
#pragma pop_macro("NOTEXTMETRIC")
#pragma pop_macro("NOWH")
#pragma pop_macro("NOWINOFFSETS")
#pragma pop_macro("NOCOMM")
#pragma pop_macro("NOKANJI")
#pragma pop_macro("NOHELP")
#pragma pop_macro("NOPROFILER")
#pragma pop_macro("NODEFERWINDOWPOS")
#pragma pop_macro("NOMCX")