#pragma once
#include "baseshape.hpp"

namespace cgray {
	namespace rt {
		class AABB : public Shape {
		public:
			AABB();
			AABB(const Vector3f& p1, const Vector3f& p2);

			virtual bool intersect(const Ray& ray, IntersectInfo& info) override;

			Vector3f getCenter() const;

			void setBoundBox(const Vector3f& min, const Vector3f& max);

			float volumn() const;

			inline const Vector3f& min() const {
				return min_;
			}
			inline const Vector3f& max() const {
				return max_;
			}

			AABB operator + (const AABB& ref) const;
			void operator += (const AABB& ref);

			virtual Vector3f getNormal(const Vector3f& pos) const override;

			virtual bool getAABB(AABB& box) const override;

		private:
			Vector3f min_, max_;
		};
	}
}
