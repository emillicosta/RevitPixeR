#include "pch.h"
#include "SphereObject.h"


SphereObject::~SphereObject()
{
}

bool SphereObject::hit(const Ray& r_, float  t_min_, float  t_max_, HitRecord& ht_) const
{
	// First, manipulate the 1), 2) and 3) line to create the 4) equation   
   // 1) (point - center) * (point - center) - radius² = 0     
   // 2) point == ray  // 3) ray(t) = origin + direction*t     
   // 4) d*d*t² + 2(origin - center)*d*t + (origin - center)*(origin - center) - radius² = 0   

   // Second, calculate the a, b and c from the equation 4) (a*t² + b*t + c = 0)   
	auto oc = r_.get_origin() - ShapeObject::origin; // (origin - center)    

	auto a = dot(r_.get_direction(), r_.get_direction()); // d*d  
	auto b = 2 * dot(oc, r_.get_direction());             // 2(origin-center)*d
	auto c = dot(oc, oc) - (radius * radius);               // (origin-center)*(origin-center) - radius²

	// Third, calculate the delta (b² - 4ac)    
	auto delta = b * b - 4 * a * c;


	// Last, return the t component if the ray hit the sphere 
	if (delta >= 0) {
		auto t = (-b - sqrt(delta)) / (2 * a);


		if (t <= t_max_ && t >= t_min_) {
			ht_.t = t;
			ht_.p = r_.point_at(t);
			ht_.normal = (ht_.p - ShapeObject::origin) / radius;
			ht_.mat = ShapeObject::material;
			double phi = atan2(ht_.normal.y(), ht_.normal.x());
			double theta = asin(ht_.normal.z());
			ht_.u = 1 - (phi + M_PI) / (2 * M_PI);
			ht_.v = (theta + M_PI / 2) / M_PI;
			return true;
		} 

		t = (-b + sqrt(delta)) / (2.0 * a);
		if (t >= t_min_ && t <= t_max_) {
			ht_.t = t;
			ht_.p = r_.point_at(t);
			ht_.normal = (ht_.p - ShapeObject::origin) / radius;
			double phi = atan2(ht_.normal.y(), ht_.normal.x());
			double theta = asin(ht_.normal.z());
			ht_.u = 1 - (phi + M_PI) / (2 * M_PI);
			ht_.v = (theta + M_PI / 2) / M_PI;
			ht_.mat = ShapeObject::material;
			return true;
		}
	}

	return false;
}