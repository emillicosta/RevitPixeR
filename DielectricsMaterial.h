#pragma once
#include "MyMaterial.h"
#include "ShapeObject.h"
#include "Texture.h"
class DielectricsMaterial :
	public MyMaterial
{
public:
	float ref_idx;

	DielectricsMaterial(Texture* albedo_, float ri);

	virtual bool scatter(const Ray& r_, const HitRecord& ht_, vec3& attenuation_, Ray& scattered_ray) const;
	virtual vec3 emitted(float u, float v, const vec3& p) const {
		return vec3(0, 0, 0);
	}
protected:

	vec3 reflect(const vec3 v, const vec3 n) const;

	vec3 random_in_unit_sphere() const;

	bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) const;

	float schlick(float cosine, float ref_idx) const;
};