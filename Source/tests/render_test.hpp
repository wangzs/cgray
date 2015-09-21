#pragma once

#include "../core/math.hpp"
#include "../core/image.hpp"
#include "../rt/render.hpp"
#include "../rt/camera.hpp"
#include "../rt/shape/group.hpp"
#include "../rt/shape/sphere.hpp"
#include "../rt/shape/plane.hpp"
#include "../rt/shape/triangle.hpp"
#include "../rt/shape/aabb.hpp"

#include <iostream>

namespace cgray {
	namespace test {
		static void printVector(const Vector3f& a) {
			std::cout << "(" << a[0] << ", " << a[1] << ", " << a[2] << ")" << std::endl;
		}


		static void normlizeTest() {
			Vector3f a(1, 2, 3);
			Vector3f b = a.normalized();

			printVector(a);
			printVector(b);
		}

		static void juliaTest() {
 			core::Image image(400, 400);
 			rt::Render render;
 			render.test_rendering0(image);
 			image.flushToFile("png_result/render0.png");
 
 			core::Image image1(600, 400);
 			std::shared_ptr<rt::Camera> camera(
 				new rt::PerspectiveCamera(Vector3f(0.0,0,1.0f),	// position
 					Vector3f(1.3f,0,0),	// target
 					Vector3f(0.3f,1,0),	// up
 					90,					// fov
 					image1.width(), image1.height()));
 			rt::Render render1(camera);
 			render1.test_rendering1(image1);
 			image1.flushToFile("png_result/render1.png");
 
 			core::Image image2(600, 400);
 			std::shared_ptr<rt::Camera> camera2(
 				new rt::OrthographicCamera(Vector3f(0.0, 0, 5.0f),	// position
 					Vector3f(0.6f, 0.5f, 0),	// target
 					Vector3f(0, 1, 0),	// up
 					image2.width(), image2.height()));
 			rt::Render render2(camera2);
 			render2.test_rendering1(image2);
 			image2.flushToFile("png_result/render2.png");

			core::Image image3(600, 400);
			std::shared_ptr<rt::Camera> camera3(
				new rt::FishEyeCamera(Vector3f(0.0, 0, 4.0f),	
 					Vector3f(1.6f, 0.5f, 0),	// target
 					Vector3f(0.3f,1,0),	// up
 					180,					// fov
					image3.width(), image3.height()));
			rt::Render render3(camera3);
			render3.test_rendering1(image3);
			image3.flushToFile("png_result/render3.png");
		}


		static void renderingTest01() {
			core::Image image0(600, 400);
			core::Image image1(600, 400);

			std::shared_ptr<rt::SimpleGroup> scene(new rt::SimpleGroup());

 			scene->add(std::make_shared<rt::Sphere>(rt::Sphere(Vector3f(-2.f, 1.7f, 0), 2)));
 			scene->add(std::make_shared<rt::Sphere>(rt::Sphere(Vector3f(1, -1, 1), 2.2f)));
 			scene->add(std::make_shared<rt::Sphere>(rt::Sphere(Vector3f(3.f, 0.8f, -2), 2.f)));
 			scene->add(std::make_shared<rt::Plane>(rt::Plane(Vector3f(0, -3, 0), Vector3f(0, 1, 0))));
 			scene->add(std::make_shared<rt::Triangle>(rt::Triangle(Vector3f(3, 2, 3), Vector3f(3, 2, -3), Vector3f(0, 0.1f, -2))));
 			scene->add(std::make_shared<rt::Triangle>(rt::Triangle(Vector3f(-2, 3.7f, 0), Vector3f(1, 2, 1), Vector3f(3, 2.8f, -2))));
 			scene->add(std::make_shared<rt::Triangle>(rt::Triangle(Vector3f(3, -2, 3), Vector3f(3, -2, -3), Vector3f(-3, -2, -3))));
 			scene->add(std::make_shared<rt::AABB>(rt::AABB(Vector3f(2, 1.5f, -0.5f), Vector3f(3, 2.5f, 2.5f))));
			scene->add(std::make_shared<rt::DiscPlane>(rt::DiscPlane(Vector3f(0, -1, 0), Vector3f(0, 1, 0), 1.0f)));


			std::shared_ptr<rt::Camera> camera0(
				new rt::FishEyeCamera(Vector3f(0.0, 0, 4.0f),
					Vector3f(1.6f, 0.5f, 0),	// target
					Vector3f(0.3f, 1, 0),	// up
					180,					// fov
					image0.width(), image0.height()));
			std::shared_ptr<rt::Camera> camera1(
				new rt::PerspectiveCamera(Vector3f(0, 0.5, 10.0f),	// position
					Vector3f(0, 0, -1),	// target
					Vector3f(0, 1, 0),	// up
					90,					// fov
					image0.width(), image0.height()));
			std::shared_ptr<rt::Camera> camera2(
				new rt::OrthographicCamera(Vector3f(0.0, 0, 5.0f),	// position
					Vector3f(0, 0, -1),	// target
					Vector3f(0, 1, 0),	// up
					image0.width(), image0.height(), 20.f));
			rt::Render render(camera1, scene);
			render.test_rendering2(image0);
			render.test_rendering3(image1, core::Color3f(1.0f, 0.2f, 0.0f), 1.f, core::Color3f(0.2f, 1.0f, 0.0f), 8.f);
			image0.flushToFile("png_result/render00.png");
			image1.flushToFile("png_result/render01.png");

		}




		static void renderingTest02() {
			core::Image image0(600, 400);

			std::shared_ptr<rt::SimpleGroup> scene(new rt::SimpleGroup());

			scene->add(std::make_shared<rt::Mesh>(rt::Mesh("../../Build/CgRay/model/cow.obj", "../../Build/CgRay/model/")));

			std::shared_ptr<rt::Camera> camera0(
				new rt::FishEyeCamera(Vector3f(0.0, 0, 4.0f),
					Vector3f(1.6f, 0.5f, 0),	// target
					Vector3f(0.3f, 1, 0),	// up
					180,					// fov
					image0.width(), image0.height()));
			std::shared_ptr<rt::Camera> camera1(
				new rt::PerspectiveCamera(Vector3f(0.0, 0.5, 5.0f),	// position
					Vector3f(0, 0, -1),	// target
					Vector3f(0, 1, 0),	// up
					90,					// fov
					image0.width(), image0.height()));
			std::shared_ptr<rt::Camera> camera2(
				new rt::OrthographicCamera(Vector3f(0.0, 0, 5.0f),	// position
					Vector3f(0, 0, -1),	// target
					Vector3f(0, 1, 0),	// up
					image0.width(), image0.height(), 20.f));
			rt::Render render(camera1, scene);
			render.test_rendering4(image0);
			image0.flushToFile("png_result/render_mesh00.png");
		}





	}
}
