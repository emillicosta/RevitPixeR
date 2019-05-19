#pragma once
#include "CubeObject.h"
#include "TriangleObject.h"
#include "ShapeObject.h"
#include "KDNode.h"
class MeshObject :
	public ShapeObject
{
public:
	CubeObject* bbox;

	KDNode* node = new KDNode();

	std::vector<TriangleObject*> triangles;

	MeshObject();
	MeshObject(MyMaterial* m_, std::vector<TriangleObject*> triangles_, CubeObject* bbox_);

	//void insertNode() const;

	virtual bool hit(const Ray& r_, float  t_min_, float  t_max_, HitRecord& ht_) const;
};