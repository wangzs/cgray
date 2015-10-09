#pragma once
#include "baseshape.hpp"
#include "aabb.hpp"
#include "../material/materialbase.hpp"
#include "../light/light.hpp"

#include <vector>
#include <memory>

namespace cgray {
	namespace rt {
		class Group : public Shape {
		public:
			virtual void add(std::shared_ptr<Shape> object) = 0;

			virtual void rebuildIndex() = 0;

			virtual void addLight(std::shared_ptr<Light> light) = 0;
			virtual const std::vector<std::shared_ptr<Light>>& lights() const=0;
		};

		class SimpleGroup : public Group {
		public:
			virtual void add(std::shared_ptr<Shape> object) override;

			virtual void rebuildIndex() override;

			virtual bool intersect(const Ray& ray, IntersectInfo& info) override;

			virtual Vector3f getNormal(const Vector3f& pos) const override;

			virtual bool getAABB(AABB& box) const override;

			virtual void setMaterial(std::shared_ptr<MaterialBase> material) override;

			virtual std::shared_ptr<MaterialBase> material() const override;

			void addLight(std::shared_ptr<Light> light);
			const std::vector<std::shared_ptr<Light>>& lights() const;

		private:
			std::vector<std::shared_ptr<Shape>> groups_;
			std::vector < std::shared_ptr<Light>> lights_;
			AABB bbox_;

		};
	}
}
