/*!
 * \file baseshape.hpp
 * \date 2015/09/16 23:13
 *
 * \author wangzs
 * Contact: wang.zhenshui@gmail.com
 *
 * \brief: Static Object Intersections - http://www.realtimerendering.com/intersections.html
 * \note
*/
#pragma once

#include "../../core/math.hpp"
#include "../ray.hpp"

#include <memory>
#include <float.h>

namespace cgray {
	namespace rt {
		class Shape;
		class AABB;
		class MaterialBase;

		struct IntersectInfo {
			bool is_hit;
			float dist;
			std::shared_ptr<Shape> hit_shape;
			Vector3f hit_point;
			Vector3f normal;
			Ray ray;

			IntersectInfo() {
				dist = FLT_MAX;
				is_hit = false;
				hit_shape = nullptr;
			}
		};

		class Shape {
		public:

			virtual bool intersect(const Ray& ray, IntersectInfo& info) = 0;

			virtual Vector3f getNormal(const Vector3f& pos) const = 0;

			virtual bool getAABB(AABB& box) const = 0;

			virtual void setMaterial(std::shared_ptr<MaterialBase> material) = 0;
			virtual std::shared_ptr<MaterialBase> material() const = 0;
		};
	}
}