#include "Vec3.h"
#pragma once
class Texture
{
public:
	Texture() 
	{
	}
	virtual rgb value(float u, float v, const vec3& p) const = 0;
};



