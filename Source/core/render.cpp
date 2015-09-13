#include "render.hpp"
#include "color.hpp"
#include "..\tools\julia.hpp"

namespace cgray {
	rt::Render::Render(std::shared_ptr<Camera> camera)
	{
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
	}

}
