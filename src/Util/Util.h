#pragma once
#include "Pattern/Pattern.h"
#include "VFunc/VFunc.h"
#include <math.h>
#include <cmath>		//std::isfinite std::remainder
#include <cfloat>		//FLT_EPSILON
#include <algorithm>	//std::min std::max
#define M_RADPI		57.295779513082
#define PI			3.14159265358979323846
#define DEG2RAD(x)	((float)(x) * (float)((float)(PI) / 180.0f))
#define RAD2DEG(x)	((float)(x) * (float)(180.0f / (float)(PI)))