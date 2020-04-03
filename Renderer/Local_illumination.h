#ifndef _LOCAL_ILLUMINATION_H_
#define	_LOCAL_ILLUMINATION_H_

#include <iostream>
#include <string>

#include "CheckerMaterial.h"
#include "DirectionalLight.h"
#include "PerspectiveCamera.h"
#include "PhongMaterial.h"
#include "Plane.h"
#include "Ray3.h"
#include "Render.h"
#include "PointLight.h"
#include "Sphere.h"
#include "SpotLight.h"
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


void MaterialAndLightTest() {
	const char* IMAGE_URL = "MaterialAndLightTest.tga";
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
	plane1->setMaterial(make_shared<PhongMaterial>(Color(1, 1, 1), Color::WHITE, 10, 0.25));

	shared_ptr<Geometry> scene = make_shared<UnionGeometry>(vector<shared_ptr<Geometry>>({ plane1, sphere1, sphere2 }));

	//light1
	auto light1 = make_shared<SpotLight>(Color(1, 1, 1) * 5, Vector3(1, 3, 3), Vector3(0, -1, -1), 10, 60, 2, true);
	auto light2 = make_shared<SpotLight>(Color(1, 1, 1) * 5, Vector3(0, 3, 3), Vector3(0, -1, -1), 10, 60, 2, true);
	auto light3 = make_shared<SpotLight>(Color(1, 1, 1) * 5, Vector3(-1, 3, 3), Vector3(0, -1, -1), 10, 60, 2, true);


	vector<shared_ptr<Light>> lights{ light1,light2,light3 };
	Render::RayTrace(scene, lights, camera, 10, WIDTH, HEIGHT, image);

	image.flip_vertically();
	image.write_tga_file(IMAGE_URL);
}

void MoreAndMoreLight() {
	const char* IMAGE_URL = "MoreAndMoreLight.tga";
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
	plane1->setMaterial(make_shared<PhongMaterial>(Color(1, 1, 1), Color::WHITE, 10, 0.25));

	shared_ptr<Geometry> scene = make_shared<UnionGeometry>(vector<shared_ptr<Geometry>>({ plane1, sphere1, sphere2 }));

	//light1
	auto light1 = make_shared<SpotLight>(Color(1, 1, 1) * 5, Vector3(1, 3, 3), Vector3(0, -1, -1), 10, 60, 2, true);
	auto light2 = make_shared<SpotLight>(Color(1, 1, 1) * 5, Vector3(0, 3, 3), Vector3(0, -1, -1), 10, 60, 2, true);
	auto light3 = make_shared<SpotLight>(Color(1, 1, 1) * 5, Vector3(-1, 3, 3), Vector3(0, -1, -1), 10, 60, 2, true);


	vector<shared_ptr<Light>> lights{ light1,light2,light3 };
	Render::RayTrace(scene, lights, camera, 10, WIDTH, HEIGHT, image);

	image.flip_vertically();
	image.write_tga_file(IMAGE_URL);
}


#endif // _LOCAL_ILLUMINATION_H_

