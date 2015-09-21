#pragma once
#include "baseshape.hpp"

#include <cassert>

namespace cgray {
	namespace rt {
		class Triangle : public Shape {
		public:
			Triangle();
			Triangle(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2);


			virtual bool intersect(const Ray& ray, IntersectInfo& info) override;

			inline const Vector3f& vertex(int index) const {
				assert(0 <= index && index <= 2);
				return vertex_[index];
			}

			inline Vector3f getMidPoint() const {
				return Vector3f((vertex_[0] + vertex_[1] + vertex_[2])/3.0f);
			}

			virtual Vector3f getNormal(const Vector3f& pos) const override;

			virtual bool getAABB(AABB& box) const override;


		private:
			Vector3f vertex_[3];
		};
	}
}