#include <list>
#include "ShapeObject.h"
#include "Background.h"
#include "Light.h"
#pragma once
class Scene
{
public:
	std::list<ShapeObject*> list;
	Background* bg;
	rgb ambientLight;
	std::list<Light*> lights;

	Scene(std::list<ShapeObject*> l_, std::list<Light*> lum, Background* bg_, rgb al_)
	{
		list = l_;
		bg = bg_;
		ambientLight = al_;
		lights = lum;
	}
};

