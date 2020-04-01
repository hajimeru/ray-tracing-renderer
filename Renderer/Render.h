#ifndef _RENDER_H_
#define _RENDER_H_

#include <algorithm>
#include <ctime>
#include <random>
#include <array>

#include "Color.h"
#include "Geometry.h"

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using std::shared_ptr;

class Render
{
public:
	static uint8** rayTrace(const shared_ptr<Geometry>& scene,  const PerspectiveCamera& camera, int maxReflect, const uint32 WIDTH, const uint32 HEIGHT);
public:
	static Color RayTraceRecursive(const shared_ptr<Geometry>& scene ,const Ray3 &ray, int maxReflect);
};

inline Color Render::RayTraceRecursive(const shared_ptr<Geometry>& scene, const Ray3 & ray, int maxReflect)
{
	if (maxReflect <= 0) return  Color::BLACK;

	IntersectResult result = scene->Intersect(ray);

	if (!result.getGeometry()) return Color::BLACK;

	double reflectiveness = result.getGeometry()->getMaterial()->getReflectiveness();
	Color color = result.getGeometry()->getMaterial()->Sample(ray, result.getPosition(), result.getNormal());
	color *= (1 - reflectiveness);
	if (reflectiveness > 0) {
		Vector3 r = result.getNormal() * (-2 * ray.getDirection().Dot(result.getNormal())) + ray.getDirection();
		Color reflectColor = RayTraceRecursive(scene, Ray3(result.getPosition(), r), maxReflect - 1);
		color += reflectColor * reflectiveness;
	}
	return color;
}


inline uint8** Render::rayTrace(const shared_ptr<Geometry>& scene, const PerspectiveCamera & camera, int maxReflect, const uint32 WIDTH, const uint32 HEIGHT)
{
	return NULL;
}
#endif // _RENDER_H_
