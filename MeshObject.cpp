#include "pch.h"
#include "MeshObject.h"


MeshObject::MeshObject()
{
}

MeshObject::MeshObject(MyMaterial* m_, std::vector<TriangleObject*> triangles_, CubeObject* bbox_)
{
	ShapeObject::material = m_;
	triangles = triangles_;
	bbox = bbox_;
	node = node->build(triangles_, 0);
}

bool MeshObject::hit(const Ray& r_, float  t_min_, float  t_max_, HitRecord& ht_) const
{

	if (bbox->hit(r_, t_min_, t_max_, ht_)) {
		return node->hit(node, r_, t_min_, t_max_, ht_);
	}
	return false;
}