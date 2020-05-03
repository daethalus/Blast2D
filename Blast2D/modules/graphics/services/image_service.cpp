#include "image_service.hpp"
#include "texture_service.hpp"
#include <modules/graphics/libs/stb_image.h>
#include <core/logging/easylogging++.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <modules/graphics/libs/stb_image_write.h>
#include <assert.h>

std::shared_ptr<Blast2D::Image> Blast2D::ImageService::loadImage(std::string path) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	assert(data != nullptr);
    return std::make_shared<Image>(width, height, nrChannels, data, path);
}

void Blast2D::ImageService::pack(SpriteSheetBuilder &spriteSheetBuilder, std::shared_ptr<Image> image) {
    auto bin = spriteSheetBuilder.shelfPack.packOne(-1, image->width, image->height);
    spriteSheetBuilder.images.emplace_back(bin, image);
}

void Blast2D::ImageService::setPixelColor(unsigned int x, unsigned int y, Blast2D::Image &image,
                                          const Blast2D::Color &color) {
    int posPixel = (image.nrChannels * (y * image.width + x));
    if (image.nrChannels > 0) {
        image.data[posPixel] = color.red;
    }
    if (image.nrChannels > 1) {
        image.data[posPixel + 1] = color.green;
    }
    if (image.nrChannels > 2) {
        image.data[posPixel + 2] = color.blue;
    }
    if (image.nrChannels > 3) {
        image.data[posPixel + 3] = color.alpha;
    }
}

Blast2D::Color Blast2D::ImageService::getPixelColor(unsigned int x, unsigned int y, const Blast2D::Image &image) {
    auto color = Color{255,255,255,255};
    int posPixel = image.nrChannels * (y * image.width + x);
    if (image.nrChannels > 0) {
        color.red = image.data[posPixel];
    }
    if (image.nrChannels > 1) {
        color.green = image.data[posPixel + 1];
    }
    if (image.nrChannels > 2) {
        color.blue = image.data[posPixel + 2];
    }
    if (image.nrChannels > 3) {
        color.alpha = image.data[posPixel + 3];
    }
    return color;
}

void Blast2D::ImageService::saveFileFromImage(std::string path, const Blast2D::Image &image) {
    stbi_write_png(path.c_str(), image.width, image.height, image.nrChannels, image.data, image.width * image.nrChannels);
}

void Blast2D::ImageService::updateSpriteSheet(Blast2D::SpriteSheet &spriteSheet,
                                              const Blast2D::SpriteSheetBuilder &spriteSheetBuilder) {

    Image image(spriteSheetBuilder.shelfPack.width(),spriteSheetBuilder.shelfPack.height(),4, nullptr, spriteSheetBuilder.id + ".png");
    spriteSheet.width = image.width;
    spriteSheet.height = image.height;
    for (const auto& binImg : spriteSheetBuilder.images){
        for (unsigned int sourceY = 0; sourceY < binImg.img->height; ++sourceY) {
            for (unsigned int sourceX = 0; sourceX < binImg.img->width; ++sourceX) {
                this->setPixelColor(sourceX + binImg.bin->x, sourceY + + binImg.bin->y, image,
                                    this->getPixelColor(sourceX, sourceY, *binImg.img));
            }
        }
        spriteSheet.sprites.emplace_back(Rect{binImg.bin->x,binImg.bin->y,binImg.bin->w,binImg.bin->h});
    }
    this->saveFileFromImage(image.path, image);
    auto& textureService = Blast2D::TextureService::getInstance();
    auto texture = textureService.loadTexture(std::make_shared<Image>(image));
    spriteSheet.textureId = texture.ID;
}
