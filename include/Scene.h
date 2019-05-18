#include <list>
#include "ShapeObject.h"
#include "Background.h"
#pragma once
class Scene
{
public:
	std::list<ShapeObject*> list;
	Background* bg;
	rgb ambientLight;

	Scene(std::list<ShapeObject*> l_, Background* bg_, rgb al_)
	{
		list = l_;
		bg = bg_;
		ambientLight = al_;
	}
};