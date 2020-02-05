

#include "Window.h"
#include "Editor.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Create editor
    Editor editor;

    // Create window
    Window::Create(hInstance, TEXT("FluentEngine"));
    Window::Show();

    // Tick
    while (Window::Tick())
    {
        editor.Update();
    }

    // Exit
    Window::Destroy();
    return 0;
}
