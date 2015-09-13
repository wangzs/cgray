/*!
 * \file image.hpp
 * \date 2015/09/13 15:41
 *
 * \author wangzs
 * Contact: wang.zhenshui@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
#pragma once

#include "color.hpp"

#include <png.hpp>
#include <string>

namespace cgray {
	namespace core {
		class Image {
		public:
			Image();

			Image(int width, int height);

			inline int width() const {
				return data_.get_width();
			}
			inline int height() const {
				return data_.get_height();
			}

			inline void flushToFile(const std::string& file_name) {
				data_.write(file_name.c_str());
			}

			void setColor(int x, int y, const Color3f& color);

		private:
			png::image< png::rgb_pixel> data_;
		};
	}
}

