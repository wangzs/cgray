#pragma once
#include "baseshape.hpp"

namespace cgray {
	namespace rt {
		class Sphere : public Shape {
		public:
			Sphere();
			Sphere(const Vector3f& center, float radius);

			virtual bool intersect(const Ray& ray, IntersectInfo& info) override;

			void setCenter(const Vector3f& center);
			void setRadius(float radius);

			inline Vector3f center() const {
				return center_;
			}
			inline float radius() const {
				return radius_;
			}

			virtual Vector3f getNormal(const Vector3f& pos) const override;

			virtual bool getAABB(AABB& box) const override;

		private:
			Vector3f center_;
			float radius_;
		};
	}
}
