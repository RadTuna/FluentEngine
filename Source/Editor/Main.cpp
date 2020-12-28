
// External include
#include <iostream>
#include <tchar.h>

// Editor Include
#include "Window.h"
#include "Editor.h"

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif


static Fluent::Editor gEditor;

void MessageCallback(const Fluent::WindowMsg& windowMsg)
{
    gEditor.OnWindowMessage(windowMsg);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    using namespace Fluent;

    // Create window
    WindowData windowData;
    Window::Create(&windowData, hInstance, TXT("FluentEngine"));
    Window::Show();

    // initialize editor
    gEditor.Initialize(windowData);

    Window::gMsgCallback = MessageCallback;

    // Tick
    while (Window::Tick())
    {
        gEditor.Update();
    }

    // Exit
    Window::Destroy();
    return 0;
}
