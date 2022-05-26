
namespace imd {

    struct Image;

    Image read_image_path(const char* path);

    void resize_image(const Image& image, Image& result);

} // namespace imd
