#ifndef _PHONG_MATERIAL_H_
#define _PHONG_MATERIAL_H_

#include <algorithm>
#include "Material.h"
class PhongMaterial : public Material{
public:
	PhongMaterial(const Color& diffuse, const Color& specular, double shininess, double reflectiveness)
		:Material(shininess, reflectiveness),
		diffuse_(diffuse),
		specular_(specular)
	{ }

	Color Sample(const Ray3& ray, const LightSample& lightSample, const Vector3& position, const Vector3& normal) override {
		Vector3 lightDir = lightSample.L();

		double NdotL = normal.Dot(lightDir);
		Vector3 H = (lightDir - ray.getDirection()).Normalize();
		double NdotH = normal.Dot(H);

		Color diffuseTerm = diffuse_ * std::max(NdotL, 0.0);
		Color specularTerm = specular_ * std::pow(std::max(NdotH, 0.0), shininess_);
		Color res = diffuseTerm + specularTerm;
		return lightSample.EL().modulate(res);
	}

private:
	const Color& diffuse_, specular_;
};

#endif // !_PHONG_MATERIAL_H_

