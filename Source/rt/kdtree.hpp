#pragma once
#include "shape\aabb.hpp"
#include "shape\triangle.hpp"

#include <memory>
#include <vector>

namespace cgray {
	namespace rt {
		class KdNode {
		public:
			AABB bbox;
			std::shared_ptr<KdNode> left;
			std::shared_ptr<KdNode> right;
			std::vector<std::shared_ptr<Triangle>> triangles;

			std::shared_ptr<KdNode> build(std::vector<std::shared_ptr<Triangle>> trias, int depth) const;

			bool intersect(const Ray& ray, IntersectInfo& info);
		};
	}
}
