#ifndef _CHECKER_MATTERIAL_H_
#define _CHECKER_MATTERIAL_H_
#include "Material.h"


class CheckerMaterial : public Material{
public:
	CheckerMaterial(double scale, double reflectiveness)
		:Material(0,reflectiveness),
		scale_(scale)
	{ }

	Color Sample(const Ray3& ray, const LightSample& lightSample, const Vector3& position, const Vector3& normal) override {
		return (std::abs((int)( std::floor(position.x() * 1) + std::floor(position.z() * scale_) ) % 2) < 1) ? Color::BLACK : Color::WHITE;
	}

private:
	double scale_;
};

#endif // !_CHECKER_MATTERIAL_H_

