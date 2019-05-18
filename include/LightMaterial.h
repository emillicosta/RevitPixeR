#pragma once
#include "ShapeObject.h"
#include "Texture.h"
#include "MyMaterial.h"
class LightMaterial :
	public MyMaterial
{
public:
	Texture* emit;

	LightMaterial(Texture* emit_);

	virtual bool scatter(const Ray& r_, const HitRecord& ht_, vec3& attenuation_, Ray& scattered_ray) const;

	virtual vec3 emitted(float u, float v, const vec3& p) const;
};
