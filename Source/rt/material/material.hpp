#pragma once
#include "materialbase.hpp"

namespace cgray {
	namespace rt {
		class Material : public MaterialBase {
		public:
			Material() {
				reset();
			}

			virtual core::Color3f getReflectionColor(const IntersectInfo& info) const override
			{
				return reflective_color();
			}

			virtual core::Color3f getTransmissionColor(const IntersectInfo& info) const override
			{
				return transmissive_color();
			}

			virtual bool isReflective() const override
			{
				return is_reflective_;
			}

			virtual bool isTransmissive() const override
			{
				return is_transmissive_;
			}

			void setShininess(float exponent);
			inline float shininess() const { return shininess_; }
			void setIndexRefraction(float index_refraction);
			inline float indexRefraction() const { return index_refraction_; }

			void setTransmissiveColor(const core::Color3f& color);
			void setReflectiveColor(const core::Color3f& color);
			void setTransmissiveColor(float r, float g, float b);
			void setReflectiveColor(float r, float g, float b);
			core::Color3f transmissive_color() const;
			core::Color3f reflective_color() const;

			void reset();

		protected:
			float shininess_;		// shininess exponent
			float index_refraction_;
			float index_refraction_inv_;	// 1/index_refraction_
			core::Color3f transmissive_color_;
			core::Color3f reflective_color_;

			bool is_reflective_;	// reflective flag
			bool is_transmissive_;	// transmissive flag
		};


		inline void Material::setShininess(float exponent) {
			shininess_ = exponent;
		}
		
		inline void Material::setIndexRefraction(float index_refraction) {
			index_refraction_ = index_refraction;
			index_refraction_inv_ = 1.0f / index_refraction;
		}

		void Material::setTransmissiveColor(const core::Color3f& color) {
			transmissive_color_ = color;
		}

		inline void Material::setReflectiveColor(const core::Color3f & color) {
			reflective_color_ = color;
		}

		inline void Material::setTransmissiveColor(float r, float g, float b) {
			transmissive_color_ = core::Color3f(r, g, b);
		}

		inline void Material::setReflectiveColor(float r, float g, float b) {
			reflective_color_ = core::Color3f(r, g, b);
		}

		inline core::Color3f Material::transmissive_color() const {
			return transmissive_color_;
		}

		inline core::Color3f Material::reflective_color() const {
			return reflective_color_;
		}

		inline void Material::reset() {
			shininess_ = 0.0f;
			setAmbient(0.1f, 0.1f, 0.1f);
			setDiffuse(0.5f, 0.5f, 0.5f);
			setSpecular(1.0f, 1.0f, 1.0f);
			setEmissive(0.0f, 0.0f, 0.0f);
			setTransmissiveColor(0.0f, 0.0f, 0.0f);
			setReflectiveColor(0.2f, 0.2f, 0.2f);
			setIndexRefraction(1.0f);
		}



	}
}
