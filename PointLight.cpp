#include "pch.h"
#include "PointLight.h"


vec3 PointLight::getDirection(const point3& p_) const
{
	return origin - p_;
}

vec3 PointLight::getIntensity() const
{
	return Light::intensity;
}