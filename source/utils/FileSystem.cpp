#include "FileSystem.h"
#include "Win32.h"
#include "Utils.h"
#include <stdlib.h>

/* A simple object that automatically frees the path buffers on exit */
static CFileSystem __filesystem_auto_cleanup__;

bool CFileSystem::Initialize(const wchar* input)
{
	/* Get full input file path */
	DWORD pathlen;
	ms_full_input_path = new wchar[MAX_PATH];
	if ((pathlen = GetFullPathNameW(input, MAX_PATH, ms_full_input_path, &ms_filename)) == 0)
		goto label_error;
	if (pathlen > MAX_PATH)
	{
		delete[] ms_full_input_path;
		ms_full_input_path = new wchar[pathlen];
		if ((pathlen = GetFullPathNameW(input, pathlen, ms_full_input_path, &ms_filename)) == 0)
		{
		label_error:
			ErrorBox(L"%ls\n%s", input, "The specified path is invalid.");
			return false;
		}
	}
	ms_pathlen = pathlen;

	/* Get default directory from file path */
	for (wchar* p = ms_full_input_path + pathlen - 1; p != ms_filename; --p)
	{
		if (*p == L'.')
		{
			*p = L'\0';
			ms_extension = p;
			break;
		}
	}

	/* Create output directory and go into it */
	if (!CreateAndChangeFolder(ms_full_input_path))
	{
		ErrorBox(L"%ls\n%s", ms_full_input_path, "Cannot create output folder.");
		return false;
	}

	return true;	
}

bool CFileSystem::CreateFolder(const char* newDir)
{
	if (!CreateDirectoryA(newDir, NULL))
		if (GetLastError() != ERROR_ALREADY_EXISTS)
			return false;
	return true;
}

bool CFileSystem::CreateFolder(const wchar* newDir)
{
	if (!CreateDirectoryW(newDir, NULL))
		if (GetLastError() != ERROR_ALREADY_EXISTS)
			return false;
	return true;
}

bool CFileSystem::ChangeFolder(const char* newDir)
{
	return SetCurrentDirectoryA(newDir);
}

bool CFileSystem::ChangeFolder(const wchar* newDir)
{
	return SetCurrentDirectoryW(newDir);
}

bool CFileSystem::CreateAndChangeFolder(const char* newDir)
{
	if (!CreateDirectoryA(newDir, NULL))
		if (GetLastError() != ERROR_ALREADY_EXISTS)
			return false;
	return SetCurrentDirectoryA(newDir);
}

bool CFileSystem::CreateAndChangeFolder(const wchar* newDir)
{
	if (!CreateDirectoryW(newDir, NULL))
		if (GetLastError() != ERROR_ALREADY_EXISTS)
			return false;
	return SetCurrentDirectoryW(newDir);
}

bool CFileSystem::ResetFolder()
{
	if (ms_extension) *ms_extension = L'\0';
	return SetCurrentDirectoryW(ms_full_input_path);
}