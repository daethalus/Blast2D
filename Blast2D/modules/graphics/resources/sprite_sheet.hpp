#ifndef BLAST2D_SPRITE_SHEET_HPP
#define BLAST2D_SPRITE_SHEET_HPP

#include <vector>
#include <modules/graphics/components/sprite.hpp>
#include <modules/graphics/libs/shelf-pack.hpp>
#include <modules/graphics/resources/image.hpp>
#include <core/math/vector2.hpp>

namespace Blast2D{
    struct BinImg {
        mapbox::Bin* bin;
        const Image& img;
        BinImg(mapbox::Bin* _bin, const Image& _img): bin(_bin), img(_img) {}
    };

    struct SpriteSheetBuilder{
        mapbox::ShelfPack shelfPack;
        std::vector<BinImg>images;

        SpriteSheetBuilder() {
            mapbox::ShelfPack::ShelfPackOptions options;
            options.autoResize = true;
            shelfPack = mapbox::ShelfPack(32,32,options);
        }
    };
    struct SpriteSheet {
        unsigned int textureId;
        std::vector<Sprite> sprites;
        unsigned int width;
        unsigned int height;
    };
}

#endif
