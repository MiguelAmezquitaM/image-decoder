extern "C" {
#include <libpng/png.h>
}

#include <image-decoder.hpp>
#include <cmath>
#include <stdexcept>

namespace imd {

	Image::Image(uint32_t w, uint32_t h)
		: width{ w }, height{ h }, data{ std::make_unique<uint32_t[]>(h * w) } {}

	Image::Image(uint32_t w, uint32_t h, uint32_t* p)
		: width{ w }, height{ h }, data{ p } {}

	Image::~Image() {}

	Image& read_image_path(const char* img_path) {
		png_image image{};

		image.version = PNG_IMAGE_VERSION;

		if (png_image_begin_read_from_file(&image, img_path)) {
			image.format = PNG_FORMAT_BGRA;

			auto buffer = std::make_unique<uint32_t[]>(PNG_IMAGE_SIZE(image));

			if (buffer and png_image_finish_read(&image, nullptr, buffer.get(), 0, nullptr)) {
				return *new Image{ image.width, image.height, buffer.release() };
			}
		}
		throw std::logic_error("No such file or directory");
	}

	void resize_image(const Image& image, Image& result) {
		uint32_t* image_it{ nullptr }, * result_it{ nullptr };
		double dw = double(image.width) / result.width;
		double dh = double(image.height) / result.height;

		double i, j; int k;
		for (i = 0.0, k = 0; round(i) < image.height; i += dh, k++) {
			image_it = &image.data[image.width * uint32_t(i)];
			result_it = &result.data[result.width * uint32_t(k)];
			for (j = 0.0; round(j) < image.width; j += dw) {
				*result_it = image_it[uint32_t(j)];
				++result_it;
			}
		}
	}

} // namespace imd
