#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "Geometry.h"


class Sphere : public Geometry{
public:
	Sphere(const Vector3 center, double radius) :
		center_(center),
		radius_(radius),
		sqrRadius_(radius*radius)
	{ }
	IntersectResult Intersect(const Ray3& ray) {
		/* 
		*�� v = ray.origin - Sphere.center, d = ray.direction
		* r = || v + t * d ||
		* t = - d <dot> v - sqrt(  (d <dot> v)^2 - (v^2 - r^2 )  )
		*		�� - d <dot> v + sqrt(  (d <dot> v)^2 - (v^2 - r^2 )  ) 
		*	(t > 0)
		*/
		Vector3 v = ray.getOrigin() - center_;
		double v2_r2 = v.SqrLength() - sqrRadius_;
		double b = ray.getDirection().Dot(v);
		double delta = b * b - v2_r2; 

		if(delta < 0) return IntersectResult::noHit;
		
		double eps = 1e-6;
		double distance = 0;
		double sqrDelta = sqrt(delta);
		if (-b - sqrDelta > eps)  distance = -b - sqrDelta;
		else if (-b + sqrDelta > eps) distance = -b + sqrDelta;
		else return IntersectResult::noHit;

		Vector3 position = ray.getPoint(distance);
		Vector3 normal = (position - center_).Normalize();
		return 
	}
	
private:
	Vector3 center_;
	double radius_,sqrRadius_;
};
#endif // !_SPHERE_H_
