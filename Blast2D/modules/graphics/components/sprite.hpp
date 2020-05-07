#ifndef BLAST2D_SPRITE_HPP
#define BLAST2D_SPRITE_HPP

#include <core/math/rect.hpp>
#include <string>
#include <modules/graphics/resources/sprite_sheet.hpp>
#include <core/ecs/entity_manager.hpp>

namespace Blast2D {

    struct Sprite {
        Rect offset;
        SpriteSheet& spriteSheet;
        Sprite(Rect _offset, SpriteSheet& _spriteSheet) : offset(_offset), spriteSheet(_spriteSheet) {
        }
    };
    BLAST_COMPONENT(Sprite);
    BLAST_RESOURCE(Sprite);
}



#endif
