#include "camera.hpp"

namespace cgray {
	rt::Camera::Camera(Vector3f direction, Vector3f up)
		: direction_(direction), up_(up) {}

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

	rt::PerspectiveCamera::~PerspectiveCamera()
	{

	}

	rt::Ray rt::PerspectiveCamera::generateRay(int x, int y) const
	{

	}

	void rt::PerspectiveCamera::norm()
	{
		right_ = direction_.cross(up_);
		up_ = right_.cross(direction_);
		direction_.normalize();
		right_.normalize();
		up_.normalize();
	}

}
