
#include "Math/Math.h"

int32 Math::Sign(int32 value)
{
	if (value > 0)
	{
		return 1;
	}
	else if (value < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

float Math::Signf(float value, float epsilon)
{
	if (value > epsilon)
	{
		return 1.0f;
	}
	else if (value < -epsilon)
	{
		return -1.0f;
	}
	else
	{
		return 0.0f;
	}
}
