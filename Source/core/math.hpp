/*!
 * \file math.hpp
 * \date 2015/09/12 23:18
 *
 * \author wangzs
 * Contact: wang.zhenshui@gmail.com
 *
 * \brief 
 *
 * TODO: Eigen�ο�http://eigen.tuxfamily.org/dox-devel/group__QuickRefPage.html
 *
 * \note
*/
#pragma once

#include "typedef.hpp"

// Matrix and Array classes, basic linear algebra (including triangular and self adjoint products), array manipulation
#include <Eigen/Core>
// Transform, Translation, Scaling, Rotation2D and 3D rotations (Quaternion, AngleAxis)
#include <Eigen/Geometry>
#include <Eigen/Dense>

using namespace Eigen;

namespace cgray {

	inline float32 clampColor(float32 color) {
		return color > 1.0f ? 1.0f : (color < .0f ? .0f : color);
	}


}