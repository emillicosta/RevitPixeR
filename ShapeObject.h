#include "Vec3.h"
#include "Ray.h"
#include "MyMaterial.h"
#pragma once
struct HitRecord
{
	point3 p;
	float t;
	//texture img
	float u= 0;
	float v= 0;
	vec3 normal;
	MyMaterial* mat;
};

class ShapeObject
{
protected:
	point3 origin;
	MyMaterial* material;
public:
public:
	virtual bool hit(const Ray& r_, float t_min_, float t_max_, HitRecord& ht_) const = 0;
};

