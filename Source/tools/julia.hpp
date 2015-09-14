/*!
 * \file julia.hpp
 * \date 2015/09/13 15:56
 *
 * \author wangzs
 * Contact: wang.zhenshui@gmail.com
 *
 * \brief 
 *
 * TODO: https://graphics.cg.uni-saarland.de/courses/winter-term-201415/computer-graphics-1/course-schedule/
 *
 * \note
*/
#pragma once

#include "../core/typedef.hpp"
#include "../core/math.hpp"
#include "../core/color.hpp"
#include "../rt/ray.hpp"

namespace cgray {
	namespace tools {
		using core::Color3f;

		// The epsilon value adjustment for precision errors.
		static const float epsilon = 0.000001f;
		// The mathematical pi constant
		static const float pi = 3.141592f;
		static const int numIter = 512;


		// Returns the fractional part of a number. For negative numbers it returns the negative fractional
		float fractional(float f) {
			float intpart;
			return modff(f, &intpart);
		}

		// Returns the difference between the given value and the nearest lower integer. Always in range [0, 1)
		float absfractional(float f) {
			float fr = fractional(f);
			if (fr >= 0) return fr;
			fr += 1.0f;
			if (fr >= 1.0f) //can happed due to epsilon errors
				return 0.0f;
			return fr;
		}

		
		/* For Assignment 1 - do not modify */
		static int julia(const Vector3f& v, const Vector3f& c) {
			Vector3f p = v - Vector3f(0.0f, 0.0f, 0.0f);
			int i = 0;
			for (i = 0; i < numIter; ++i) {
				if (p.squaredNorm() > 1.0e+8)
					break;
				Vector3f q = p;
				q[1] = -p[1];
				p = Vector3f(q.dot(p), q.cross(p)[2], 0.0f) + c - Vector3f(0.0f, 0.0f, 0.0f);
			}
			return i;
		}

		static float a1computeWeight(float fx, float fy, const Vector3f& c, float div) {
			Vector3f v(fx, fy, 0.5f);
			v = v - Vector3f(0.5f, 0.5f, 0.5f);
			v = v * 2.0f;
			int numIter = julia(v, c);
			return numIter / (numIter + div);
		}

		static Color3f a1computeColor(uint32 x, uint32 y, uint32 width, uint32 height) {
			float fx = float(x) / float(width);
			float fy = float(y) / float(height);
			Color3f color = Color3f::rep(0.0f);
			color = color + a1computeWeight(fx, fy, Vector3f(-0.8f, 0.156f, 0.0f), 64.0f) * Color3f(0.8f, 0.8f, 1.0f);
			color = color + a1computeWeight(fx, fy, Vector3f(-0.6f, 0.2f, 0.0f), 64.0f)*0.2f * Color3f(0.5f, 0.5f, -0.2f);
			color = color + a1computeWeight(fy, fx, Vector3f(0.285f, 0.0f, 0.0f), 64.0f) * Color3f(0.2f, 0.3f, 0.4f);
			return Color3f::rep(1.0f) - color;
		}




		static float a2computeWeight(float fx, float fy, const Vector3f& c, float div) {
			Vector3f v(fx, fy, 0.0f);
			int numIter = julia(v, c);
			return numIter / (numIter + div);
		}

		static Color3f a2computeColor(const rt::Ray& r) {
			float theta = asin(r.direction()[2]) / pi * 2;
			float phi = atan2(r.direction()[1], r.direction()[0]) / pi;
			float ofx = absfractional((r.origin()[0] + 1.0f) / 2.0f)*2.0f - 1.0f;
			float ofy = absfractional((r.origin()[1] + 1.0f) / 2.0f)*2.0f - 1.0f;
			Color3f color = Color3f::rep(0.0f);
			color = color + a2computeWeight(phi, theta, Vector3f(-0.8f, 0.156f, 0.0f), 64.0f) * Color3f(0.8f, 0.8f, 1.0f);
			color = color + a2computeWeight(phi, theta, Vector3f(-0.6f, 0.2f, 0.0f), 64.0f)*0.2f * Color3f(0.5f, 0.5f, -0.2f);
			color = color + a2computeWeight(ofy, ofx, Vector3f(0.285f, 0.0f, 0.0f), 64.0f) * Color3f(0.4f, 0.5f, 0.6f);
			color = Color3f::rep(1.0f) - color;
			if (absfractional(theta / (2 * pi) * 90) < 0.03) color = Color3f(0.9f, 0.5f, 0.5f)*0.7f;
			if (absfractional(phi / (2 * pi) * 90) < 0.03) color = Color3f(0.9f, 0.9f, 0.5f)*0.7f;
			return color;
		}

	}
}
