#pragma once
#include "MyMaterial.h"
#include "Texture.h"
#include "ShapeObject.h"
class MetalMaterial :
	public MyMaterial
{
public:
	float fuzziness;

	MetalMaterial(Texture* albedo_, float fuzz);

	virtual bool scatter(const Ray& r_, const HitRecord& ht_, vec3& attenuation_, Ray& scattered_ray) const;
	virtual vec3 emitted(float u, float v, const vec3& p) const;

protected:

	vec3 reflect(const vec3 v, const vec3 n) const;

	vec3 random_in_unit_sphere() const;
};

