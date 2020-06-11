#pragma once
#include "Common.h"

class CFileSystem final
{
private:
	inline static wchar* ms_full_input_path = nullptr; // The full path of the input file
	inline static wchar* ms_filename        = nullptr; // A pointer to the filename part of the full path
	inline static wchar* ms_extension       = nullptr; // A pointer to the '.' of the file extension in the full path
	inline static unsigned int ms_pathlen;             // The length of the full path string

public:
	~CFileSystem() { delete[] ms_full_input_path; }

	static bool Initialize(const wchar* inputFileName);
	static bool CreateFolder(const char* newDir);
	static bool CreateFolder(const wchar* newDir);
	static bool ChangeFolder(const char* newDir);
	static bool ChangeFolder(const wchar* newDir);
	static bool CreateAndChangeFolder(const char* newDir);
	static bool CreateAndChangeFolder(const wchar* newDir);
	static bool ResetFolder();

	static const wchar* GetInputFilePath()
	{
		if (ms_extension) *ms_extension = L'.';
		return ms_full_input_path;
	}
	static const wchar* GetInputFileName()
	{
		if (ms_extension) *ms_extension = L'.';
		return ms_filename;
	}
	static const wchar* GetInputFileNameNoExtension()
	{
		if (ms_extension) *ms_extension = L'\0';
		return ms_filename;
	}
	static unsigned int GetInputFileNameNoExtensionLength()
	{
		if (ms_extension)
			return ms_extension - ms_filename;
		return ms_pathlen - (ms_filename - ms_full_input_path);
	}
};