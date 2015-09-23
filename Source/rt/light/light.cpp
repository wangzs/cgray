#include "light.hpp"

using namespace cgray;

cgray::rt::LightHit::LightHit(const Vector3f & dir, float dist)
	: direction(dir), distance(dist)
{
}

cgray::rt::Light::Light(const Vector3f & direction, const core::Color3f & color)
	: color_(color), direction_(direction.normalized())
{
}

cgray::rt::DirectionalLight::DirectionalLight()
	: Light(Vector3f(-0.5f, -0.5f, -0.5f), core::Color3f::WHITE)
{
}

cgray::rt::DirectionalLight::DirectionalLight(const Vector3f & direction, const core::Color3f & color)
	: Light(direction, color)
{
}

cgray::rt::LightHit cgray::rt::DirectionalLight::getLightHit(const Vector3f & point) const
{
	return LightHit(direction_, FLT_MAX);	// directional light infinitely far away from source
}

cgray::core::Color3f cgray::rt::DirectionalLight::getLightIntensity(const LightHit & hit_info) const
{
	return color_;
}

cgray::rt::SpotLight::SpotLight()
	: Light(Vector3f(-1.0f, -1.0f, -1.0f), core::Color3f::WHITE),
	position_(1.0f, 1.0f, 1.0f),
	inner_angle_(25.f), outer_angle_(35.0f)
{
	epsilon_ = cos(outer_angle_) - cos(inner_angle_);
}

cgray::rt::SpotLight::SpotLight(const Vector3f & position, const Vector3f & destination, float inner, float outer, const core::Color3f& color)
	: Light(destination- position, color),
	position_(position),
	inner_angle_(25.f), outer_angle_(60.0f)
{
	epsilon_ = cos(outer_angle_) - cos(inner_angle_);
}

cgray::rt::LightHit cgray::rt::SpotLight::getLightHit(const Vector3f& point) const
{
	Vector3f direction = point - position_;
	return LightHit(direction.normalized(), direction.norm());
}

core::Color3f cgray::rt::SpotLight::getLightIntensity(const LightHit& hit_info) const
{
	static float cos_outer = cos(outer_angle_);
	float theta = direction_.dot(hit_info.direction);
	float intensity = clamp((cos_outer - theta) / epsilon_, 0.0f, 1.0f);
	// FIXME consider the distance attenuation
	return intensity * color_;
}

cgray::rt::PointLight::PointLight()
	: Light(Vector3f(1.0f, 1.0f, 1.0f), core::Color3f::WHITE)
{
	kc_ = 1.0f; kl_ = 0.09f; kq_ = 0.032f;
}

cgray::rt::PointLight::PointLight(const Vector3f & position, const core::Color3f & color)
	: Light(position, color)
{
	kc_ = 1.0f; kl_ = 0.09f; kq_ = 0.032f;
}

cgray::rt::LightHit cgray::rt::PointLight::getLightHit(const Vector3f& point) const
{
	Vector3f direction = point - position_;
	return LightHit(direction.normalized(), direction.norm());
}

core::Color3f cgray::rt::PointLight::getLightIntensity(const LightHit& hit_info) const
{
	// Attenuation = Constant + Linear * Distance + Quadratic * Distance ^ 
	float attenuation = kc_ + kl_ * hit_info.distance + kq_ * hit_info.distance * hit_info.distance;
	// FIXME consider the distance attenuation
	return attenuation * color_;
}

void cgray::rt::PointLight::configByDistance(float distance)
{
	kc_ = 1.0f;
	if (distance < 13) {
		kl_ = 0.7f; kq_ = 1.8f;
	}
	else if (distance >= 13 && distance < 20) {
		kl_ = 0.35f; kq_ = 0.44f;
	}
	else if (distance >= 20 && distance < 32) {
		kl_ = 0.22f; kq_ = 0.20f;
	}
	else if (distance >= 32 && distance < 50) {
		kl_ = 0.14f; kq_ = 0.07f;
	}
	else if (distance >= 50 && distance < 65) {
		kl_ = 0.09f; kq_ = 0.032f;
	}
	else if (distance >= 65 && distance < 100) {
		kl_ = 0.07f; kq_ = 0.017f;
	}
	else if (distance >= 100 && distance < 160) {
		kl_ = 0.045f; kq_ = 0.0075f;
	}
	else if (distance >= 160 && distance < 200) {
		kl_ = 0.027f; kq_ = 0.0028f;
	}
	else if (distance >= 200 && distance < 325) {
		kl_ = 0.022f; kq_ = 0.0019f;
	}
	else if (distance >= 325 && distance < 600) {
		kl_ = 0.014f; kq_ = 0.0007f;
	}
	else {
		kl_ = 0.007f; kq_ = 0.0002f;
	}
}
