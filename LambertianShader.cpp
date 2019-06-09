#include "pch.h"
#include "LambertianShader.h"

/*
 * Generates a random ray
 */
vec3 LambertianShader::random_in_unit_sphere() const
{
	vec3 p;
	do {
		p = 2.0f * vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX) - vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0);
	return p;
}

/*
 * Returns the color of the point hitted by the ray.
 */
rgb LambertianShader::color(const Ray & r_, float t_min, float t_max, int depth_) const
{
	HitRecord ht;
	HitRecord ht_s;

	// If the ray hitted anything
	if (Shader::hit_anything(r_, t_min, t_max, ht))
	{
		DielectricsMaterial* glass = dynamic_cast<DielectricsMaterial*>(ht.mat);
		if (world->lights.size() > 0 && glass == nullptr) {
			rgb ip = rgb(0, 0, 0);
			rgb sombra = rgb(1, 1, 1);
			for each (Light * light in world->lights)
			{
				vec3 l = light->getDirection(ht.p);
				auto sr = Ray(ht.p, l);
				DielectricsMaterial* vidro = nullptr;
				if (Shader::hit_anything(sr, 0.001f, 1, ht_s)) {
					vidro = dynamic_cast<DielectricsMaterial*>(ht_s.mat);
					if (vidro == nullptr)
						sombra = world->ambientLight;
					else
					{
						Ray sr1 = Ray(ht_s.p, l);
						HitRecord ht_s1;
						if (Shader::hit_anything(sr1, 0.001f, 1, ht_s1)) {
							vidro = dynamic_cast<DielectricsMaterial*>(ht_s1.mat);
							if (vidro == nullptr)
								sombra = world->ambientLight;
							else {
								Ray sr2 = Ray(ht_s1.p, l);
								HitRecord ht_s2;
								if (Shader::hit_anything(sr2, 0.001f, 1, ht_s2)) {
									//vidro = dynamic_cast<DielectricsMaterial*>(ht_s1.mat);
									//if (vidro == nullptr)
										sombra = world->ambientLight;
								}
							}
						}
					}
				}
				//if (!Shader::hit_anything(sr, 0.001f, 1, ht_s) || vidro != nullptr) {
				Ray scattered_ray;
				rgb attenuation;
				vec3 emitted = ht.mat->emitted(ht.u, ht.v, ht.p);
				if (depth_ > 0 && ht.mat->scatter(r_, ht, attenuation, scattered_ray)) {
					ip += attenuation * sombra * light->getIntensity();
					ip += emitted + attenuation * color(scattered_ray, t_min, t_max, depth_ - 1);
					return ip;
				}
				return emitted;
				/*}
				else
				{
					Ray scattered_ray;
					rgb attenuation;
					ht.mat->scatter(r_, ht, attenuation, scattered_ray);
					ip += attenuation * world->ambientLight;
				}*/
			}
		}
		else
		{
			Ray scattered_ray = r_;
			rgb attenuation = rgb(1, 1, 1);
			vec3 emitted = ht.mat->emitted(0, 0, ht.p);
			if (depth_ > 0 && ht.mat->scatter(r_, ht, attenuation, scattered_ray)) {
				return emitted + attenuation * color(scattered_ray, t_min, t_max, depth_ - 1);
			}

			return emitted;
		}
	}

	// Else, dye the pixel with the background color
	return Shader::vertical_interpolation(r_, world->bg->lower_left, world->bg->top_left);
	return Shader::interpolation_biline(r_);
}
