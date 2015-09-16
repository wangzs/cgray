#include "sphere.hpp"

cgray::rt::Sphere::Sphere()
	: center_(0.0f,.0f,.0f), radius_(.5f)
{
}

cgray::rt::Sphere::Sphere(const Vector3f & center, float radius)
	: center_(center), radius_(radius)
{
}

bool cgray::rt::Sphere::intersect(const Ray & ray, IntersectInfo & info)
{
	Vector3f vec_l = ray.origin() - center_;
	float len_square = vec_l.squaredNorm();
	float a = ray.direction().squaredNorm();
	float b = 2 * ray.direction().dot(vec_l);
	float c = len_square - radius_ * radius_;

	float delta = b * b - 4 * a * c;
	if (delta < M_EPSILON) {
		return false;
	}
	delta = sqrtf(delta);
	// ray can intersect the sphere, and get the closer hitpoint
	float t = (-0.5f) * (b + delta) / a;
	// set intersection info
	info.hit_point = ray.origin() + ray.direction() * t;
	info.is_hit = true;
	info.hit_shape = std::make_shared<Sphere>(*this);
	info.normal = (info.hit_point - center_).normalized();
	info.ray = ray;

	return true;
}

void cgray::rt::Sphere::setCenter(const Vector3f & center)
{
	center_ = center;
}

void cgray::rt::Sphere::setRadius(float radius)
{
	radius_ = radius;
}

