#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <memory>

#include "LightSample.h"
#include "Vector3.h"
#include "Geometry.h"

using std::shared_ptr;

class Light {
public:
	virtual LightSample Sample(const shared_ptr<Geometry>& scene, const Vector3& position) const = 0;
};
#endif // !_LIGHT_H_

