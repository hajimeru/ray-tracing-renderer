#ifndef _LIGHT_TEST_H_
#define _LIGHT_TEST_H_


#include <iostream>
#include <string>

#include "CheckerMaterial.h"
#include "DirectionalLight.h"
#include "PerspectiveCamera.h"
#include "PhongMaterial.h"
#include "Plane.h"
#include "PointLight.h"
#include "Ray3.h"
#include "Render.h"
#include "Sphere.h"
#include "SpotLight.h"
#include "tgaimage.h"
#include "UnionGeometry.h"
#include "Vector3.h"
#include "MyMath.h"
using namespace std;


const int WIDTH = 800;
const int HEIGHT = 600;

const double W_DIVIDE_H = WIDTH / (double)HEIGHT;

void DirectionalLightTest()
{
	const char* IMAGE_URL = "DirectionalLightTest.tga";
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	//Camera
	Vector3 eye(0, 1, 3);
	Vector3 front(0, 0, -1);
	Vector3 up(0, 1, 0);
	PerspectiveCamera camera(eye, front, up, 90, W_DIVIDE_H);


	// Two spheres
	auto sphere1 = make_shared<Sphere>(Vector3(-1, 1, 0), 1);
	auto sphere2 = make_shared<Sphere>(Vector3(1, 1, 0), 1);

	sphere1->setMaterial(make_shared<PhongMaterial>(Color(1, 0, 0), Color::WHITE, 10, 0.25));
	sphere2->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color::WHITE, 16, 0.25));

	//plane
	auto plane1 = make_shared<Plane>(Vector3(-1, 0, 0), -2);
	auto plane2 = make_shared<Plane>(Vector3(0, 1, 0), 0);
	auto plane3 = make_shared<Plane>(Vector3(0, 0, 1), -1);

	plane1->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color(1, 1, 1), 32, 0.25));
	plane2->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color(1, 1, 1), 32, 0.25));
	plane3->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color(1, 1, 1), 32, 0.25));

	//plane2->setMaterial(make_shared<CheckerMaterial>(1, 0.25));

	DirectionalLight light(Color(1, 1, 1), Vector3(-1, -1, -1), true);

	shared_ptr<Geometry> scene = make_shared<UnionGeometry>(vector<shared_ptr<Geometry>>({ plane2, sphere1, sphere2 }));

	for (int x = 0; x < WIDTH; ++x) {
		double sx = x / (double)WIDTH;
		for (int y = 0; y < HEIGHT; ++y) {
			double sy = y / (double)HEIGHT;
			Ray3 cmRay = camera.generateRay(sx, sy);
			IntersectResult result = scene->Intersect(cmRay);
			if (result.getGeometry()) {
				Color c = Color::BLACK;

				LightSample lightSample = light.Sample(scene, result.getPosition());
				if (lightSample != LightSample::Zero) {
					auto NdotL = result.getNormal().Dot(lightSample.L());
					if (NdotL >= 0) {
						c += lightSample.EL() *  NdotL;
						//cout << c << "\n";
					}
				}
				double r = MyMath::clip<double>(c.r, 0, 1);
				double g = MyMath::clip<double>(c.g, 0, 1);
				double b = MyMath::clip<double>(c.b, 0, 1);

				c = Color(r, g, b);
				TGAColor color(255, 255, 255);


				color.bgra[0] *= c.b;
				color.bgra[1] *= c.g;
				color.bgra[2] *= c.r;
				image.set(x, y, color);
			}
		}
	}
	image.flip_vertically();
	image.write_tga_file(IMAGE_URL);


}

void PointLightTest()
{
	const char* IMAGE_URL = "PointLightTest.tga";
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	//Camera
	Vector3 eye(0, 1, 3);
	Vector3 front(0, 0, -1);
	Vector3 up(0, 1, 0);
	PerspectiveCamera camera(eye, front, up, 90, W_DIVIDE_H);


	// Two spheres
	auto sphere1 = make_shared<Sphere>(Vector3(-1, 1, 0), 1);
	auto sphere2 = make_shared<Sphere>(Vector3(1, 1, 0), 1);

	sphere1->setMaterial(make_shared<PhongMaterial>(Color(1, 0, 0), Color::WHITE, 10, 0.25));
	sphere2->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color::WHITE, 16, 0.25));

	//plane
	auto plane1 = make_shared<Plane>(Vector3(-1, 0, 0), -2);
	auto plane2 = make_shared<Plane>(Vector3(0, 1, 0), 0);
	auto plane3 = make_shared<Plane>(Vector3(0, 0, 1), -1);

	plane1->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color(1, 1, 1), 32, 0.25));
	plane2->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color(1, 1, 1), 32, 0.25));
	plane3->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color(1, 1, 1), 32, 0.25));

	//plane2->setMaterial(make_shared<CheckerMaterial>(1, 0.25));

	PointLight light(Color(1, 1, 1) * 10, Vector3(3, 3, 3), true);

	shared_ptr<Geometry> scene = make_shared<UnionGeometry>(vector<shared_ptr<Geometry>>({ plane2, sphere1, sphere2 }));

	for (int x = 0; x < WIDTH; ++x) {
		double sx = x / (double)WIDTH;
		for (int y = 0; y < HEIGHT; ++y) {
			double sy = y / (double)HEIGHT;
			Ray3 cmRay = camera.generateRay(sx, sy);
			IntersectResult result = scene->Intersect(cmRay);
			if (result.getGeometry()) {
				Color c = Color::BLACK;

				LightSample lightSample = light.Sample(scene, result.getPosition());
				if (lightSample != LightSample::Zero) {
					auto NdotL = result.getNormal().Dot(lightSample.L());
					if (NdotL >= 0) {
						c += lightSample.EL() *  NdotL;
						//cout << c << "\n";
					}
				}
				
				double r = MyMath::clip<double>(c.r, 0, 1);
				double g = MyMath::clip<double>(c.g, 0, 1);
				double b = MyMath::clip<double>(c.b, 0, 1);

				c = Color(r, g, b);
				TGAColor color(255, 255, 255);
				
				color.bgra[0] *= c.b;
				color.bgra[1] *= c.g;
				color.bgra[2] *= c.r;
				image.set(x, y, color);
			}
		}
	}
	image.flip_vertically();
	image.write_tga_file(IMAGE_URL);
}


void SpotLightTest()
{
	const char* IMAGE_URL = "SpotLightTest.tga";
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	//Camera
	Vector3 eye(0, 1, 3);
	Vector3 front(0, 0, -1);
	Vector3 up(0, 1, 0);
	PerspectiveCamera camera(eye, front, up, 90, W_DIVIDE_H);


	// Two spheres
	auto sphere1 = make_shared<Sphere>(Vector3(-1, 1, 0), 1);
	auto sphere2 = make_shared<Sphere>(Vector3(1, 1, 0), 1);

	sphere1->setMaterial(make_shared<PhongMaterial>(Color(1, 0, 0), Color::WHITE, 10, 0.25));
	sphere2->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color::WHITE, 16, 0.25));

	//plane
	auto plane1 = make_shared<Plane>(Vector3(-1, 0, 0), -2);
	auto plane2 = make_shared<Plane>(Vector3(0, 1, 0), 0);
	auto plane3 = make_shared<Plane>(Vector3(0, 0, 1), -1);

	plane1->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color(1, 1, 1), 32, 0.25));
	plane2->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color(1, 1, 1), 32, 0.25));
	plane3->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color(1, 1, 1), 32, 0.25));

	//plane2->setMaterial(make_shared<CheckerMaterial>(1, 0.25));

	//light1
	auto light1 = make_shared<SpotLight>(Color(1, 0, 0) * 10, Vector3(1, 3, 3), Vector3(0, -1, -1), 10, 60, 2, true);
	auto light2 = make_shared<SpotLight>(Color(0, 1, 0) * 10, Vector3(0, 3, 3), Vector3(0, -1, -1), 10, 60, 2, true);
	auto light3 = make_shared<SpotLight>(Color(0, 0, 1) * 10, Vector3(-1, 3, 3), Vector3(0, -1, -1), 10, 60, 2, true);

	shared_ptr<Geometry> scene = make_shared<UnionGeometry>(vector<shared_ptr<Geometry>>({ plane2, sphere1, sphere2 }));

	vector<shared_ptr<Light>> AllLight{ light1,light2,light3 };

	for (int x = 0; x < WIDTH; ++x) {
		double sx = x / (double)WIDTH;
		for (int y = 0; y < HEIGHT; ++y) {
			double sy = y / (double)HEIGHT;
			Ray3 cmRay = camera.generateRay(sx, sy);
			IntersectResult result = scene->Intersect(cmRay);
			if (result.getGeometry()) {
				Color c = Color::BLACK;

				for (auto light : AllLight)
				{
					LightSample lightSample = light->Sample(scene, result.getPosition());
					if (lightSample != LightSample::Zero) {
						auto NdotL = result.getNormal().Dot(lightSample.L());
						if (NdotL >= 0) {
							c += lightSample.EL() *  NdotL;
							//cout << c << "\n";
						}
					}

				}
				
				double r = MyMath::clip<double>(c.r, 0, 1);
				double g = MyMath::clip<double>(c.g, 0, 1);
				double b = MyMath::clip<double>(c.b, 0, 1);

				c = Color(r, g, b);
				TGAColor color(255, 255, 255);

				color.bgra[0] *= c.b;
				color.bgra[1] *= c.g;
				color.bgra[2] *= c.r;
				image.set(x, y, color);
			}
		}
	}
	image.flip_vertically();
	image.write_tga_file(IMAGE_URL);
}



void MoreAndMoreLightTest()
{
	const char* IMAGE_URL = "MoreAndMoreLightTest.tga";
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

	//Camera
	Vector3 eye(0, 1, 3);
	Vector3 front(0, 0, -1);
	Vector3 up(0, 1, 0);
	PerspectiveCamera camera(eye, front, up, 90, W_DIVIDE_H);


	// Two spheres
	auto sphere1 = make_shared<Sphere>(Vector3(-1, 1, 0), 1);
	auto sphere2 = make_shared<Sphere>(Vector3(1, 1, 0), 1);

	sphere1->setMaterial(make_shared<PhongMaterial>(Color(1, 0, 0), Color::WHITE, 10, 0.25));
	sphere2->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color::WHITE, 16, 0.25));

	//plane
	auto plane1 = make_shared<Plane>(Vector3(-1, 0, 0), -2);
	auto plane2 = make_shared<Plane>(Vector3(0, 1, 0), 0);
	auto plane3 = make_shared<Plane>(Vector3(0, 0, 1), -1);

	plane1->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color(1, 1, 1), 32, 0.25));
	plane2->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color(1, 1, 1), 32, 0.25));
	plane3->setMaterial(make_shared<PhongMaterial>(Color(0.5, 0.5, 0.5), Color(1, 1, 1), 32, 0.25));

	//plane2->setMaterial(make_shared<CheckerMaterial>(1, 0.25));

	//light1
	auto light1 = make_shared<SpotLight>(Color(1, 0, 0) * 10, Vector3(1, 3, 3), Vector3(0, -1, -1), 10, 60, 2, true);
	auto light2 = make_shared<SpotLight>(Color(0, 1, 0) * 10, Vector3(0, 3, 3), Vector3(0, -1, -1), 10, 60, 2, true);
	auto light3 = make_shared<SpotLight>(Color(0, 0, 1) * 10, Vector3(-1, 3, 3), Vector3(0, -1, -1), 10, 60, 2, true);

	shared_ptr<Geometry> scene = make_shared<UnionGeometry>(vector<shared_ptr<Geometry>>({ plane2, sphere1, sphere2 }));

	vector<shared_ptr<Light>> AllLight{ light1,light2,light3 };

	for (int x = 0; x < WIDTH; ++x) {
		double sx = x / (double)WIDTH;
		for (int y = 0; y < HEIGHT; ++y) {
			double sy = y / (double)HEIGHT;
			Ray3 cmRay = camera.generateRay(sx, sy);
			IntersectResult result = scene->Intersect(cmRay);
			if (result.getGeometry()) {
				Color c = Color::BLACK;

				for (auto light : AllLight)
				{
					LightSample lightSample = light->Sample(scene, result.getPosition());
					if (lightSample != LightSample::Zero) {
						auto NdotL = result.getNormal().Dot(lightSample.L());
						if (NdotL >= 0) {
							c += lightSample.EL() *  NdotL;
							//cout << c << "\n";
						}
					}

				}

				double r = MyMath::clip<double>(c.r, 0, 1);
				double g = MyMath::clip<double>(c.g, 0, 1);
				double b = MyMath::clip<double>(c.b, 0, 1);

				c = Color(r, g, b);
				TGAColor color(255, 255, 255);

				color.bgra[0] *= c.b;
				color.bgra[1] *= c.g;
				color.bgra[2] *= c.r;
				image.set(x, y, color);
			}
		}
	}
	image.flip_vertically();
	image.write_tga_file(IMAGE_URL);
}

#endif // !_LIGHT_TEST_H_

