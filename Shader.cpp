#include "pch.h"
#include "Shader.h"

/*
 * Verifies if the ray hitted any object
 */
bool Shader::hit_anything(const Ray& r_, float t_min_, float t_max_, HitRecord& ht_) const
{

	HitRecord temp_ht;

	bool hit_anything = false;
	float closest_so_far = t_max_;

	for each (ShapeObject*  o in world->list) {
		if (o->hit(r_, t_min_, closest_so_far, temp_ht)) {
			hit_anything = true;
			closest_so_far = temp_ht.t;
			ht_ = temp_ht;
		}
	}

	return hit_anything;
}

/*
 * Calculates the vertical interpolation between 2 colors
 * Only works with the aspect ratio [2:1]
 */
rgb Shader::vertical_interpolation(const Ray& r_, const rgb& bottom_, const rgb& top_) const
{
	// Make the ray a vector in the same direction.     
	vec3 ray = unit_vector(r_.get_direction());

	// Take only the vertical component, since the lerp has to interpolate colors verticaly     
	float ray_y = ray.z(); // this component might assume values ranging from -1 to 1     

	// Normalize the ray's vertical component to the range [0;1]     
	float t = (1 + ray_y) * 0.5f;

	// Use linear interpolation (lerp) between the colors that compose the background     
	rgb result = bottom_ * (1 - t) + top_ * (t);

	return result;
}

/*
 * Calculates the vertical interpolation between 3 colors
 * Only works with the aspect ratio [2:1]
 */
rgb Shader::vertical_interpolation3(const Ray & r_, const rgb & bottom_, const rgb & center_, const rgb & top_) const
{
	// Make the ray a vector in the same direction.     
	vec3 ray = unit_vector(r_.get_direction());

	// Take only the vertical component, since the lerp has to interpolate colors verticaly     
	float ray_y = ray.y(); // this component might assume values ranging from -1 to 1     

	// Normalize the ray's vertical component to the range [0;1]     
	float t = (1 + ray_y) * 0.5f;

	// Use linear interpolation (lerp) between the colors that compose the background     
	rgb result;

	if (t <= 0.5)
		result = bottom_ * t * 2.0f + center_ * (0.5f - t) * 2.0f;
	else
		result = center_ * (t - 0.5f) * 2.0f + top_ * (1.0f - t) * 2.0f;

	return result;
}

/*
 * Calculates the horizontal interpolation between 2 colors
 * Only works with the aspect ratio [2:1]
 */
rgb Shader::horizontal_interpolation(const Ray & r_, const rgb & left_, const rgb & right_) const
{
	// Make the ray a vector in the same direction.     
	vec3 ray = unit_vector(r_.get_direction());

	// Take only the horizontal component     
	float ray_x = ray.x(); // this component might assume values ranging from -2 to 2     

	// Normalize the ray's horizontal component to the range [0;1]     
	float t = (2 + ray_x) * 0.25f;

	// Use linear interpolation (lerp) between the colors that compose the background     
	rgb result = left_ * (1 - t) + right_ * (t);

	return result;
}

/*
 * Calculates the horizontal interpolation between 3 colors
 * Only works with the aspect ratio [2:1]
 */
rgb Shader::horizontal_interpolation3(const Ray & r_, const rgb & left_, const rgb & center_, const rgb & right_) const
{
	// Make the ray a vector in the same direction.     
	vec3 ray = unit_vector(r_.get_direction());

	// Take only the horizontal component     
	float ray_x = ray.x(); // this component might assume values ranging from -2 to 2     

	// Normalize the ray's horizontal component to the range [0;1]     
	float t = (2 + ray_x) * 0.25f;

	// Use linear interpolation (lerp) between the colors that compose the background     
	rgb result;

	if (t <= 0.5f)
		result = left_ * t * 2.0f + center_ * (0.5f - t) * 2.0f;
	else
		result = center_ * (t - 0.5f) * 2.0f + right_ * (1.0f - t) * 2.0f;

	return result;
}

rgb Shader::interpolation_biline(const Ray & r_) const
{

	vec3 unit_ray = r_.get_direction();
	float unit_ray_y = unit_ray.y();
	float unit_ray_x = unit_ray.x();
	float a = (0.5f * unit_ray_y) + 0.5f;
	float t = a;//max(0.f, a);
	float b = (0.25f * unit_ray_x) + 0.5f;
	float u = b;//max(0.f, (b));
	rgb result = (world->bg->lower_left * (1 - t) * (1 - u) +
		world->bg->top_left * t * (1 - u) +
		world->bg->lower_right * (1 - t) * (u)+
		world->bg->top_right * (t) * (u)
		);

	return result;
}
