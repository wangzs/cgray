#pragma once

#include "../../core/math.hpp"
#include "../ray.hpp"


#include <memory>
namespace cgray {
	namespace rt {
		class Shape;

		struct IntersectInfo {
			bool is_hit;
			std::shared_ptr<Shape> hit_shape;
			Vector3f hit_point;
			Vector3f normal;
			Ray ray;

			IntersectInfo() {
				is_hit = false;
				hit_shape = nullptr;
			}
		};

		class Shape {
		public:

			virtual bool intersect(const Ray& ray, IntersectInfo& info) = 0;

		};
	}
}