
#include "Core/TimeCounter.h"


namespace Fluent
{

	TimeCounter::TimeCounter(const std::shared_ptr<SystemStorage>& inStorage) noexcept
		: ISubModule(inStorage)
	{
	}

	bool TimeCounter::Initialize()
	{
		// 현재 시스템이 QueryPerformanceCounter를 지원하는 지 확인
		QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&mFrequency));
		if (mFrequency == 0)
		{
			return false;
		}

		mTickPerMs = static_cast<float>(mFrequency / 1000);

		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mStartTime));

		return true;
	}

	void TimeCounter::Update(float prevDeltaTime)
	{
		i64 currentTime;
		float timeDifference;

		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentTime));

		timeDifference = static_cast<float>(currentTime - mStartTime);
		mFrameTime = timeDifference / mTickPerMs;
		mFramePerSecond = mFrequency / timeDifference;

		mStartTime = currentTime;
	}

}
