#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Geometry.h"
#include "PhongMaterial.h"

class Sphere : public Geometry{
public:
	Sphere(const Vector3 center, double radius, const std::shared_ptr<Material>& material = nullptr)
		:Geometry(material),
		center_(center),
		radius_(radius),
		sqrRadius_(radius*radius)
	{ }

	// 通过 Geometry 继承
	virtual IntersectResult Intersect(const Ray3 & ray) const override;

private:
	Vector3 center_;
	double radius_,sqrRadius_;
};


IntersectResult Sphere::Intersect(const Ray3& ray) const {
	/*
	*设 v = ray.origin - Sphere.center, d = ray.direction
	* r = || v + t * d ||
	* t = - d <dot> v - sqrt(  (d <dot> v)^2 - (v^2 - r^2 )  )
	*		或 - d <dot> v + sqrt(  (d <dot> v)^2 - (v^2 - r^2 )  )
	*	(t > 0)
	*/
	Vector3 v = ray.getOrigin() - center_;
	double v2_r2 = v.SqrLength() - sqrRadius_;
	double b = ray.getDirection().Dot(v);
	double delta = b * b - v2_r2;

	if (delta < 0) return IntersectResult::noHit;

	double eps = 1e-6;
	double distance = 0;
	double sqrtDelta = sqrt(delta);
	if (-b - sqrtDelta > eps)  distance = -b - sqrtDelta;
	else if (-b + sqrtDelta > eps) distance = -b + sqrtDelta;
	else return IntersectResult::noHit;//(t>0)

	Vector3 position = ray.getPoint(distance);
	Vector3 normal = (position - center_).Normalize();
	return IntersectResult(this, distance, position, normal);
}

#endif // !_SPHERE_H_

