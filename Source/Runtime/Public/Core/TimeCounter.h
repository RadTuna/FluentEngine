#pragma once

// External Include
#include <Windows.h>

// Engine Include
#include "Core/Core.h"
#include "Core/ISubSystem.h"


namespace Fluent
{

	class TimeCounter : public ISubSystem
	{
	public:

		using Super = ISubSystem;

		explicit TimeCounter(const std::shared_ptr<RuntimeStorage>& inStorage) noexcept;
		virtual ~TimeCounter() = default;

		bool Initialize() override;
		void Update(float prevDeltaTime) override;

	private:

		__int64 mFrequency = 0;
		__int64 mStartTime = 0;
		float mTickPerMs = 0.0f;
		float mFrameTime = 0.0f;
		float mFramePerSecond = 0.0f;

	public:

		FORCEINLINE float GetFPS() const { return mFramePerSecond; }
		FORCEINLINE float GetDeltaTime() const { return mFrameTime; }

	};

}
