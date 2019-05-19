#include "ShapeObject.h"
#include "MyMaterial.h"
#include "CubeObject.h"
#define error 0.00001
# define M_PI           3.14159265358979323846
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::UI;
#pragma once
class TriangleObject :
	public ShapeObject
{
public:
	bool backface_cull;

	point3 v0;
	point3 v1;
	point3 v2;

	CubeObject* bbox;
	TriangleObject(MyMaterial* m_, point3 v0_, point3 v1_, point3 v2_, bool backface_cull_ = false)
	{
		ShapeObject::origin = point3(0, 0, 0);
		ShapeObject::material = m_;

		v0 = v0_;
		v1 = v1_;
		v2 = v2_;
		backface_cull = backface_cull_;

		bbox = new CubeObject(m_, min_vector(v0, min_vector(v1, v2)), max_vector(v0, max_vector(v1, v2)));
	}

	virtual bool hit(const Ray& r_, float  t_min_, float  t_max_, HitRecord& ht_) const;

	point3 get_midpoint()const;

	std::vector<point3*> getPoints();
};