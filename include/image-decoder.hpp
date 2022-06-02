#include <cstdint>
#include <memory>

namespace imd {

	struct Image {

		Image(uint32_t w, uint32_t h);

		Image(uint32_t w, uint32_t h, uint32_t* p);

		~Image();

		uint32_t width, height;
		std::unique_ptr<uint32_t[]> data;
	};

	Image& read_image_path(const char* path);

	void resize_image(const Image& image, Image& result);

} // namespace imd
