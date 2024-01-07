#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <codecvt>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include <vector>
#include <cstdio>

DWORD GetProcessIdByName(const wchar_t* processName);
uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);