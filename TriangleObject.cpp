#include "pch.h"
#include "TriangleObject.h"


std::vector<point3*> TriangleObject::getPoints() {
	std::vector<point3*> points;
	points.push_back(&v0);
	points.push_back(&v1);
	points.push_back(&v2);
	return points;
}

point3 TriangleObject::get_midpoint() const
{
	float xB = (v0.x() + v1.x() + v2.x()) / 3;
	float yB = (v0.y() + v1.y() + v2.y()) / 3;
	float zB = (v0.z() + v1.z() + v2.z()) / 3;

	return point3(xB, yB, zB);
}


/*
 * Returns true if the ray hits the Triangle  or false otherwise
 */
bool TriangleObject::hit(const Ray & r_, float  t_min_, float  t_max_, HitRecord & ht_) const
{

	vec3 e1, e2, h, s, q;
	float det, inv_det, u, v;

	e1 = (v1 - v0);
	e2 = (v2 - v0);

	h = cross(r_.get_direction(), e2);

	det = dot(e1, h);

	if (backface_cull) {
		if (det < error)
			return false;

		s = r_.get_origin() - v0;

		u = dot(s, h);

		if (u < 0.0 || u > det)
			return false;

		q = cross(s, e1);

		v = dot(r_.get_direction(), q);

		if (v < 0.0 || u + v > det)
			return false;

		inv_det = 1.0f / det;

		float t = inv_det * dot(e2, q);

		t *= inv_det;
		u *= inv_det;
		v *= inv_det;

		if (t > error && t <= t_max_) // ray intersection
		{
			ht_.t = t;
			ht_.p = r_.point_at(t);
			ht_.normal = unit_vector(cross(e1, e2));
			ht_.mat = ShapeObject::material;
			float phi = atan2(ht_.normal.z(), ht_.normal.x());
			float theta = asin(ht_.normal.y());
			float maxX = std::max(v0.x(), std::max(v1.x(), v2.x()));
			float minX = std::min(v0.x(), std::min(v1.x(), v2.x()));
			float maxY = std::max(v0.y(), std::max(v1.y(), v2.y()));
			float minY = std::min(v0.y(), std::min(v1.y(), v2.y()));
			ht_.u =  (float)(1 - (phi + M_PI) / (2 * M_PI)); 
			ht_.v = (float)((theta + M_PI / 2) / M_PI); 
			return true;
		}
		else // This means that there is a line intersection but not a ray intersection.
			return false;
	}
	else {

		if (det > -error && det < error)
			return false;

		inv_det = 1.0f / det;

		s = r_.get_origin() - v0;

		u = inv_det * dot(s, h);

		if (u < 0.0 || u > 1.0)
			return false;

		q = cross(s, e1);

		v = inv_det * dot(r_.get_direction(), q);

		if (v < 0.0 || u + v > 1.0)
			return false;

		float t = inv_det * dot(e2, q);

		if (t > error && t <= t_max_) // ray intersection
		{
			ht_.t = t;
			ht_.p = r_.point_at(t);
			ht_.normal = unit_vector(cross(e1, e2));
			ht_.mat = ShapeObject::material;
			
			float minX = std::min(v0.x(), std::min(v1.x(), v2.x()));
			float minY = std::min(v0.y(), std::min(v1.y(), v2.y()));
			float minZ = std::min(v0.z(), std::min(v1.z(), v2.z()));

			float maxX = std::max(v0.x(), std::max(v1.x(), v2.x()));
			float maxY = std::max(v0.y(), std::max(v1.y(), v2.y()));
			float maxZ = std::max(v0.z(), std::max(v1.z(), v2.z()));
			if (maxZ == minZ) {
				ht_.u = ((ht_.p.x() - minX) ) / ((maxX - minX) );
				ht_.v = (ht_.p.y() - minY) / (maxY - minY);
			}
			else
			{
				ht_.u = ((ht_.p.x() - minX) + (ht_.p.y() - minY)) / ((maxX - minX) + (maxY - minY));
				ht_.v = (ht_.p.z() - minZ) / (maxZ - minZ);
			}
			
			return true;
		}
		else // This means that there is a line intersection but not a ray intersection.
			return false;
	}
}