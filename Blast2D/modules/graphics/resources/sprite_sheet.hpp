#ifndef BLAST2D_SPRITE_SHEET_HPP
#define BLAST2D_SPRITE_SHEET_HPP

#include <vector>
#include <modules/graphics/libs/shelf-pack.hpp>
#include <modules/graphics/resources/image.hpp>
#include <core/math/vector2.hpp>
#include <core/resource/resource_manager.hpp>
#include <memory>

namespace Blast2D {

    struct Sprite;

    struct BinImg {
        mapbox::Bin* bin;
        std::shared_ptr<Image> img;
        BinImg(mapbox::Bin* _bin, std::shared_ptr<Image> _img): bin(_bin), img(_img) {}
    };

    struct SpriteSheetBuilder{
        std::string id;
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
        std::vector<std::string> sprites;
        unsigned int width;
        unsigned int height;
    };

    BLAST_RESOURCE(SpriteSheet)
}

#endif
