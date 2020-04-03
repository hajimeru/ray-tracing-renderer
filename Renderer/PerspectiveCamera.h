#ifndef _PERSPECTIVE_CAMERA_H_
#define _PERSPECTIVE_CAMERA_H_

#include "MyConst.h"
#include "Ray3.h"
#include "Vector3.h"

class PerspectiveCamera {
public:
	PerspectiveCamera(const Vector3& eye, const Vector3& front, const Vector3& up, double fov, double w_divide_h)
		:eye_(eye), front_(front.Normalize()), refUp_(up.Normalize()), fov_(fov)
	{ 
		right_ = front_.Cross(refUp_);
		up_ = right_.Cross(front_);
		fovScaleV_ = std::tan(fov * 0.5 * MyConst::PI / 180) * 2;
		fovScaleH_ = fovScaleV_ * w_divide_h;
	}

	Ray3 generateRay(double x, double y) const {
		Vector3 r = right_ * fovScaleH_ * (x - 0.5);
		Vector3 u = up_ * fovScaleV_ * (y - 0.5);

		return Ray3(eye_, front_ + r + u);
	}
	

private:
	Vector3 eye_, front_, up_, right_;
	Vector3 refUp_;
	double fov_, fovScaleH_, fovScaleV_;
};

#endif // !_PERSPECTIVE_CAMERA_H_

