#pragma once
#include "baseshape.hpp"

namespace cgray {
	namespace rt {
		enum class AxisType : char {
			XAxis = 0,
			YAxis = 1,
			ZAxis = 2
		};

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
			AABB operator + (const Vector3f& point) const;
			void operator += (const AABB& ref);
			void operator += (const Vector3f& point);

			inline AxisType getLongestAxis() const {
				Vector3f diff = max_ - min_;
				if (diff[0] >= diff[1] && diff[0] >= diff[2]) return AxisType::XAxis;
				else if (diff[1] > diff[0] && diff[1] > diff[2]) return AxisType::YAxis;
				return AxisType::ZAxis;
			}

			virtual Vector3f getNormal(const Vector3f& pos) const override;

			inline Vector3f diagonal() const {
				return max_ - min_;
			}

			virtual bool getAABB(AABB& box) const override;

		private:
			Vector3f min_, max_;
		};
	}
}
