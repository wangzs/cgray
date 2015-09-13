#if 1

#include "tests/render_test.hpp"

int main() {
	//cgray::test::normlizeTest();

	cgray::test::juliaTest();

	return 0;
}

#else
#include <iostream>
#include <ostream>
#include <png.hpp>

class pixel_generator : public png::generator< png::gray_pixel_1, pixel_generator >
{
public:
	pixel_generator(size_t width, size_t height)
		: png::generator< png::gray_pixel_1, pixel_generator >(width, height),
		m_row(width)
	{
		for (size_t i = 0; i < m_row.size(); ++i)
		{
			m_row[i] = i > m_row.size() / 2 ? 1 : 0;
		}
	}

	png::byte* get_next_row(size_t /*pos*/)
	{
		size_t i = std::rand() % m_row.size();
		size_t j = std::rand() % m_row.size();
		png::gray_pixel_1 t = m_row[i];
		m_row[i] = m_row[j];
		m_row[j] = t;
		return reinterpret_cast<png::byte*>(row_traits::get_data(m_row));
	}

private:
	typedef png::packed_pixel_row< png::gray_pixel_1 > row;
	typedef png::row_traits< row > row_traits;
	row m_row;
};


template< typename pixel >
void
generate_image(png::image< pixel >& image)
{
	typedef png::pixel_traits< pixel > traits;
	size_t colors = 1 << traits::get_bit_depth();
	size_t size = colors / 2;
	image.resize(size, size);

	png::palette palette(colors);
	for (size_t c = 0; c < colors; ++c)
	{
		palette[c] = png::color(c * 255 / colors,
			(colors - c - 1) * 255 / colors,
			c * 255 / colors);
	}
	image.set_palette(palette);
	for (size_t j = 0; j < image.get_height(); ++j)
	{
		for (size_t i = 0; i < image.get_width(); ++i)
		{
			image.set_pixel(i, j, i + j);
		}
	}
}


int main() try
{
	png::image< png::gray_pixel_16 > image(256, 256);
	for (size_t y = 0; y < image.get_height(); ++y)
	{
		for (size_t x = 0; x < image.get_width(); ++x)
		{
			png::gray_pixel_16 pix = x*y;
			image[y][x] = pix;
		}
	}
	image.write("png_result/gray_16.png");


	//////////////////////////////////////////////////////////////////////
	size_t const width = 32;
	size_t const height = 512;
	std::ofstream file("png_result/generated.png", std::ios::binary);
	pixel_generator generator(width, height);
	generator.write(file);


	/////////////////////////////////////////////////////////////////////
	png::image< png::index_pixel_1 > image1;
	generate_image(image1);
	image1.write("png_result/palette1.png");

	png::image< png::index_pixel_2 > image2;
	generate_image(image2);
	image2.write("png_result/palette2.png");

	png::image< png::index_pixel_4 > image4;
	generate_image(image4);
	image4.write("png_result/palette4.png");

	png::image< png::index_pixel > image8;
	generate_image(image8);
	image8.write("png_result/palette8.png");

	png::image< png::index_pixel > image8_tRNS;
	generate_image(image8_tRNS);
	png::tRNS trns(256);
	for (size_t i = 0; i < trns.size(); ++i)
	{
		trns[i] = i;
	}
	image8_tRNS.set_tRNS(trns);
	image8_tRNS.write("png_result/palette8_tRNS.png");
}
catch (std::exception const& error)
{
	std::cerr << "write_gray_16: " << error.what() << std::endl;
	return EXIT_FAILURE;
}

#endif