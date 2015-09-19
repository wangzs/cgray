#include "triangle.hpp"

cgray::rt::Triangle::Triangle()
{
	vertex_[0] = Vector3f(-0.5f, 0, 0);
	vertex_[1] = Vector3f(0.5f, 0, 0);
	vertex_[2] = Vector3f(0, 0.5f, 0);
}

cgray::rt::Triangle::Triangle(const Vector3f & v0, const Vector3f & v1, const Vector3f & v2)
{
	vertex_[0] = v0;
	vertex_[1] = v1;
	vertex_[2] = v2;
}

/**
 * reference: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm   
 */
bool cgray::rt::Triangle::intersect(const Ray & ray, IntersectInfo & info)
{
	Vector3f e1_0 = vertex_[1] - vertex_[0];
	Vector3f e2_0 = vertex_[2] - vertex_[0];

	Vector3f p = ray.direction().cross(e2_0);
	float det = e1_0.dot(p);
	if (det > -M_EPSILON && det < M_EPSILON) 
		return false;

	float inv_det = 1.0f / det;
	Vector3f t = ray.origin() - vertex_[0];
	float u = t.dot(p) * inv_det;
	if (u < 0.0f || u > 1.0f)
		return false;

	Vector3f q = t.cross(e1_0);
	float v = ray.direction().dot(q) * inv_det;
	if (v < 0.0f || u + v  > 1.0f) 
		return false;

	float dist = e2_0.dot(q) * inv_det;

	if (dist > M_EPSILON) { //ray intersection
		// set intersection info
		info.hit_point = ray.origin() + dist * ray.direction();
		info.hit_shape = std::make_shared<Triangle>(*this);
		info.is_hit = true;
		info.dist = dist;
		info.normal = (e1_0.cross(e2_0)).normalized();
		info.ray = ray;

		return true;
	}

	return false;
}

Eigen::Vector3f cgray::rt::Triangle::getNormal(const Vector3f& pos) const
{
	return (vertex_[1] - vertex_[0]).cross(pos - vertex_[0]).normalized();
}

bool cgray::rt::Triangle::getAABB(AABB& box) const
{
	// TODO
	return true;
}
