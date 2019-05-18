#include "Vec3.h"
#include "Texture.h"
#pragma once
class ConstantTexture : public Texture
{
public:
	rgb color;

	ConstantTexture();
	ConstantTexture(rgb color_);
	~ConstantTexture();
	virtual rgb value(float u = 0, float v = 0, const vec3& p = vec3()) const
	{
		return color;
	}
};

