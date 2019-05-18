#include "pch.h"
#include "LightMaterial.h"


LightMaterial::LightMaterial(Texture* emit_) 
{
	emit = emit_;
}

vec3 LightMaterial::emitted(float u, float v, const vec3& p) const
{
	return emit->value(u, v, p);
}



bool LightMaterial::scatter(const Ray& r_, const HitRecord& ht_, vec3& attenuation_, Ray& scattered_ray) const
{
	return false;
}