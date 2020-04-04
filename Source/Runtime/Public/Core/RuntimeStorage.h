#pragma once

// Engine Include
#include "Core/Core.h"
#include "TypeDefinition.h"


namespace Fluent
{

	struct WindowData
	{
		HWND Handle = nullptr;
		HINSTANCE Instance = nullptr;
		uint32 Message = 0;
		uint32 ScreenWidth = 0;
		uint32 ScreenHeight = 0;
		uint32 MonitorWidth = 0;
		uint32 MonitorHeight = 0;
		uint64 WParam = 0;
		int64 LParam = 0;
	};
	
	class RuntimeStorage final
	{
	public:

		explicit RuntimeStorage() = default;
		~RuntimeStorage() = default;

	public:

		WindowData mWindowData;
	};

}
