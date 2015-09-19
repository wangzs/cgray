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
#include "shape/group.hpp"
#include <memory>

namespace cgray {
	namespace rt {
		class Scene {
		public:
			Scene();

			inline void setWorld(std::shared_ptr<Group> objs) {
				worlds_ = objs;
			}
			inline void setLight(std::shared_ptr<Light> light) {
				light_ = light;
			}

		private:
			std::shared_ptr<Group> worlds_;
			std::shared_ptr<Light> light_;
		};
	}
}