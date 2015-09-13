#pragma once

#include "../core/image.hpp"

#include <memory>

namespace cgray {
	namespace rt {
		class Camera;

		class Render {
		public:
			Render() {}

			Render(std::shared_ptr<Camera> camera);

			void rendering(core::Image& output);

			// FIXME: just for test
			void test_rendering0(core::Image& output);

			// FIXME: just for test
			void test_rendering1(core::Image& output);
		};
	}
}
