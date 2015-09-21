#pragma once
#include "baseshape.hpp"
#include "aabb.hpp"

#include <vector>
#include <memory>

namespace cgray {
	namespace rt {
		class Group : public Shape {
		public:
			virtual void add(std::shared_ptr<Shape> object) = 0;

			virtual void rebuildIndex() = 0;

		};

		class SimpleGroup : public Group {
		public:
			virtual void add(std::shared_ptr<Shape> object) override;

			virtual void rebuildIndex() override;

			virtual bool intersect(const Ray& ray, IntersectInfo& info) override;

			virtual Vector3f getNormal(const Vector3f& pos) const override;

			virtual bool getAABB(AABB& box) const override;

		private:
			std::vector<std::shared_ptr<Shape>> groups_;
			AABB bbox_;

		};
	}
}
