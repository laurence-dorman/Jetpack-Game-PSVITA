#include "utilities.h"
#include <cassert>

float clamp(const float v, const float lo, const float hi)
{
	assert(!(hi < lo));
	return (v < lo) ? lo : (hi < v) ? hi : v;
}
