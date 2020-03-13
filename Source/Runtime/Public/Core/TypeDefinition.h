#pragma once

#include <Windows.h>

// Engine Include
#include "Core/Core.h"


struct WindowData
{
	HWND Handle = nullptr;
	HINSTANCE Instance = nullptr;
	uint32 Message = 0;
	float ScreenWidth = 0;
	float ScreenHeight = 0;
	uint32 MonitorWidth = 0;
	uint32 MonitorHeight = 0;
	uint64 WParam = 0;
	int64 LParam = 0;
};
