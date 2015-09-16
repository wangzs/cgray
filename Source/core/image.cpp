#include "image.hpp"

namespace cgray {
	namespace core {
		Image::Image()
			:data_(800, 600)
		{
		}
		Image::Image(int width, int height)
			:data_(width, height)
		{
		}

		void Image::setColor(int x, int y, const Color3f & color)
		{
			data_[y][x].red = (png::byte)(color.r * 255);
			data_[y][x].green = (png::byte)(color.g * 255);
			data_[y][x].blue = (png::byte)(color.b * 255);
		}




	}
}
