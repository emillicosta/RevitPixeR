#include "pch.h"
#include "CubeObject.h"


CubeObject::CubeObject()
{
}

CubeObject::CubeObject(MyMaterial* m_, point3 min_, point3 max_)
{
	ShapeObject::origin = point3(0, 0, 0);
	ShapeObject::material = m_;
	float x = max_.x(), y = max_.y(), z = max_.z();
	if (min_.x() == max_.x())
		x += 0.1;
	if (min_.y() == max_.y())
		y += 0.1;
	if (min_.z() == max_.z())
		z += 0.1;
	mini = min_;
	maxi = point3(x, y, z);
}

CubeObject* CubeObject::wrap(CubeObject* node, CubeObject* bbox_tri)const {

	point3 mini_ = min_vector(node->mini, bbox_tri->mini);
	vec3 maxi_1 = max_vector(node->maxi, bbox_tri->maxi);
	CubeObject* aux = new CubeObject(ShapeObject::material, mini_, maxi_1);
	return aux;
}

/*
 * Returns true if the ray hits the Cube  or false otherwise
 */
bool CubeObject::hit(const Ray& r_, float  t_min_, float  t_max_, HitRecord& ht_) const
{
	float tymin = (mini.y() - r_.get_origin().y()) / r_.get_direction().y();
	float tymax = (maxi.y() - r_.get_origin().y()) / r_.get_direction().y();

	double tmin = -INFINITY, tmax = INFINITY;

	for (int i = 0; i < 3; ++i) {
		double t1 = (mini[i] - r_.get_origin()[i]) / r_.get_direction()[i];
		double t2 = (maxi[i] - r_.get_origin()[i]) / r_.get_direction()[i];

		tmin = max(tmin, min(t1, t2));
		tmax = min(tmax, max(t1, t2));
	}

	if (tmax > max(tmin, 0.0)) {
		float t = tmin;
		ht_.t = tmin;
		ht_.p = r_.point_at(t);

		point3 c = (mini + maxi) * 0.5;
		vec3 p = ht_.p - c;
		point3 d = (mini - maxi) * 0.5;
		float bias = 1.000001;

		vec3 normal = vec3(
			p.x() / abs(d.x()) * bias,
			p.y() / abs(d.y()) * bias,
			p.z() / abs(d.z()) * bias
		);

		ht_.normal = unit_vector(normal);
		ht_.mat = ShapeObject::material;
		return true;
	}


	return false;

}


