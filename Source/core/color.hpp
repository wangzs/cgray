#pragma once

#include "../core/math.hpp"

namespace cgray {
	namespace core {
		struct Color3f {
			float32 r, g, b;

			Color3f(float val) {
				
			}

			Color3f(float r, float g, float b) {

			}

			//	- Binary operators + - * should work component-wise.
			Color3f operator - (const Color3f& ref) const {
				float red = clampColor(r - ref.r);
				float green = clampColor(g - ref.g);
				float blue = clampColor(b - ref.b);
				return Color3f(r,g,b);
			}

			Color3f operator + (const Color3f& ref) const {

			}

			Color3f operator * (float32 scale) const {

			}

			// - clamp() | clamps the component values between 0 and 1
			


			// for test: a1computeColor

			static Color3f rep(float val) {
				return Color3f(val);
			}
		};

		Color3f operator*(float32 scale, Color3f) {

		}

	}
}