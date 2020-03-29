#ifndef _RAY3_H_
#define _RAY3_H_

#include "Vector3.h"

class Ray3{
public:
	Ray3(const Vector3& origin, const Vector3 direction) 
		:origin_(origin),
		direction_(direction)
	{ }
	
	Vector3 getDirection() const { return direction_; }

	Vector3 getOrigin() const { return origin_; }

	Vector3 getPoint(double t) const { return origin_ + t * direction_; }

private:
	Vector3 origin_;
	Vector3 direction_;
};

#endif // !_RAY3_H_

