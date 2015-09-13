#include "camera.hpp"

namespace cgray {
	rt::Camera::Camera(Vector3f direction, Vector3f up)
		: direction_(direction), up_(up) {}

	void rt::Camera::setCameraParams(const Vector3f & direction, const Vector3f & up)
	{
		direction_ = direction.normalized();
		right_ = direction.cross(up).normalized();
		up_ = right_.cross(direction).normalized();
	}

	const Vector3f & rt::Camera::direction() const
	{
		return direction_;
	}

	const Vector3f & rt::Camera::up() const
	{
		return up_;
	}

	const Vector3f & rt::Camera::right() const
	{
		return right_;
	}

	rt::PerspectiveCamera::PerspectiveCamera()
		: Camera(Vector3f(.0f, .0f, .0f), Vector3f(.0f, 1.0f, .0f)),
		pos_(Vector3f(.0f, .0f, 1.0f)), fov_(90.0f), res_x_(800), res_y_(600)
	{
		norm();
	}

	rt::PerspectiveCamera::PerspectiveCamera(Vector3f pos, Vector3f direction, Vector3f up, float fov, int res_x, int res_y)
		: Camera(direction, up), pos_(pos), fov_(fov), res_x_(res_x), res_y_(res_y)
	{
		norm();
	}

	rt::Ray rt::PerspectiveCamera::generateRay(int x, int y) const
	{
		static float tan_fov = std::tan(dToR(fov_ / 2));
		float32 x0 = (float)x / (float)res_x_;
		float32 y0 = (float)y / (float)res_y_;
		Ray ray;
		ray.setOrigin(pos_);
		Vector3f direction = direction_ + right_ * ((x0 - 0.5f) * tan_fov) + up_ * ((y0 - 0.5f) * tan_fov);
		ray.setDirection(direction);
		return ray;
	}

	void rt::PerspectiveCamera::norm()
	{
		right_ = direction_.cross(up_);
		up_ = right_.cross(direction_);
		direction_.normalize();
		right_.normalize();
		up_.normalize();
	}


	rt::Ray cgray::rt::OrthographicCamera::generateRay(int x, int y) const
	{
		// TODO
		return Ray();
	}
}


