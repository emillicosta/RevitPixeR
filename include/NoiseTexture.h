#pragma once
#include "Texture.h"
#include "Perlin.h"
class NoiseTexture :
	public Texture
{
public:
	Perlin* noise = new Perlin();
	float scale;

	NoiseTexture() {
		scale = 1;
	}

	NoiseTexture(float scale_) {
		scale = scale_;
	}

	virtual rgb value(float u = 0, float v = 0, const vec3& p = vec3()) const
	{
		//return vec3(1,1,1)*0.5*(1+noise.turb(scale*p));
		//return vec3(1,1,1)*noise.noise(scale*p);
		//return vec3(1,1,1)* 0.5 * (1 + std::sin(scale * p.x() + 5*noise.turb(scale * p)));
		return vec3(1, 0, 0)* 0.5* (1 + std::sin(scale * p.z() + 10 * noise->turb(p)));
	}
};



