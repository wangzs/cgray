#include "plane.hpp"

cgray::rt::Plane::Plane()
	: point_(.0f,.0f,.0f), normal_(.0f,1.0f,.0f)
{
}

cgray::rt::Plane::Plane(Vector3f point, Vector3f normal_vec)
	: point_(point), normal_(normal_vec.normalized())
{
}


bool cgray::rt::Plane::intersect(const Ray& ray, IntersectInfo& info)
{
	float denom = normal_.dot(ray.direction());
	if (denom > M_EPSILON) {
		float t = (point_ - ray.origin()).dot(normal_) / denom;
		if (t >= 0) {
			info.hit_point = ray.origin() + t * ray.direction();
			info.hit_shape = std::make_shared<Plane>(*this);
			info.is_hit = true;
			info.normal = normal_;
			info.ray = ray;

			return true;
		}
	}
	return false;
}

void cgray::rt::Plane::setPoint(const Vector3f & point)
{
	point_ = point;
}

void cgray::rt::Plane::setNormal(const Vector3f & normal_vec)
{
	normal_ = normal_vec.normalized();
}

