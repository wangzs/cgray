/*!
 * \file materialbase.hpp
 * \date 2015/10/01 22:11
 *
 * \author wangzs
 * Contact: wang.zhenshui@gmail.com
 *
 * \brief: material params - http://www.nicoptere.net/dump/materials.html 
 *						http://globe3d.sourceforge.net/g3d_html/gl-materials__ads.htm
 *
 * TODO: long description
 *
 * \note
*/
#pragma once
#include "../../core/color.hpp"
#include "../shape/baseshape.hpp"


namespace cgray {
	namespace rt {
		class MaterialBase {
		public:
			// get and set
			inline void setAmbient(const core::Color3f& color) {
				ambient_color_ = color;
			}
			inline void setDiffuse(const core::Color3f& color) {
				diffuse_color_ = color;
			}
			inline void setSpecular(const core::Color3f& color) {
				specular_color_ = color;
			}
			inline void setEmissive(const core::Color3f& color) {
				emissive_color_ = color;
			}

			inline void setAmbient(float r, float g, float b) {
				ambient_color_ = core::Color3f(r, g, b);
			}
			inline void setDiffuse(float r, float g, float b) {
				diffuse_color_ = core::Color3f(r, g, b);
			}
			inline void setSpecular(float r, float g, float b) {
				specular_color_ = core::Color3f(r, g, b);
			}
			inline void setEmissive(float r, float g, float b) {
				emissive_color_ = core::Color3f(r, g, b);
			}

			inline const core::Color3f ambient_color() const {
				return ambient_color_;
			}
			inline const core::Color3f diffuse_color() const {
				return diffuse_color_;
			}
			inline const core::Color3f specular_color() const {
				return specular_color_;
			}
			inline const core::Color3f emissive_color() const {
				return emissive_color_;
			}

			virtual core::Color3f getReflectionColor(const IntersectInfo& info) const = 0;
			virtual core::Color3f getTransmissionColor(const IntersectInfo& info) const = 0;

			virtual bool isReflective() const = 0;
			virtual bool isTransmissive() const = 0;

		protected:
			core::Color3f ambient_color_;
			core::Color3f diffuse_color_;
			core::Color3f specular_color_;
			core::Color3f emissive_color_;
		};
	}
}
