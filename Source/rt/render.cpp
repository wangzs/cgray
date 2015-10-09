#include "render.hpp"
#include "..\core\color.hpp"
#include "..\tools\julia.hpp"
#include "camera.hpp"

namespace cgray {
	rt::Render::Render(std::shared_ptr<Camera> camera, std::shared_ptr<Group> group)
	{
		camera_ = camera;
		group_ = group;
	}

	rt::Render::Render(std::shared_ptr<Camera> camera)
	{
		camera_ = camera;
	}

	void rt::Render::rendering(core::Image & output)
	{
	}

	void rt::Render::test_rendering0(core::Image & output)
	{
		for (int y = 0; y < output.height(); ++y) {
			for (int x = 0; x < output.width(); ++x) {
				core::Color3f color = tools::a1computeColor(x, y, output.width(), output.height());
				output.setColor(x, y, color);
			}
		}
	}

	void rt::Render::test_rendering1(core::Image & output)
	{
		for (int y = 0; y < output.height(); ++y) {
			for (int x = 0; x < output.width(); ++x) {
				Ray ray = camera_->generateRay(x, y);
				core::Color3f color = tools::a2computeColor(ray);
				output.setColor(x, y, color);
			}
		}
	}

	void rt::Render::test_rendering2(core::Image & output)
	{
		for (int y = 0; y < output.height(); ++y) {
			for (int x = 0; x < output.width(); ++x) {
				IntersectInfo info;
				Ray ray = camera_->generateRay(x, y);
				if (group_->intersect(ray, info)) {
					core::Color3f color(info.normal.dot(-ray.direction()));
					output.setColor(x, y, color);
				}
				else {
					output.setColor(x, y, core::Color3f::WHITE);
				}
			}
		}
	}

	void rt::Render::test_rendering3(core::Image & output, const core::Color3f & near_color, float near, const core::Color3f & far_color, float far)
	{
		float interval = far - near;
		for (int y = 0; y < output.height(); ++y) {
			for (int x = 0; x < output.width(); ++x) {
				IntersectInfo info;
				Ray ray = camera_->generateRay(x, y);
				if (group_->intersect(ray, info)) {
					float ratio = (info.dist - near) / interval;
					core::Color3f color(near_color * ratio + (1-ratio)*far_color);
					output.setColor(x, y, color);
				}
				else {
					output.setColor(x, y, core::Color3f::WHITE);
				}
			}
		}
	}

	void rt::Render::test_rendering4(core::Image & output)
	{
		for (int y = 0; y < output.height(); ++y) {
			for (int x = 0; x < output.width(); ++x) {
				IntersectInfo info;
				Ray ray = camera_->generateRay(x, y);
				if (group_->intersect(ray, info)) {
					core::Color3f color(info.normal.dot(-ray.direction()));
					output.setColor(x, y, color);
				}
				else {
					output.setColor(x, y, core::Color3f::WHITE);
				}
			}
		}
	}

	void rt::Render::test_rendering5(core::Image & output)
	{
		for (int y = 0; y < output.height(); ++y) {
			for (int x = 0; x < output.width(); ++x) {
				IntersectInfo info;
				Ray ray = camera_->generateRay(x, y);
				if (group_->intersect(ray, info)) {
					std::shared_ptr<rt::MaterialBase> material = info.hit_shape->material();
					core::Color3f color(0.0f);
					for (auto light : group_->lights()) {
						LightHit hit = light->getLightHit(info.hit_point);
						Vector3f reflect = hit.direction - 2 * info.normal * (hit.direction.dot(info.normal));
						color = color
							+ material->ambient_color() * light->getLightIntensity(hit)
							+ 0.5f * pow(std::max(-ray.direction().dot(reflect), 0.0f), 32) * material->specular_color() * light->getLightIntensity(hit)
							+ material->diffuse_color() * light->getLightIntensity(hit) * info.normal.dot(-hit.direction);
					}
					
					output.setColor(x, y, color);
				}
				else {
					output.setColor(x, y, core::Color3f::WHITE);
				}
			}
		}
	}



}
