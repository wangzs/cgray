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

#define _USE_MATH_DEFINES
#include <cmath>

using namespace Eigen;

#define M_EPSILON 1e-5

namespace cgray {
	inline bool isApproximateZero(float v) {
		return -M_EPSILON < v && v < M_EPSILON;
	}

	inline float32 clampColor(float32 color) {
		return color > 1.0f ? 1.0f : (color < .0f ? .0f : color);
	}

	inline float32 dToR(float32 degree) {
		return (float)(degree * M_PI / 180.0f);
	}

	inline float32 rToD(float radian) {
		return (float)(radian * 180.0f / M_PI);
	}

	inline float32 clamp(float32 val, float32 min, float32 max) {
		return val < min ? min : (val > max ? max : val);
	}

}