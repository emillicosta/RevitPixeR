#include "pch.h"
#include "DifuseMaterial.h"


DifuseMaterial::DifuseMaterial()
{
}

DifuseMaterial::DifuseMaterial(Texture* albedo_)
{
	texture = albedo_;
	MyMaterial::ks = rgb(0, 0, 0);
	MyMaterial::ka = rgb(0, 0, 0);
	MyMaterial::alpha = 0;
}


DifuseMaterial::~DifuseMaterial()
{
}

vec3 DifuseMaterial::random_in_unit_sphere() const
{
	vec3 p;
	do {
		p = 2.0f * vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX) - vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0);

	return p;
}

bool DifuseMaterial::scatter(const Ray & r_, const HitRecord & ht_, vec3 & attenuation_, Ray & scattered_ray) const
{
	vec3 p_ = random_in_unit_sphere();
	vec3 target = ht_.p + ht_.normal + p_;
	scattered_ray = Ray(ht_.p, target - ht_.p);
	attenuation_ = texture->value(ht_.u, ht_.v, ht_.p);//MyMaterial::albedo->value(0, 0, ht_.p);

	return true;
}
