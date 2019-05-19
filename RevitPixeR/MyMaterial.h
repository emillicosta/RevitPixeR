#include "Texture.h"
#include "Vec3.h"
#include "Ray.h"
#include <vector>
#pragma once
class MyMaterial
{
public:
	Texture* albedo; //Kd o difuso.
	rgb ks;
	rgb ka;
	rgb km;
	std::vector<rgb> gradient;
	float alpha;
	std::vector<float> angles;

	virtual bool scatter(const Ray& r, const struct HitRecord& ht, vec3& attenuation, Ray& scatterd) const = 0;

	virtual vec3 emitted(float u, float v, const vec3& p) const = 0;
};
