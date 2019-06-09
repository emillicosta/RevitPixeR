#include "MyMaterial.h"
#include "Texture.h"
#include "ShapeObject.h"
#include "ConstantTexture.h"
#pragma once
class DifuseMaterial : public MyMaterial
{
public:
	Texture* texture;
	DifuseMaterial();
	DifuseMaterial(Texture* albedo_);
	~DifuseMaterial();
	virtual bool scatter(const Ray& r_, const HitRecord& ht_, vec3& attenuation_, Ray& scattered_ray) const;
	virtual vec3 emitted(float u, float v, const vec3& p) const {
		return vec3(0, 0, 0);
	}

protected:

	vec3 random_in_unit_sphere() const;
};

