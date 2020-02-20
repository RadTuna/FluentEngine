
#include "Window.h"

namespace Fluent
{

	class Editor
	{
	public:

		Editor() = default;
		~Editor() = default;

		void OnWindowMessage(Window::WindowData& windowData);
		
		void Update();

	private:
	};

}

