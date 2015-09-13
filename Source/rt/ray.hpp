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

			Ray(Vector3f origin, Vector3f direction)
				: origin_(origin), direction_(direction) {}


			// get and set
			const Vector3f& origin() const {
				return origin_;
			}
			const Vector3f& direction() const {
				return direction_;
			}

			// getPoint(float distance)

		private:
			Vector3f origin_;
			Vector3f direction_;
		};
	}
}