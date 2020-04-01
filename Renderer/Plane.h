#ifndef _PLANE_H_
#define _PLANE_H_

#include "Geometry.h"

class Plane : public Geometry{
public:
	Plane(const Vector3& normal, double distance,const std::shared_ptr<Material>& material = nullptr)
		: Geometry(material),
		normal_(normal.Normalize()),
		position_(distance * normal.Normalize())
	{ }

	
private:
	Vector3 normal_, position_;
	// Í¨¹ý Geometry ¼Ì³Ð
	virtual IntersectResult Intersect(const Ray3 & ray) const override;
};


IntersectResult Plane::Intersect(const Ray3 & ray) const
{
	double a = ray.getDirection().Dot(normal_);
	if (a >= 0) {
		return IntersectResult::noHit;
	}
	double b = normal_.Dot(ray.getOrigin() - position_);
	double distance = -b / a;

	return IntersectResult(this, distance, ray.getPoint(distance), normal_);
}

#endif
