#include "pch.h"
#include "Camera.h"


Camera::Camera(point3 e_, point3 d_, vec3 vup_, float fov_, float aspect_, float aperture_, float focus_dist_)
{
	origin = e_;

	w = unit_vector(- d_);
	u = unit_vector(cross(vup_, w));
	v = cross(w, u);


	lens_radius = aperture_ / 2;

	float theta = fov_ * (float)M_PI / 180.f; // Radian transformation

	float half_height = tan(theta / 2) * 2 * focus_dist_;
	float half_width = aspect_ * half_height;

	horizontal = half_width * u;
	vertical = half_height * v;
	lower_left_corner = origin - (focus_dist_ * w) - (horizontal / 2) - (vertical / 2); //e_ - half_width * focus_dist_ * u - half_height * focus_dist_ * v - w * focus_dist_;
	
}


vec3 Camera::random_in_unit_sphere() const
{
	vec3 p;
	do {
		p = 2.0 * vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}

/*
 * Get the ray that hits the view plane on the coordinate (u,v)
 */
Ray Camera::get_ray(float u_, float v_) const
{
	vec3 rd = lens_radius * random_in_unit_sphere();
	vec3 offset = u * rd.x() + v * rd.y();

	point3 end_point = lower_left_corner + u_ * horizontal + v_ * vertical;
	Ray r(origin + offset, end_point - origin - offset);
	return r;
}
