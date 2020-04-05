#pragma once

// External Include
#include <Windows.h>

// Engine Include
#include "Core/Core.h"
#include "Core/ISubSystem.h"


namespace Fluent
{
	
	class TimeCounter final : public ISubSystem
	{
	public:

		explicit TimeCounter(const std::shared_ptr<RuntimeStorage>& inStorage) noexcept;
		virtual ~TimeCounter() = default;

		bool Initialize() override;
		void Update(f32 prevDeltaTime) override;

	private:

		__int64 mFrequency = 0;
		__int64 mStartTime = 0;
		f32 mTickPerMs = 0.0f;
		f32 mFrameTime = 0.0f;
		f32 mFramePerSecond = 0.0f;

	public:

		FORCEINLINE f32 GetFPS() const { return mFramePerSecond; }
		FORCEINLINE f32 GetDeltaTime() const { return mFrameTime; }

	};

}
