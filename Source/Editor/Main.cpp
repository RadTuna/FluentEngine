
// Editor Include
#include "Window.h"
#include "Editor.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    using namespace Fluent;
	
    // Create editor
    Editor editor;

    // Create window
    Window::Create(hInstance, TEXT("FluentEngine"));
    Window::Show();

    Window::gWindowMessage = [&editor](const WindowData& windowData) -> void
    {
        editor.OnWindowMessage(windowData);
    };
	
    // Tick
    while (Window::Tick())
    {
        editor.Update();
    }

    // Exit
    Window::Destroy();
    return 0;
}
