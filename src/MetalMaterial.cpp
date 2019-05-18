#include "pch.h"
#include "MetalMaterial.h"


MetalMaterial::MetalMaterial(Texture* albedo_, float fuzz) {
	MyMaterial::albedo = albedo_;
	fuzziness = fuzz;
}

vec3 MetalMaterial::emitted(float u, float v, const vec3& p) const {
	return vec3(0, 0, 0);
}

vec3 MetalMaterial::random_in_unit_sphere() const
{
	vec3 p;
	do {
		p = 2.0 * vec3((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX) - vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0);

	return p;
}



vec3 MetalMaterial::reflect(const vec3 v, const vec3 n) const
{
	return v - 2 * dot(v, n) * n;
}

bool MetalMaterial::scatter(const Ray & r_, const HitRecord & ht_, vec3 & attenuation_, Ray & scattered_ray) const
{
	vec3 reflected = reflect(unit_vector(r_.get_direction()), ht_.normal);
	scattered_ray = Ray(ht_.p, reflected + fuzziness * random_in_unit_sphere());
	attenuation_ = MyMaterial::albedo->value(0, 0, vec3(0, 0, 0));

	return (dot(scattered_ray.get_direction(), ht_.normal) > 0);
}