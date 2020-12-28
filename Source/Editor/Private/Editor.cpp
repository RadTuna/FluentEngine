
#include "Editor.h"
#include "Core/Core.h"


namespace Fluent
{
    void Editor::Initialize(const WindowData& windowData)
    {
        if (!mEditorInitialized)
		{
			mRuntime = std::make_unique<Engine>(windowData);

			const bool result = mRuntime->Initialize();
			Assert(result);

			mEditorInitialized = true;
		}
    }

	void Editor::OnWindowMessage(const WindowMsg& windowMsg) const
	{	
		mRuntime->SetWindowMessage(windowMsg);
	}

	void Editor::Update()
	{
		if (mEditorInitialized)
		{
			mRuntime->Update();
		}
	}

}

