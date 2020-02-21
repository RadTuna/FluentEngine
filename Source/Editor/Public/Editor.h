#pragma once

// External Include
#include <memory>

// Editor Include
#include "Window.h"


namespace Fluent
{
	
	class Editor
	{
	public:

		Editor() = default;
		~Editor() = default;

		void OnWindowMessage(const WindowData& windowData);
		void Update();

	private:

		std::unique_ptr<class Runtime> mRuntime;
		bool mEditorInitialized = false;
		
	};

}

