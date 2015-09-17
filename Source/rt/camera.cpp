#include "camera.hpp"

#ifdef _LOG_INFO
#include <iostream>
#endif

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

	void rt::Camera::norm()
	{
		right_ = direction_.cross(up_);
		up_ = right_.cross(direction_);
		direction_.normalize();
		right_.normalize();
		up_.normalize();
	}

	rt::PerspectiveCamera::PerspectiveCamera()
		: Camera(Vector3f(.0f, .0f, -1.0f), Vector3f(.0f, 1.0f, .0f)),
		pos_(Vector3f(.0f, .0f, 1.0f)), fov_(90.0f), res_x_(400), res_y_(200)
	{
		norm();
	}

	rt::PerspectiveCamera::PerspectiveCamera(Vector3f pos, Vector3f target, Vector3f up, float fov, int res_x, int res_y)
		: Camera(target-pos, up), pos_(pos), fov_(fov), res_x_(res_x), res_y_(res_y)
	{
		norm();
	}

	rt::Ray rt::PerspectiveCamera::generateRay(int x, int y) const
	{
		static float tan_fov = std::tan(dToR(fov_ / 2));
		float x0 = 2.0f * x / res_x_ - 1.0f;
		float y0 = 2.0f * y / res_y_ - 1.0f;
		Ray ray;
		ray.setOrigin(pos_);
		Vector3f direction = direction_ + right_ * (x0 * tan_fov) + up_ * (y0 * tan_fov);
		ray.setDirection(direction);
		return ray;
	}


	rt::OrthographicCamera::OrthographicCamera()
		: Camera(Vector3f(.0f, .0f, -1.0f), Vector3f(.0f, 1.0f, .0f)), pos_(.0f, .0f, 1.0f), res_x_(400), res_y_(200)
	{
		norm();
	}

	rt::OrthographicCamera::OrthographicCamera(Vector3f pos, Vector3f target, Vector3f up, int res_x, int res_y)
		: Camera(target-pos, up), pos_(pos), res_x_(res_x), res_y_(res_y)
	{
		norm();
	}

	rt::Ray cgray::rt::OrthographicCamera::generateRay(int x, int y) const
	{
		float x0 = 2.0f * x / res_x_ - 1.0f;
		float y0 = 2.0f * y / res_y_ - 1.0f;
		Ray ray;
		ray.setDirection(direction_);
		Vector3f pos = pos_ + right_ * x0 + up_ * y0;
		ray.setOrigin(pos);
		return ray;
	}

	rt::FishEyeCamera::FishEyeCamera()
		: Camera(Vector3f(0,0,-1.0f), Vector3f(.0f,1.0f,.0f)), pos_(0.0f,0.0f,1.0f), fov_(90.0f), res_x_(400), res_y_(400)
	{
		norm();
	}

	rt::FishEyeCamera::FishEyeCamera(Vector3f pos, Vector3f target, Vector3f up, float fov, int res_x, int res_y)
		: Camera(target - pos, up), pos_(pos), fov_(fov), res_x_(res_x), res_y_(res_y)
	{
		norm();
	}

	cgray::rt::Ray rt::FishEyeCamera::generateRay(int x, int y) const
	{
		Ray ray;
		float x0 = 2.0f * x / res_x_ - 1.0f;
		float y0 = 2.0f * y / res_y_ - 1.0f;
		float phi = 0.0f;
		// radius
		float r = sqrt(x0*x0 + y0*y0);
		if (r <= 1.0) {
			if (r > -M_EPSILON && r < M_EPSILON) {
				phi = 0.0f;
			}
			else {
				if (x < -M_EPSILON) {
					phi = (float)(M_PI - asin(y0 / r));
				}
				else {
					phi = asin(y0 / r);
				}
			}

			float fov = dToR(fov_);
			float theta = r * (fov / 2.0f);	// 按照投影的长度比例算出在xy平面上与x轴夹角

			ray.setOrigin(pos_);
			float dx = sin(theta)*cos(phi);
			float dy = sin(theta) * sin(phi);
			float dz = cos(theta);
			ray.setDirection(Vector3f(dx, dy, dz));
			return ray;
		}
		return Ray(pos_, direction_);
	}

}


