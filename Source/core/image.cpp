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
			data_[y][x].red = color.r * 255;
			data_[y][x].green = color.g * 255;
			data_[y][x].blue = color.b * 255;
		}




	}
}
