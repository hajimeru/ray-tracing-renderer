#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "IntersectResult.h"
#include "Material.h"
#include "Ray3.h"


class Geometry {
public:
	Geometry() {}
	Geometry(const std::shared_ptr<Material>& material) : material_(material) {}
	virtual IntersectResult Intersect(const Ray3& ray)  const = 0;

	const std::shared_ptr<Material>& getMaterial() const { return material_; }

	void setMaterial(const std::shared_ptr<Material>& material) { material_ = material; }

	virtual ~Geometry() {}
private:
	std::shared_ptr<Material> material_;
};
#endif // !_GEOMETRY_H_

