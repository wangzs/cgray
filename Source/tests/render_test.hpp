#pragma once

#include "../core/math.hpp"
#include "../core/image.hpp"
#include "../core/render.hpp"

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
			core::Image image(100, 100);
			rt::Render render;
			render.test_rendering0(image);
			image.flushToFile("png_result/render0.png");
		}
	}
}
