#pragma once
#include "triangle.hpp"
#include "aabb.hpp"

#include <vector>

namespace cgray {
	namespace rt {
		class Mesh : public Shape{
		public:
			Mesh(const char* obj_name, const char* path);

			inline std::vector<std::shared_ptr<Triangle>>& getMesh() {
				return triangles_;
			}

			virtual bool intersect(const Ray& ray, IntersectInfo& info) override;

			virtual Vector3f getNormal(const Vector3f& pos) const override;

			virtual bool getAABB(AABB& box) const override;

		private:
			void loadObj(const char* obj_name, const char* path);

		private:
			std::vector<std::shared_ptr<Triangle>> triangles_;
			AABB bbox_;
		};
	}
}