#ifndef BLAST2D_IMAGE_SERVICE_HPP
#define BLAST2D_IMAGE_SERVICE_HPP

#include <memory>

#include <modules/graphics/resources/image.hpp>
#include <modules/graphics/resources/sprite_sheet.hpp>
#include <modules/graphics/resources/color.hpp>

namespace Blast2D{
    class ImageService {
    private:
        ImageService() {}
    public:
        ImageService(ImageService const&) = delete;
        ImageService& operator=(ImageService const&) = delete;
        static ImageService& getInstance() {
            static ImageService imageService;
            return imageService;
        }
        void saveFileFromImage(std::string path, const Image& image);
        std::shared_ptr<Image> loadImage(std::string path);
        void pack(SpriteSheetBuilder &spriteSheetBuilder, const Image& image);
        std::shared_ptr<SpriteSheet> buildSpriteSheet(const SpriteSheetBuilder &spriteSheetBuilder);
        void setPixelColor(unsigned int x, unsigned int y, Image& image, const Color& color);
        Color getPixelColor(unsigned int x, unsigned int y, const Blast2D::Image &image);
    };

    static ImageService& imageService = Blast2D::ImageService::getInstance();
}

#endif
