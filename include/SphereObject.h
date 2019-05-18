#include "ShapeObject.h"
#include "MyMaterial.h"
#pragma once
class SphereObject : public ShapeObject 
{
public:
	float radius;

	SphereObject(MyMaterial* m_, point3 center_ = point3(), float rad_ = 0.0)
	{
		ShapeObject::origin = center_;
		ShapeObject::material = m_;
		radius = rad_;
	}
	~SphereObject();
	virtual bool hit(const Ray& r_, float  t_min_, float  t_max_, HitRecord& ht_) const;
};

