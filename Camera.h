#include "Ray.h"
# define M_PI           3.14159265358979323846
#pragma once
class Camera
{
public:
	point3 lower_left_corner; // lower left corner of the view plane.
	vec3 horizontal; // Horizontal dimension of the view plane.
	vec3 vertical; // Vertical dimension of the view plane.
	point3 origin; // the camera's origin.
	float lens_radius;
	vec3 u, v, w;

	Camera(point3 e_, point3 d_, vec3 vup_, float fov_, float aspect_, float aperture_, float focus_dist_);

	Ray get_ray(float u_, float v_) const;
	vec3 random_in_unit_sphere() const;
};
