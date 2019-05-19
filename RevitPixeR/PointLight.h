#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	point3 origin;

	PointLight(point3 origin_, rgb intensity_)
	{
		origin = origin_;
		Light::intensity = intensity_;
	}

	virtual vec3 getDirection(const point3& p_) const;
	virtual vec3 getIntensity() const;
};

