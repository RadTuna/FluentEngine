#pragma once

// Engine Include
#include "Core/Core.h"


namespace Fluent
{

	enum class EWindowMsgType
	{
		Unknown,
	    DisplayChange,
		Size
	};

	struct WindowData
	{
		void* Handle = nullptr;
		void* Instance = nullptr;
		u32 ScreenWidth = 0;
		u32 ScreenHeight = 0;
		u32 MonitorWidth = 0;
		u32 MonitorHeight = 0;
	};

	struct WindowMsg
	{
	    EWindowMsgType MsgType = EWindowMsgType::Unknown;
		u64 WParam = 0;
		i64 LParam = 0;
	};
	
	class SystemStorage final
	{
	public:

		explicit SystemStorage() = default;
		~SystemStorage() = default;

		void SetWindowData(const WindowData& windowData);

		[[nodiscard]]
		inline const WindowData& GetWindowData() const { return mWindowData; }

		void SetWindowMessage(const WindowMsg& windowMsg); 

		[[nodiscard]]
		inline const WindowMsg& GetWindowMessage() const { return mWindowMsg; }


	private:

		WindowData mWindowData;
		WindowMsg mWindowMsg;

	};

}
