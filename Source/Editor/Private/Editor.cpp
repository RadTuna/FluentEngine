
#include "Editor.h"

using namespace Fluent;

void Editor::OnWindowMessage(const WindowData& windowData)
{
	if (!mEditorInitialized)
	{
		mRuntime = std::make_unique<Runtime>(windowData);
		
		const bool result = mRuntime->Initialize();
		Assert(result);

		mEditorInitialized = true;
	}

	mRuntime->SetWindowData(windowData);
}

void Editor::Update()
{
	if (mEditorInitialized)
	{
		mRuntime->Update();
	}
}

