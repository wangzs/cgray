#include "plane.hpp"

cgray::rt::Plane::Plane()
	: point_(.0f,.0f,.0f), normal_(.0f,1.0f,.0f)
{
}

cgray::rt::Plane::Plane(const Vector3f& point, const Vector3f& normal_vec)
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

Eigen::Vector3f cgray::rt::Plane::getNormal(const Vector3f& pos) const
{
	return normal_;
}

bool cgray::rt::Plane::getAABB(AABB& box) const
{
	// ? not need aabb
	return false;
}

cgray::rt::DiscPlane::DiscPlane()
	: Plane(Vector3f(.0f, .0f, .0f), Vector3f(.0f, 1.0f, .0f)), radius_(1.0f)
{
}

cgray::rt::DiscPlane::DiscPlane(const Vector3f & point, const Vector3f & normal, float radius)
	: Plane(point, normal), radius_(1.0f)
{
}

bool cgray::rt::DiscPlane::intersect(const Ray & ray, IntersectInfo & info)
{
	static float r2 = radius_ * radius_;
	float denom = normal_.dot(ray.direction());
	if (denom > M_EPSILON) {
		float t = (point_ - ray.origin()).dot(normal_) / denom;
		if (t >= 0) {
			Vector3f hit_point = ray.origin() + t * ray.direction();
			float dist2 = (hit_point - point_).squaredNorm();
			if (dist2 <= r2) {
				info.hit_point = hit_point;
				info.hit_shape = std::make_shared<Plane>(*this);
				info.is_hit = true;
				info.normal = normal_;
				info.ray = ray;

				return true;
			}
		}
	}
	return false;
}
