#include "SFloat.h"
#include <cmath>

bool SPARKLE_API sFloatIsNull(float v)
{
	return std::fabs(v) <= 0.00001f;
}
