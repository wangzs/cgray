#include "aabb.hpp"
#include <algorithm>

cgray::rt::AABB::AABB()
	: min_(-0.5f,0.0f,-0.5f), max_(0.5f,1.0f,0.5f)
{
}

cgray::rt::AABB::AABB(const Vector3f & p1, const Vector3f & p2)
	: min_(std::min(p1[0], p2[0]), std::min(p1[1], p2[1]), std::min(p1[2], p2[2])), 
	max_(std::max(p1[0], p2[0]), std::max(p1[1], p2[1]), std::max(p1[2], p2[2]))
{
}

/**
 *  slab method: http://www.siggraph.org/education/materials/HyperGraph/raytrace/rtinter3.htm   
 */
bool cgray::rt::AABB::intersect(const Ray & ray, IntersectInfo & info)
{
	// r.dir is unit direction vector of ray
	Vector3f dir_frac;
	dir_frac[0] = 1.0f / ray.direction()[0];
	dir_frac[1] = 1.0f / ray.direction()[1];
	dir_frac[2] = 1.0f / ray.direction()[2];
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = (min_[0] - ray.origin()[0])*dir_frac[0];
	float t2 = (max_[0] - ray.origin()[0])*dir_frac[0];
	float t3 = (min_[1] - ray.origin()[1])*dir_frac[1];
	float t4 = (max_[1] - ray.origin()[1])*dir_frac[1];
	float t5 = (min_[2] - ray.origin()[2])*dir_frac[2];
	float t6 = (max_[2] - ray.origin()[2])*dir_frac[2];

	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0) {
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax) {
		return false;
	}

	// set intersection info
	info.hit_point = ray.origin() + ray.direction() * tmin;
	info.hit_shape = std::make_shared<AABB>(*this);
	info.is_hit = true;
	info.normal = Vector3f(1.0f,0,0);	//FIXME
	info.ray = ray;

	return true;
}

Vector3f cgray::rt::AABB::getCenter() const
{
	return min_ + (max_ + min_) / 2;
}

void cgray::rt::AABB::setBoundBox(const Vector3f & min, const Vector3f & max)
{
	min_ = min;
	max_ = max;
}

float cgray::rt::AABB::volumn() const
{
	return (max_[0] - min_[0])*(max_[1] - min_[1])*(max_[2] - min_[2]);
}

Eigen::Vector3f cgray::rt::AABB::getNormal(const Vector3f& pos) const
{
	Vector3f min_vec = pos - min_;
	Vector3f max_vec = pos - max_;

	// corner point
	if ((isApproximateZero(min_vec[0]) && isApproximateZero(min_vec[1]))
		|| (isApproximateZero(min_vec[0]) && isApproximateZero(min_vec[2]))
		|| (isApproximateZero(min_vec[1]) && isApproximateZero(min_vec[2]))
		|| (isApproximateZero(max_vec[0]) && isApproximateZero(max_vec[1]))
		|| (isApproximateZero(max_vec[1]) && isApproximateZero(max_vec[2]))
		|| (isApproximateZero(max_vec[0]) && isApproximateZero(max_vec[2]))
		) {
		return Vector3f(0.0f,0.0f,0.0f);
	}

	float left = min_vec.dot(Vector3f(-1.0f, 0.0f, 0.0f));
	float right = min_vec.dot(Vector3f(1.0f, 0.0f, 0.0f));
	float up = min_vec.dot(Vector3f(0.0f, 1.0f, 0.0f));
	float bottom = min_vec.dot(Vector3f(0.0f, -1.0f, 0.0f));
	float back = min_vec.dot(Vector3f(0.0f, 0.0f, -1.0f));
	float front = min_vec.dot(Vector3f(0.0f, 0.0f, 1.0f));
	if (-M_EPSILON < left && left < M_EPSILON) {
		return Vector3f(-1.0f, 0.0f, 0.0f);
	} 
	if (-M_EPSILON < right && right < M_EPSILON) {
		return Vector3f(1.0f, 0.0f, 0.0f);
	}
	if (-M_EPSILON < up && up < M_EPSILON) {
		return Vector3f(0.0f, 1.0f, 0.0f);
	}
	if (-M_EPSILON < bottom && bottom < M_EPSILON) {
		return Vector3f(0.0f, -1.0f, 0.0f);
	}
	if (-M_EPSILON < back && back < M_EPSILON) {
		return Vector3f(0.0f, 0.0f, -1.0f);
	}
	if (-M_EPSILON < front && front < M_EPSILON) {
		return Vector3f(0.0f, 0.0f, 1.0f);
	}
}

bool cgray::rt::AABB::getAABB(AABB& box) const
{
	box = *this;
	return true;
}

cgray::rt::AABB cgray::rt::AABB::operator+(const AABB & ref) const
{
	Vector3f new_min(std::min(min_[0], ref.min_[0]), std::min(min_[1], ref.min_[1]), std::min(min_[2], ref.min_[2]));
	Vector3f new_max(std::max(max_[0], ref.max_[0]), std::max(max_[1], ref.max_[1]), std::max(max_[2], ref.max_[2]));
	return AABB(new_min, new_max);
}

void cgray::rt::AABB::operator+=(const AABB & ref)
{
	min_ = Vector3f(std::min(min_[0], ref.min_[0]), std::min(min_[1], ref.min_[1]), std::min(min_[2], ref.min_[2]));
	max_ = Vector3f(std::max(max_[0], ref.max_[0]), std::max(max_[1], ref.max_[1]), std::max(max_[2], ref.max_[2]));

}
