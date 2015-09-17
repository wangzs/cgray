#pragma once

#include "../core/math.hpp"
#include "../core/image.hpp"
#include "../rt/render.hpp"
#include "../rt/camera.hpp"


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
	}
}
