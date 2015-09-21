#include "kdtree.hpp"

static const int KDTREE_DEPTH = 10;


std::shared_ptr<cgray::rt::KdNode> cgray::rt::KdNode::build(std::vector<std::shared_ptr<Triangle>> trias, int depth) const
{
	std::shared_ptr<KdNode> root(new KdNode());
	root->triangles = trias;
	root->left = nullptr;
	root->right = nullptr;

	if (trias.size() == 0)
		return root;

	trias[0]->getAABB(root->bbox);

	if (trias.size() == 1) {
		return root;
	}

	AABB tmp;
	for (auto iter : trias) {
		(*iter).getAABB(tmp);
		root->bbox += tmp;
	}
	// kd-tree的深度超多10，不再划分
	if (depth > KDTREE_DEPTH) {
		return root;
	}

	Vector3f midpoint(0.0f,0.0f,0.0f);
	for (auto iter : trias) {
		midpoint = midpoint + (iter->getMidPoint() / trias.size());
	}

	std::vector<std::shared_ptr<Triangle>> left_triangles;
	std::vector<std::shared_ptr<Triangle>> right_triangles;
	AxisType axis = root->bbox.getLongestAxis();
	for (auto iter : trias) {
		switch (axis)
		{
		case cgray::rt::AxisType::XAxis:
			midpoint[0] >= iter->getMidPoint()[0] ? left_triangles.push_back(iter) : right_triangles.push_back(iter);
			break;
		case cgray::rt::AxisType::YAxis:
			midpoint[1] >= iter->getMidPoint()[1] ? left_triangles.push_back(iter) : right_triangles.push_back(iter);
			break;
		case cgray::rt::AxisType::ZAxis:
			midpoint[2] >= iter->getMidPoint()[2] ? left_triangles.push_back(iter) : right_triangles.push_back(iter);
			break;
		default:
			break;
		}
	}

	root->left = build(left_triangles, depth + 1);
	root->right = build(right_triangles, depth + 1);

	return root;
}

bool cgray::rt::KdNode::intersect(const Ray & ray, IntersectInfo & info)
{
	IntersectInfo tmp;
	if (bbox.intersect(ray, tmp) == true) {
		if (left->triangles.size() > 0 || right->triangles.size() > 0) {
			bool left_hit = left->intersect(ray, info);
			bool right_hit = right->intersect(ray, info);
			return left_hit || right_hit;
		}

		for (auto iter : triangles) {
			if (iter->intersect(ray, tmp) == true) {
				if (tmp.dist < info.dist) {
					info = tmp;
				}
			}
		}
		if (info.is_hit == true) {
			return true;
		}
	}
	return false;
}
