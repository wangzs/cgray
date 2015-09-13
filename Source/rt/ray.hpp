/*!
 * \file ray.hpp
 * \date 2015/09/12 22:59
 *
 * \author 
 * Contact: xxx@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
#pragma once

#include "../core/math.hpp"

namespace cgray {
	namespace rt {
		class Ray {
		public:
			Ray() {}

			Ray(Vector3f origin, Vector3f target)
				: origin_(origin){
				direction_ = (target - origin).normalized();
			}

			// get and set
			void setOrigin(const Vector3f& origin) {
				origin_ = origin;
			}
			const Vector3f& origin() const {
				return origin_;
			}
			void setDirection(const Vector3f& direction) {
				direction_ = direction.normalized();
			}
			const Vector3f& direction() const {
				return direction_;
			}

			// getPoint(float distance)
			Vector3f getPoint(float distance) const {
				return origin_ + distance * direction_;
			}

		private:
			Vector3f origin_;
			Vector3f direction_;
		};
	}
}