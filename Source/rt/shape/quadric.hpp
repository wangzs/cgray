/*!
 * \file quadric.hpp
 * \date 2015/09/17 22:54
 *
 * \author wangzs
 * Contact: wang.zhenshui@gmail.com
 *
 * \brief - http://www.bmsc.washington.edu/people/merritt/graphics/quadrics.html
 * \note
*/
#pragma once
#include "baseshape.hpp"

namespace cgray {
	namespace rt {
		class Quadric : public Shape {
		public:
			Quadric();
			Quadric(const Vector3f& pos, float a, float b, float c, float d, float e, float f, float g, float h, float i, float j);

			virtual bool intersect(const Ray& ray, IntersectInfo& info) override;

			virtual Vector3f getNormal(const Vector3f& pos) const override;

			virtual bool getAABB(AABB& box) const override;

		private:
			Vector3f position_;
			float A, B, C, D, E, F, G, H, I, J;	// quadric params
		};
	}
}
