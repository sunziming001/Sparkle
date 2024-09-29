#ifndef SPOINT_H
#define SPOINT_H


#include <stdint.h>

typedef struct SPoint2D
{
	int32_t x = 0;
	int32_t y = 0;
}SPoint2D;

typedef struct SPointF3D
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
}SPointF3D;

#endif