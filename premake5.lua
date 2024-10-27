workspace "g3DTZ"
	configurations {
		"Debug_LCSPSP",
		"Debug_LCSPS2",
		"Debug_VCSPSP",
		"Debug_VCSPS2",
		"Release_LCSPSP",
		"Release_LCSPS2",
		"Release_VCSPSP",
		"Release_VCSPS2"
	}
	characterset "MBCS"
	defines      "_CRT_SECURE_NO_WARNINGS"
	
	filter "*Debug*"
		defines  "DEBUG"
		symbols  "On"
		optimize "Off"
	
	filter "*Release*"
		symbols  "Off"
		optimize "On"
	
project "zlib"
	location    "projects\\zlib"
	kind        "StaticLib"
	language    "C"
	includedirs "modules\\zlib"
	files {
		"modules\\zlib\\*.h",
		"modules\\zlib\\*.c"
	}
	postbuildcommands {
		"if not exist \"$(SolutionDir)zlib\\include\" mkdir \"$(SolutionDir)zlib\\include\"",
		"for %%i in (zlib zconf) do copy /y \"$(SolutionDir)modules\\zlib\\%%i.h\" \"$(SolutionDir)zlib\\include\""
	}
	filter "*Debug*"
		targetdir "zlib\\lib\\Debug"
	filter "*Release*"
		targetdir "zlib\\lib\\Release"

project "g3DTZ"
	location       "projects\\g3DTZ"
	kind           "ConsoleApp"
	language       "C++"
	cppdialect     "C++20"
	sysincludedirs "zlib/include"
	includedirs {
		"$(ProjectDir)",
		"source",
		"source\\**"
	}
	files "source\\**.*"
	links "zlib"
	filter "*Debug*"
		targetdir "bin/Debug"
		syslibdirs "zlib/lib/Debug"
	filter "*Release*"
		targetdir "bin/Release"
		syslibdirs "zlib/lib/Release"
	filter "*LCSPSP*"
		defines {
			"LCS",
			"PSP"
		}
		debugargs "\"C:/Users/guard3/Desktop/My G3/Grand Theft Auto/DTZ/lcs_psp.dtz\""
		targetname "lcs_psp"
	filter "*LCSPS2*"
		defines {
			"LCS",
			"PS2"
		}
		debugargs "\"C:/Users/guard3/Desktop/My G3/Grand Theft Auto/DTZ/lcs_ps2.dtz\""
		targetname "lcs_ps2"
	filter "*VCSPSP*"
		defines {
			"VCS",
			"PSP"
		}
		debugargs "\"C:/Users/guard3/Desktop/My G3/Grand Theft Auto/DTZ/vcs_psp.dtz\""
		targetname "vcs_psp"	
	filter "*VCSPS2*"
		defines {
			"VCS",
			"PS2"
		}
		debugargs "\"C:/Users/guard3/Desktop/My G3/Grand Theft Auto/DTZ/vcs_ps2.dtz\""
		targetname "vcs_ps2"