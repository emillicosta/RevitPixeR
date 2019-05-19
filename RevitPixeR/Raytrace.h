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
	static void render(std::vector<rgb>& imagj, Camera* cam, Scene* world, Shader* shader,
		int n_cols, int n_rows, int height_top, int height_bottom, int n_samples, int ray_depth, float t_min,
		float t_max);
};

