#include "Scene.h"
#include <math.h> 
#pragma once
class Shader
{
public:
public:
	virtual rgb color(const Ray& r_, float t_min, float t_max, int depth_) const = 0;
	bool hit_anything(const Ray& r_, float t_min_, float t_max_, HitRecord& ht_) const;

protected:

	Scene* world;

	rgb vertical_interpolation(const Ray& r_, const rgb& bottom_, const rgb& top_) const;
	rgb horizontal_interpolation(const Ray& r_, const rgb& bottom_, const rgb& top_) const;
	rgb vertical_interpolation3(const Ray& r_, const rgb& bottom_, const rgb& center_, const rgb& top_) const;
	rgb horizontal_interpolation3(const Ray& r_, const rgb& left_, const rgb& center_, const rgb& right_) const;
	rgb interpolation_biline(const Ray& r_) const;
};
