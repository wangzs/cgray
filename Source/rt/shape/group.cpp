#include "group.hpp"

void cgray::rt::SimpleGroup::add(std::shared_ptr<Shape> object)
{
	groups_.push_back(object);
	AABB tmp;
	object->getAABB(tmp);
	bbox_ += tmp;
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
	return Vector3f();
}

bool cgray::rt::SimpleGroup::getAABB(AABB & box) const
{
	box = bbox_;
	return true;
}
