#pragma once
#include "..\..\core\color.hpp"

namespace cgray {
	namespace rt {
		struct LightHit {
			Vector3f direction;		// light -> object
			float distance;

			LightHit(const Vector3f& dir, float dist);
		};

		class Light {
		public:
			Light(const Vector3f& direction, const core::Color3f& color);

			virtual LightHit getLightHit(const Vector3f& point) const = 0;
			virtual core::Color3f getLightIntensity(const LightHit& hit_info) const = 0;

		protected:
			core::Color3f color_;
			Vector3f direction_;
		};


		/**
		 * Directional Light, like sun light  
		 */
		class DirectionalLight : public Light {
		public:
			DirectionalLight();
			DirectionalLight(const Vector3f& direction, const core::Color3f& color = core::Color3f::WHITE);

			virtual LightHit getLightHit(const Vector3f& point) const override;

			virtual core::Color3f getLightIntensity(const LightHit& hit_info) const override;
		};


		/**
		 * Spot Light, like flashlight
		 */
		class SpotLight : public Light {
		public:
			SpotLight();
			SpotLight(const Vector3f& position, const Vector3f& destination, float inner, float outer, const core::Color3f& color = core::Color3f::WHITE);

			virtual LightHit getLightHit(const Vector3f& point) const override;

			virtual core::Color3f getLightIntensity(const LightHit& hit_info) const override;

		private:
			Vector3f position_;
			float inner_angle_;	// inner cone angle (degree)
			float outer_angle_;	// outer cone angle (degree)
			float epsilon_;		// cos(outer) - cos(inner)
		};


		/**
		 * Point Light 
		 */
		class PointLight : public Light {
		public:
			PointLight();
			PointLight(const Vector3f& position, const core::Color3f& color = core::Color3f::WHITE);

			virtual LightHit getLightHit(const Vector3f& point) const override;

			virtual core::Color3f getLightIntensity(const LightHit& hit_info) const override;

			void configByDistance(float distance);

		private:
			Vector3f position_;
			float kc_, kl_, kq_;
		};

	}
}