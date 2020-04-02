#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Color.h"
#include "LightSample.h"
#include "Ray3.h"
class Material {
public:
	Material():shininess_(0), reflectiveness_(0){ }
	Material(double shininess, double reflectiveness) 
		:shininess_(shininess), 
		reflectiveness_(reflectiveness)
	{ }
	virtual ~Material() { }

	virtual Color Sample(const Ray3& ray, const LightSample& lightSample, const Vector3& position, const Vector3& normal) = 0;

	double getShininess() const { return shininess_; }

	double getReflectiveness() const { return reflectiveness_; }

protected:
	double shininess_;
	double reflectiveness_;
};
#endif // !_MATERIAL_H_

