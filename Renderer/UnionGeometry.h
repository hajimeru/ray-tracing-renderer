#ifndef _UNION_GEOMETRY_H_
#define _UNION_GEOMETRY_H_

#include <limits>
#include <vector>
#include "Geometry.h"

class UnionGeometry : public Geometry{
public:
	UnionGeometry(const std::vector<std::shared_ptr<Geometry>>& geometries)
		: geometries_(geometries)
	{ }

	virtual IntersectResult Intersect(const Ray3& ray)  const  override;

	void Add(const std::shared_ptr<Geometry>& geometry) { geometries_.push_back(geometry); }

	std::vector<std::shared_ptr<Geometry>> getAll() const { return geometries_; }
private:
	std::vector<std::shared_ptr<Geometry>> geometries_;
};

IntersectResult UnionGeometry::Intersect(const Ray3 & ray) const
{
	double minDistance = std::numeric_limits<double>::max();
 	IntersectResult minResult = IntersectResult::noHit;
 	for (auto& geometry : geometries_) {
 		IntersectResult&& result = geometry->Intersect(ray);
 		if (result.getGeometry() && result.getDistance() < minDistance) {
 			minDistance = result.getDistance();
 			minResult = result;
 		}
 	}
 	return minResult;
}
#endif // !_UNION_GEOMETRY_H_

