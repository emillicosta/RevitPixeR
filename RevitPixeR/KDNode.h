#include <algorithm>
#include "CubeObject.h"
#include "TriangleObject.h"
#include <functional>
#include <array>
#include <iostream>
#pragma once
class KDNode
{
public:
	CubeObject* bbox;
	KDNode* left;
	KDNode* right;
	std::vector<TriangleObject*> triangles;

	KDNode();

	KDNode* build(std::vector<TriangleObject*>& tris, int depth)const;

	bool hit(KDNode* node, const Ray& r_, float  t_min_, float  t_max_, HitRecord& ht_) const;

	/*bool ordenarX(TriangleObject* i, TriangleObject* j);
	bool ordenarY(TriangleObject* i, TriangleObject* j);
	bool ordenarZ(TriangleObject* i, TriangleObject* j);*/
};
