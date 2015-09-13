#pragma once

#include "../core/math.hpp"

namespace cgray {
	namespace core {
		struct Color3f {
			float32 r, g, b;

			Color3f(float val) {
				r = g = b = clampColor(val);
			}

			Color3f(float red, float green, float blue) {
				r = clampColor(red);
				g = clampColor(green);
				b = clampColor(blue);
			}

			//	- Binary operators + - * should work component-wise.
			Color3f operator - (const Color3f& ref) const {
				return Color3f(r - ref.r, g - ref.g, b - ref.b);
			}

			Color3f operator + (const Color3f& ref) const {
				return Color3f(r + ref.r, g + ref.g, b + ref.b);
			}

			Color3f operator * (const Color3f& ref) const {
				return Color3f(r*ref.r, g*ref.g, b*ref.b);
			}

			void operator -= (const Color3f& ref) {
				this->r -= ref.r;
				this->g -= ref.g;
				this->b -= ref.b;
				clamp();
			}

			void operator += (const Color3f& ref) {
				this->r += ref.r;
				this->g += ref.g;
				this->b += ref.b;
				clamp();
			}

			void operator *= (const Color3f& ref) {
				this->r *= ref.r;
				this->g *= ref.g;
				this->b *= ref.b;
			}

			Color3f operator * (float32 scale) const {
				return Color3f(scale*r, scale*g, scale*b);
			}

			void operator *= (float32 scale) {
				this->r *= scale;
				this->g *= scale;
				this->b *= scale;
				clamp();
			}

			// - clamp() | clamps the component values between 0 and 1
			void clamp() {
				this->r = clampColor(r);
				this->g = clampColor(g);
				this->b = clampColor(b);
			}


			// for test: a1computeColor

			static Color3f rep(float val) {
				return Color3f(val);
			}
		};

		inline Color3f operator*(float32 scale, Color3f color) {
			return color * scale;
		}

	}
}