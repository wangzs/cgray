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


		private:
			Vector3f vertex_[3];
		};
	}
}