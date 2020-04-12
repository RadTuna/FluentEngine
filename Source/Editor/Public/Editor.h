#pragma once

// External Include
#include <memory>

// Editor Include
#include "Window.h"

// Engine Include
#include "Core/Engine.h"

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

		std::unique_ptr<Engine> mRuntime;
		bool mEditorInitialized = false;
		
	};

}

