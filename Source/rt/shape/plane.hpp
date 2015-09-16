/*!
 * \file plane.hpp
 * \date 2015/09/16 12:51
 *
 * \author wangzs
 * Contact: wang.zhenshui@gmail.com
 *
 * \brief https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection
 *
 * \note
*/
#pragma once
#include "baseshape.hpp"

namespace cgray {
	namespace rt {
		class Plane : public Shape {
		public:
			Plane();
			Plane(const Vector3f& point, const Vector3f& normal);
			Plane(const Plane& ref) = default;

			virtual bool intersect(const Ray&, IntersectInfo& info) override;

			void setPoint(const Vector3f& point);
			void setNormal(const Vector3f& normal_vec);

			inline const Vector3f& point() const {
				return point_;
			}
			inline const Vector3f& normal()	const {
				return normal_;
			}

		protected:
			Vector3f point_;
			Vector3f normal_;
		};


		// disc
		class DiscPlane : public Plane {
		public:
			DiscPlane();
			DiscPlane(const Vector3f& point, const Vector3f& normal, float radius);

			virtual bool intersect(const Ray& ray, IntersectInfo& info) override;

			inline void setRadius(float radius) {
				radius_ = radius;
			}
			inline float radius() const {
				return radius_;
			}

		private:
			float radius_;
		};

	}
}