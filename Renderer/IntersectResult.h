#ifndef _INTERSECT_RESULT_H_
#define _INTERSECT_RESULT_H_

#include <limits>
#include "Vector3.h"

class Geometry;

class IntersectResult {
public:
	IntersectResult()
		: geometry_(nullptr),
		distance_(std::numeric_limits<double>::max()),
		position_(Vector3::Zero),
		normal_(Vector3::Zero)
	{ }

	IntersectResult(const Geometry* geometry, double distance, const Vector3& position, const Vector3& normal)
		: geometry_(geometry),
		distance_(distance),
		position_(position),
		normal_(normal)
	{ }

	static const IntersectResult noHit;
	
	const Geometry* getGeometry() const { return geometry_; }

	void setGeometry(const Geometry* geometry) { geometry_ = geometry; }

	double getDistance() const { return distance_; }

	void setDistance(double distance) { distance_ = distance; }

	const Vector3& getPosition() const { return position_; }

	void setPosition(const Vector3& position) { position_ = position; }

	const Vector3& getNormal() const { return normal_; }

	void setNormal(const Vector3& normal) { normal_ = normal; }

	friend std::ostream& operator<< (std::ostream& os, const IntersectResult& intersect);

private:
	const Geometry* geometry_;
	double distance_;
	Vector3 position_;
	Vector3 normal_;
};

const IntersectResult IntersectResult::noHit = IntersectResult();

std::ostream & operator<<(std::ostream & os, const IntersectResult & intersect)
{
	os << "[IntersectResult]" << "\n"
		<< "[geometry] " << intersect.geometry_ << "\n"
		<< "[distance] " << intersect.distance_ << "\n"
		<< "[position] " << intersect.position_ << "\n"
		<< "[normal] " << intersect.normal_ << "\n"
		<< "\n";

	return os;
}
#endif // !_INTERSECT_RESULT_H_

