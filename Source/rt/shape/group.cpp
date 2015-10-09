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

void cgray::rt::SimpleGroup::setMaterial(std::shared_ptr<MaterialBase> material)
{
	//TODO
	return;
}

std::shared_ptr<cgray::rt::MaterialBase> cgray::rt::SimpleGroup::material() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

void cgray::rt::SimpleGroup::addLight(std::shared_ptr<cgray::rt::Light> light)
{
	lights_.push_back(light);
}

const std::vector<std::shared_ptr<cgray::rt::Light>>& cgray::rt::SimpleGroup::lights() const
{
	return lights_;
}
