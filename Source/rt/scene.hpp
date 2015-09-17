/*!
 * \file scene.hpp
 * \date 2015/09/18 0:30
 *
 * \author wangzs
 * Contact: wang.zhenshui@gmail.com
 *
 * \brief - manager all objects
 * \note
*/
#pragma once
#include "shape/baseshape.hpp"
#include "light/light.hpp"
#include "camera.hpp"

#include <memory>

namespace cgray {
	namespace rt {
		class Scene {
		public:
			Scene();

		private:
			std::shared_ptr<Shape> shapes_;
			std::shared_ptr<Light> lights_;
			std::shared_ptr<Camera> camera_;
		};
	}
}