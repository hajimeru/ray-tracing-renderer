#ifndef _LOCAL_ILLUMINATION_H_
#define	_LOCAL_ILLUMINATION_H_

#include <iostream>
#include <string>

#include "CheckerMaterial.h"
#include "PerspectiveCamera.h"
#include "PhongMaterial.h"
#include "Plane.h"
#include "Ray3.h"
#include "Render.h"
#include "Sphere.h"
#include "tgaimage.h"
#include "UnionGeometry.h"
#include "Vector3.h"

using namespace std;


const int WIDTH = 800;
const int HEIGHT = 600;

const double W_DIVIDE_H = WIDTH / (double)HEIGHT;

void RenderDepthTest();
void RenderNormalTest();
void RayTraceTest();
void RayTraceReflection();


void RenderDepthTest() {
	const char* IMAGE_URL = "RenderDepthTest.tga";
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	//Camera
	Vector3 eye(0, 0, -1);
	Vector3 front(0, 0, 1);
	Vector3 up(0, 1, 0);
	PerspectiveCamera camera(eye, front, up, 90, W_DIVIDE_H);

	//Sphere
	Vector3 sphPos = Vector3(0, 0, 1);
	Sphere sphere(sphPos, 1);

	double Maxdepth = 5.0;

	for (int x = 0; x < WIDTH; ++x) {
		double sx = x / (double)WIDTH;
		for (int y = 0; y < HEIGHT; ++y) {
			double sy = y / (double)HEIGHT;
			Ray3 cmRay = camera.generateRay(sx, sy);
			IntersectResult result = sphere.Intersect(cmRay);
			double depth = result.getDistance() / Maxdepth;
			//std::cout << result << std::endl;
			image.set(x, y, TGAColor(255, 255, 255)* depth);
		}
	}


	image.flip_vertically();
	image.write_tga_file(IMAGE_URL);
}


void RenderNormalTest() {
	const char* IMAGE_URL = "RenderNormalTest.tga";
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	//Camera
	Vector3 eye(0, 0, -1);
	Vector3 front(0, 0, 1);
	Vector3 up(0, 1, 0);
	PerspectiveCamera camera(eye, front, up, 90, W_DIVIDE_H);

	//Sphere
	Vector3 sphPos = Vector3(0, 0, 1);
	Sphere sphere(sphPos, 1);

	double Maxdepth = 5.0;

	for (int x = 0; x < WIDTH; ++x) {
		double sx = x / (double)WIDTH;
		for (int y = 0; y < HEIGHT; ++y) {
			double sy = y / (double)HEIGHT;
			Ray3 cmRay = camera.generateRay(sx, sy);
			IntersectResult result = sphere.Intersect(cmRay);
			Vector3 normal = result.getNormal();
			normal += Vector3(1, 1, 1);
			normal *= 0.5;
			image.set(x, y, TGAColor(255 * normal.x(), 255 * normal.y(), 255 * normal.z()));
		}
	}

	image.flip_vertically();
	image.write_tga_file(IMAGE_URL);
}


void RayTraceTest() {
	const char* IMAGE_URL = "RayTraceTest.tga";
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	//Camera
	Vector3 eye(0, 0, 2);
	Vector3 front(0, 0, -1);
	Vector3 up(0, 1, 0);
	PerspectiveCamera camera(eye, front, up, 90, W_DIVIDE_H);

	//Sphere
	std::shared_ptr<PhongMaterial> material = std::make_shared<PhongMaterial>(Color(1, 0, 0), Color::WHITE, 32, 1);
	Vector3 sphPos = Vector3(0, 0, 0);
	Sphere sphere(sphPos, 1, material);

	double Maxdepth = 5.0;

	for (int x = 0; x < WIDTH; ++x) {
		double sx = x / (double)WIDTH;
		for (int y = 0; y < HEIGHT; ++y) {
			double sy = y / (double)HEIGHT;
			Ray3 cmRay = camera.generateRay(sx, sy);
			IntersectResult result = sphere.Intersect(cmRay);
			TGAColor color(255, 255, 255);
			if (result.getGeometry()) {
				Color c = result.getGeometry()->getMaterial()->Sample(cmRay, result.getPosition(), result.getNormal());
				if (c.r > 1 || c.g > 1 || c.b > 1)
					std::cout << c << "\n";
				color.bgra[0] *= c.b;
				color.bgra[1] *= c.g;
				color.bgra[2] *= c.r;
			}
			image.set(x, y, color);
		}
	}

	image.flip_vertically();
	image.write_tga_file(IMAGE_URL);
}


void RayTraceReflection() {
	const char* IMAGE_URL = "RayTraceReflection.tga";
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	//Camera
	Vector3 eye(0, 0.5, 3);
	Vector3 front(0, 0, -1);
	Vector3 up(0, 1, 0);
	PerspectiveCamera camera(eye, front, up, 90, W_DIVIDE_H);


	// Two spheres
	auto sphere1 = make_shared<Sphere>(Vector3(-1, 1, 0), 1);
	auto sphere2 = make_shared<Sphere>(Vector3(1, 1, 0), 1);

	sphere1->setMaterial(make_shared<PhongMaterial>(Color(1, 0, 0), Color::WHITE, 10, 0.25));
	sphere2->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color::WHITE, 16, 0.25));

	//plane
	auto plane1 = make_shared<Plane>(Vector3(0, 1, 0), 0);
	plane1->setMaterial(make_shared<CheckerMaterial>(1,0.25));

	shared_ptr<Geometry> scene = make_shared<UnionGeometry>(vector<shared_ptr<Geometry>>({ plane1, sphere1, sphere2 }));

	double Maxdepth = 5.0;

	for (int x = 0; x < WIDTH; ++x) {
		double sx = x / (double)WIDTH;
		for (int y = 0; y < HEIGHT; ++y) {
			double sy = y / (double)HEIGHT;
			Ray3 cmRay = camera.generateRay(sx, sy);
			//IntersectResult result = scene.Intersect(cmRay);
			TGAColor color(255, 255, 255);
			Color c = Render::RayTraceRecursive(scene, cmRay, 3);
			if (c.r > 1 || c.g > 1 || c.b > 1)
					std::cout << c << "\n";
			color.bgra[0] *= c.b;
			color.bgra[1] *= c.g;
			color.bgra[2] *= c.r;
			image.set(x, y, color);
		}
	}
	image.flip_vertically();
	image.write_tga_file(IMAGE_URL);
}

#endif // _LOCAL_ILLUMINATION_H_
