#include "pch.h"
#include "LambertianShader.h"

/*
 * Generates a random ray
 */
vec3 LambertianShader::random_in_unit_sphere() const
{
	vec3 p;
	do {
		p = 2.0 * vec3((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX) - vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0);
	return p;
}

/*
 * Returns the color of the point hitted by the ray.
 */
rgb LambertianShader::color(const Ray & r_, float t_min, float t_max, int depth_) const
{
	HitRecord ht;

	// If the ray hitted anything
	if (Shader::hit_anything(r_, t_min, t_max, ht))
	{
		Ray scattered_ray = r_;
		rgb attenuation = rgb(1, 1, 1);
		vec3 emitted = ht.mat->emitted(0, 0, ht.p);
		if (depth_ > 0 && ht.mat->scatter(r_, ht, attenuation, scattered_ray)) {
			return emitted + attenuation* color(scattered_ray, t_min, t_max, depth_ - 1);
		}
		//return ht.mat->albedo->value(0, 0, ht.p);
		return emitted;
	}

	// Else, dye the pixel with the background color
	return Shader::vertical_interpolation(r_, world->bg->lower_left, world->bg->top_left);
	return Shader::interpolation_biline(r_);
}