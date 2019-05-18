#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream> 
#include "camera.h"
#include "scene.h"
#include "shader.h"
#pragma once
class Raytrace
{
public:
	static void render(std::stringstream& ss, Camera* cam, Scene* world, Shader* shade,
		int n_cols, int n_rows, int n_samples, int ray_depth, float t_min,
		float t_max);
};

