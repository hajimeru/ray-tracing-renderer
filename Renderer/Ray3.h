#ifndef _RAY3_H_
#define _RAY3_H_

#include "Vector3.h"

class Ray3{
public:
	Ray3(const Vector3& origin, const Vector3& direction) 
		:origin_(origin),
		direction_(direction.Normalize())
	{ }
	
	Vector3 getDirection() const { return direction_; }

	Vector3 getOrigin() const { return origin_; }

	Vector3 getPoint(double t) const { return origin_ + t * direction_; }

	friend std::ostream& operator<<(std::ostream& os, const Ray3& ray);
private:
	Vector3 origin_;
	Vector3 direction_;
};

std::ostream& operator<<(std::ostream& os, const Ray3& ray) {
	os << "[IntersectResult]: " 
		<< "[origin] " << ray.origin_ << " "
		<< "[direction] " << ray.direction_ << " "
		<< "\n";
	return os;
}
#endif // !_RAY3_H_

