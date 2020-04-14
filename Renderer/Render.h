#ifndef _RENDER_H_
#define _RENDER_H_

#include <algorithm>
#include <ctime>
#include <random>
#include <array>

#include "Color.h"
#include "Geometry.h"
#include "Light.h"
#include "tgaimage.h"


using std::shared_ptr;
using std::vector;

class Render
{
public:
	static void RayTrace(const shared_ptr<Geometry>& scene, const vector<shared_ptr<Light>>& lights, const PerspectiveCamera& camera, int maxReflect, const int WIDTH, const int HEIGHT, TGAImage& image);
private:
	static Color RayTraceRecursive(const shared_ptr<Geometry>& scene, const vector<shared_ptr<Light>>& lights, const Ray3 &ray, int maxReflect);
};

Color Render::RayTraceRecursive(const shared_ptr<Geometry>& scene, const vector<shared_ptr<Light>>& lights, const Ray3 & ray, int maxReflect)
{
	if (maxReflect <= 0) return  Color::BLACK;

	IntersectResult result = scene->Intersect(ray);

	if (!result.getGeometry()) return Color::BLACK;

	auto material = result.getGeometry()->getMaterial();
	double reflectiveness = result.getGeometry()->getMaterial()->getReflectiveness();

	Color color;
	for (auto light : lights) {
		LightSample lightSample = light->Sample(scene, result.getPosition());
		color += material->Sample(ray, lightSample, result.getPosition(), result.getNormal());
	}

	color *= (1 - reflectiveness);

	if (reflectiveness > 0) {
		Vector3 r = result.getNormal() * (-2 * ray.getDirection().Dot(result.getNormal())) + ray.getDirection();
		Color reflectColor = RayTraceRecursive(scene, lights, Ray3(result.getPosition(), r), maxReflect - 1);
		color += reflectColor * reflectiveness;
	}
	return color;
}


void Render::RayTrace(const shared_ptr<Geometry>& scene, const vector<shared_ptr<Light>>& lights, const PerspectiveCamera & camera, int maxReflect, const int WIDTH, const int HEIGHT, TGAImage& image)
{
	#pragma omp parallel for
	for (int x = 0; x < WIDTH; ++x) {
		double sx = x / (double)WIDTH;
		for (int y = 0; y < HEIGHT; ++y) {
			double sy = y / (double)HEIGHT;
			Ray3 cmRay = camera.generateRay(sx, sy);
			//IntersectResult result = scene.Intersect(cmRay);
			TGAColor color( 255,255,255 );
			Color c = Render::RayTraceRecursive(scene,lights, cmRay, maxReflect);
			

			double r = MyMath::clip<double>(c.r, 0, 1);
			double g = MyMath::clip<double>(c.g, 0, 1);
			double b = MyMath::clip<double>(c.b, 0, 1);

			color[0] *= b;
			color[1] *= g;
			color[2] *= r;

			image.set(x, y, color);
		}
	}
}


#endif // _RENDER_H_
