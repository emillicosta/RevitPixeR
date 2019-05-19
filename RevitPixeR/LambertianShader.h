#pragma once
#include "Shader.h"
#include "DielectricsMaterial.h"
#include <cmath>  

using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::UI;
class LambertianShader :
	public Shader
{
public:
public:

	LambertianShader(Scene* world_)
	{
		Shader::world = world_;
	}

	virtual rgb color(const Ray& r_, float t_min, float t_max, int depth_) const;

protected:
	vec3 random_in_unit_sphere() const;
};

