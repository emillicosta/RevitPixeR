#pragma once
#include "ShapeObject.h"
class CubeObject :
	public ShapeObject
{
public:
	point3 maxi;
	point3 mini;


	CubeObject();
	CubeObject(MyMaterial* m_, point3 min_, point3 max_);

	CubeObject* wrap(CubeObject* node, CubeObject* bbox_tri)const;

	virtual bool hit(const Ray& r_, float  t_min_, float  t_max_, HitRecord& ht_) const;
};

