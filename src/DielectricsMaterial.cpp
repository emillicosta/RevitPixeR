#include "pch.h"
#include "DielectricsMaterial.h"


DielectricsMaterial::DielectricsMaterial(Texture* albedo_, float ri) {
	MyMaterial::albedo = albedo_;
	ref_idx = ri;
}

vec3 DielectricsMaterial::random_in_unit_sphere() const
{
	vec3 p;
	do {
		p = 2.0 * vec3((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX) - vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0);

	return p;
}



vec3 DielectricsMaterial::reflect(const vec3 v, const vec3 n) const
{
	float cosI = -dot(n, v);
	return v + 2 * cosI * n;
	//i = v; 
}


bool DielectricsMaterial::refract(const vec3 & v, const vec3 & n, float ni_over_nt, vec3 & refracted) const
{
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.f - (ni_over_nt * ni_over_nt * (1.f - (dt * dt)));
	if (discriminant > 0.f) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
		return false;
}


float DielectricsMaterial::schlick(float cosine, float ref_idx) const {
	float r = (1.f - ref_idx) / (1.f + ref_idx);
	r = r * r;
	return (r + (1.f - r) * std::pow((1.f - cosine), 5.f));
}



bool DielectricsMaterial::scatter(const Ray & r_, const HitRecord & ht_, vec3 & attenuation_, Ray & scattered_ray) const
{
	vec3 outward_normal, refracted;
	float ni_over_nt, reflect_prob, cosine;

	vec3 reflected = reflect(r_.get_direction(), ht_.normal);
	attenuation_ = MyMaterial::albedo->value(0, 0, vec3(0, 0, 0));

	float d = dot(r_.get_direction(), ht_.normal);

	if (dot(r_.get_direction(), ht_.normal) > 0)
	{
		outward_normal = -ht_.normal;
		ni_over_nt = ref_idx;
		// cosine = (d / r_.get_direction().length());
		// cosine = std::sqrt(1 - ((ref_idx *ref_idx) * (1 - (cosine * cosine))));
		cosine = ref_idx * dot(r_.get_direction(), ht_.normal) / r_.get_direction().length();
	}
	else
	{
		outward_normal = ht_.normal;
		ni_over_nt = 1.0 / ref_idx;
		cosine = -dot(r_.get_direction(), ht_.normal) / r_.get_direction().length();
	}

	if (refract(r_.get_direction(), outward_normal, ni_over_nt, refracted))
	{
		reflect_prob = schlick(cosine, ni_over_nt);
	}
	else
	{
		reflect_prob = 1.f;
	}

	if ((double)rand() / RAND_MAX < reflect_prob)
		scattered_ray = Ray(ht_.p, reflected);
	else
		scattered_ray = Ray(ht_.p, refracted);

	return true;
}



