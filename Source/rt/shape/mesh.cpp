#include "mesh.hpp"

#include <tiny_obj_loader.h>
#include <iostream>

cgray::rt::Mesh::Mesh(const char * obj_name, const char* path)
{
	loadObj(obj_name, path);
}

void cgray::rt::Mesh::loadObj(const char * obj_name, const char* mtl_basepath)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err = tinyobj::LoadObj(shapes, materials, obj_name, mtl_basepath);

	if (!err.empty()) {
		std::cerr << err << std::endl;
		return;
	}

	for (auto shape : shapes) {
		int trianlge_num = shape.mesh.indices.size() / 3;
		for (int i = 0; i < trianlge_num; i++) {
			int a_index = shape.mesh.indices[3 * i + 0];
			int b_index = shape.mesh.indices[3 * i + 1];
			int c_index = shape.mesh.indices[3 * i + 2];

			Vector3f a(
				shape.mesh.positions[3 * a_index + 0],
				shape.mesh.positions[3 * a_index + 1],
				shape.mesh.positions[3 * a_index + 2]);
			Vector3f b(
				shape.mesh.positions[3 * b_index + 0],
				shape.mesh.positions[3 * b_index + 1],
				shape.mesh.positions[3 * b_index + 2]);
			Vector3f c(
				shape.mesh.positions[3 * c_index + 0],
				shape.mesh.positions[3 * c_index + 1],
				shape.mesh.positions[3 * c_index + 2]);
			Triangle obj = Triangle(a, b, c);
			triangles_.push_back(std::make_shared<Triangle>(obj));

			AABB tmp;
			obj.getAABB(tmp);
			bbox_ += tmp;
		}
	}
}


std::shared_ptr<cgray::rt::MaterialBase> cgray::rt::Mesh::material() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

void cgray::rt::Mesh::setMaterial(std::shared_ptr<MaterialBase> material)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool cgray::rt::Mesh::intersect(const Ray& ray, IntersectInfo& info)
{
	IntersectInfo tmp;
	for (auto tria : triangles_) {
		if (tria->intersect(ray, tmp) == true) {
			if (tmp.dist < info.dist)
				info = tmp;
		}
	}
	if (info.is_hit) {
		return true;
	}
	return false;
}

Vector3f cgray::rt::Mesh::getNormal(const Vector3f& pos) const
{
	return Vector3f();
}

bool cgray::rt::Mesh::getAABB(AABB& box) const
{
	box = bbox_;
	return true;
}
