#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "Light.h"
#include "LightSample.h"

class PointLight : public Light{
public:
	PointLight(const Color& intensity, const Vector3& position, bool isShadow)
		:intensity_(intensity),
		position_(position),
		isShadow_(isShadow)
	{ }

	virtual LightSample Sample(const shared_ptr<Geometry>& scene, const Vector3& position) const override;
private:
	Color intensity_;
	Vector3 position_;
	bool isShadow_;
};


LightSample PointLight::Sample(const shared_ptr<Geometry>& scene, const Vector3& position) const 
{
	Vector3 delta = this->position_ - position;
	double rr = delta.SqrLength();
	double r = delta.Length();
	Vector3 L = delta / r;

	if (isShadow_) {
		Ray3 shadowRay(position, L);
		IntersectResult shadowResult = scene->Intersect(shadowRay);
		if (shadowResult.getGeometry() && shadowResult.getDistance() <= r) {
			return LightSample::Zero;
		}
	}
	double attenuation = 1 / rr;
	return LightSample(L, intensity_ * attenuation);
}
#endif // !_POINT_LIGHT_H_

