#include "pch.h"
#include "Raytrace.h"

using namespace Autodesk::Revit::UI;

void Raytrace::render(std::vector<rgb>& imagj, Camera* cam, Scene* world, Shader* shader,
	int n_cols, int n_rows, int height_top, int height_bottom, int n_samples, int ray_depth, float t_min,
	float t_max
)
{
	// NOTICE: We loop rows from bottom to top.
	for (auto row = height_bottom; row <= height_top; row++) // Y
	{
		for (auto col= 0 ; col < n_cols; col++) // X
		{
			rgb hue(0, 0, 0);
			//antialiasing
			for (int s = 0; s < n_samples; ++s)
			{
				// Determine how much we have 'walked' on the image: in [0,1]
				auto u = float(col + ((double)rand() / RAND_MAX)) / float(n_cols); // walked u% of the horizontal dimension of the view plane.
				auto v = float(row + ((double)rand() / RAND_MAX)) / float(n_rows); // walked v% of the vertical dimension of the view plane.

				Ray r = cam->get_ray(u, v);

				hue += shader->color(r, t_min, t_max, ray_depth);
			}

			hue /= float(n_samples);

			if (hue[rgb::X] > 1.f) {
				hue[rgb::X] = 1.f;
			}
			if (hue[rgb::Y] > 1.f) {
				hue[rgb::Y] = 1.f;
			}
			if (hue[rgb::Z] > 1.f) {
				hue[rgb::Z] = 1.f;
			}

			hue = vec3(sqrt(hue[rgb::R]), sqrt(hue[rgb::G]), sqrt(hue[rgb::B]));
			int ir = int(255.99f * hue[rgb::R]);
			int ig = int(255.99f * hue[rgb::G]);
			int ib = int(255.99f * hue[rgb::B]);


			if (ig < 0 || ir < 0) {
				ir = 0;
				ig = 0;
				ib = 0;
			}

			int position = col +  (n_rows - row -1) * n_cols;
			imagj[position] = rgb(ir, ig, ib);
			//progressbar.increase();      
		}
	}
}

