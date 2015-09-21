#pragma once
#include "shape\aabb.hpp"
#include "shape\triangle.hpp"
#include "shape\baseshape.hpp"
#include <memory>
#include <vector>

namespace cgray {
	namespace rt {
		class KdNode : public Shape {
		public:
			AABB bbox;
			std::shared_ptr<KdNode> left;
			std::shared_ptr<KdNode> right;
			std::vector<std::shared_ptr<Triangle>> triangles;

			static std::shared_ptr<KdNode> build(std::vector<std::shared_ptr<Triangle>> trias, int depth);

			bool intersect(const Ray& ray, IntersectInfo& info) override;

			virtual Vector3f getNormal(const Vector3f& pos) const override;

			virtual bool getAABB(AABB& box) const override;

		};
	}
}
