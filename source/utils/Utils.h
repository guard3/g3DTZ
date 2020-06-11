#pragma once
#include "Common.h"

/* printf style functions for error message boxes */
void ErrorBox(const char* text, ...);
void ErrorBox(const wchar* text, ...);

inline void ErrorBoxCannotCreateFile(const char* text)
{
	ErrorBox("Cannot create %s%s", text, "");
}
inline void ErrorBoxCannotCreateFolder(const char* text)
{
	ErrorBox("Cannot create %s%s", text, " folder");
}

/*
 * A float to cstring with precision up to 2 decimal digits
 * Guarantees at least one decimal digit in the output string
 */
const char* Precision(float value);
const char* Precision3(float value);
const char* Precision5(float value);
const char* PrecisionAny(float value);