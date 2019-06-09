#pragma once
#include "Texture.h"
class CheckerTexture :
	public Texture
{
public:
	Texture* odd;
	Texture* even;

	CheckerTexture();
	CheckerTexture(Texture* t0, Texture* t1)
	{
		even = t0;
		odd = t1;
	}


	virtual rgb value(float u = 0, float v = 0, const vec3& p = vec3()) const
	{
		float sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
		if (sines < 0) {
			return odd->value(u, v, p);
		}
		else
		{
			return even->value(u, v, p);
		}
	}
};


