#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include "Color.h"
#include "Light.h"
#include "MyConst.h"
#include "Vector3.h"
class SpotLight : public Light{
public:
	SpotLight(const Color& intensity, const Vector3& position, const Vector3& direction, double theta, double phi, double falloff, double isShadow)
		:intensity_(intensity),
		position_(position),
		direction_(direction.Normalize()),
		theta_(theta),
		phi_(phi),
		falloff_(falloff),
		isShadow_(isShadow)
	{
		S_ = direction_.Negative();
		cosTheta_ = std::cos(theta_ * 0.5 * MyConst::PI / 180);
		cosPhi_ = std::cos(phi_* 0.5 * MyConst::PI / 180);
		baseMultiplier_ = 1 / (cosTheta_ - cosPhi_);
	}

	LightSample Sample(const shared_ptr<Geometry>& scene, const Vector3& position) const override;
	
private:
	Color intensity_;
	Vector3 direction_, position_, S_;
	double theta_, phi_, falloff_, cosTheta_, cosPhi_, baseMultiplier_;
	bool isShadow_;
};

LightSample SpotLight::Sample(const shared_ptr<Geometry>& scene, const Vector3& position) const {
	Vector3 delta = this->position_ - position;
	double rr = delta.SqrLength();
	double r = delta.Length();
	Vector3 L = delta / r;

	double spot; //计算聚光灯因子
	double SdotL = S_.Dot(L);
	if (SdotL >= cosTheta_)
		spot = 1;
	else if (SdotL <= cosPhi_)
		spot = 0;
	else
		spot = std::pow((SdotL - cosPhi_) * baseMultiplier_, falloff_);
	//Shadow Test
	if (isShadow_) {
		Ray3 shadowRay(position, L);
		IntersectResult shadowResult = scene->Intersect(shadowRay);
		if (shadowResult.getGeometry() && shadowResult.getDistance() <= r) {
			return LightSample::Zero;
		}
	}

	double attenuation = 1 / rr;

	return LightSample(L, intensity_ * attenuation * spot);
}

#endif // !_SPOTLIGHT_H_
