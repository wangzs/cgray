#pragma once

#include "../core/image.hpp"
#include "scene.hpp"
#include "shape/mesh.hpp"

#include <memory>

namespace cgray {
	namespace rt {
		class Camera;

		class Render {
		public:
			Render() {}
			Render(std::shared_ptr<Camera> camera);
			Render(std::shared_ptr<Camera> camera, std::shared_ptr<Group> group);

			void rendering(core::Image& output);

			// FIXME: just for test
			void test_rendering0(core::Image& output);

			// FIXME: just for test
			void test_rendering1(core::Image& output);

			void test_rendering2(core::Image& output);
			void test_rendering3(core::Image& output, const core::Color3f& near_color, float near, const core::Color3f& far_color, float far);

			void test_rendering4(core::Image& output);

			void test_rendering5(core::Image& output);

		private:
			std::shared_ptr<Camera> camera_;
			std::shared_ptr<Group> group_;
			std::shared_ptr<Mesh> mesh_;
		};
	}
}
