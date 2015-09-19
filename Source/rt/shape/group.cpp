#include "group.hpp"

void cgray::rt::SimpleGroup::add(std::shared_ptr<Shape> object)
{
	groups_.push_back(object);
}

void cgray::rt::SimpleGroup::rebuildIndex()
{
	// TODO
}

bool cgray::rt::SimpleGroup::intersect(const Ray & ray, IntersectInfo & info)
{
	IntersectInfo tmp;
	for (auto obj : groups_) {
		if (obj->intersect(ray, tmp) == true) {
			if (tmp.dist < info.dist) {
				info = tmp;
			}
		}
	}

	if (info.is_hit == true)
		return true;
	return false;
}

Vector3f cgray::rt::SimpleGroup::getNormal(const Vector3f & pos) const
{
	// TODO
	return Vector3f();
}

bool cgray::rt::SimpleGroup::getAABB(AABB & box) const
{
	// TODO
	return false;
}
