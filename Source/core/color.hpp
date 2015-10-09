#pragma once

#include "../core/math.hpp"

#ifdef _LOG_INFO
#include <ostream>
#endif

namespace cgray {
	namespace core {
		struct Color3f {
			float32 r, g, b;
			Color3f() {
				r = g = b = 0.0f;
			}

			Color3f(float val) {
				r = g = b = clampColor(val);
			}

			Color3f(float red, float green, float blue) {
				r = clampColor(red);
				g = clampColor(green);
				b = clampColor(blue);
			}

			Color3f(const Color3f& ref) = default;

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


			static Color3f rep(float val) {
				return Color3f(val);
			}

			inline Color3f toGrayScale() const {
				float gray = 0.2126f * r + 0.7152f * g + 0.0722f * b;
				return Color3f(gray, gray, gray);
			}


			// const color variable
			const static Color3f BLACK;
			const static Color3f RED;
			const static Color3f GREEN;
			const static Color3f BLUE;
			const static Color3f YELLOW;
			const static Color3f CYAN;
			const static Color3f MAGENTA;
			const static Color3f WHITE;
		};

		inline Color3f operator*(float32 scale, Color3f color) {
			return color * scale;
		}


		// print
#ifdef _LOG_INFO
		inline std::ostream& operator<< (std::ostream& out, const Color3f& color) {
			out << "(" << color.r << ", " << color.g << ", " << color.b << ")";
			return out;
		}
#endif
		

	}
}