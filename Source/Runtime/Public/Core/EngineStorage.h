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
		u32 Message = 0;
		u32 ScreenWidth = 0;
		u32 ScreenHeight = 0;
		u32 MonitorWidth = 0;
		u32 MonitorHeight = 0;
		u64 WParam = 0;
		i64 LParam = 0;
	};
	
	class EngineStorage final
	{
	public:

		explicit EngineStorage() = default;
		~EngineStorage() = default;

	public:

		WindowData mWindowData;
	};

}
