#ifndef _DIRECTIONAL_LIGNT_H_
#define _DIRECTIONAL_LIGNT_H_

#include "Light.h"
#include "Ray3.h"
#include "Vector3.h"

class DirectionalLight : public Light{
public:
	DirectionalLight(const Color& irradiance, const Vector3& direction, bool isShadow)
		:irradiance_(irradiance),
		direction_(direction.Normalize()),
		isShadow_(isShadow)
	{ 
		l_ = direction_.Negative();
	}

	virtual LightSample Sample(const shared_ptr<Geometry>& scene, const Vector3 & position) const override;

private:
	Color irradiance_;
	Vector3 direction_, l_;
	bool isShadow_;
};

LightSample DirectionalLight::Sample(const shared_ptr<Geometry>& scene, const Vector3 & position) const 
{
	if (isShadow_) {
		IntersectResult shadowResult = scene->Intersect(Ray3(position, l_));
		if (shadowResult.getGeometry()) {
			return LightSample::Zero;
		}
	}
	return LightSample(l_, irradiance_);
}

#endif // !_DIRECTIONAL_LIGNT_H_

