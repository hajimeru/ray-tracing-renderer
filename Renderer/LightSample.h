#ifndef _LIGHT_SAMPLE_H_
#define _LIGHT_SAMPLE_H_

#include "Color.h"
#include "Vector3.h"

class LightSample {
public:
	LightSample() :l_(Vector3::Zero), el_(Color::BLACK) { }
	LightSample(const Vector3& L, const Color& EL): l_(L), el_(EL) { }

	static const LightSample Zero;

	const Vector3& L() const{ return l_; }
	const Color& EL() const { return el_; }

	friend bool operator!=(const LightSample& lhs, const LightSample& rhs) {
		return !((lhs.l_ == rhs.l_) && (lhs.el_ == rhs.el_));
	}
private:
	Vector3 l_;
	Color el_;
};

const LightSample LightSample::Zero = LightSample();
#endif // !_LIGHT_SAMPLE_H_

