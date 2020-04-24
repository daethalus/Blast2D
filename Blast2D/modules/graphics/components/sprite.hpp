#ifndef BLAST2D_SPRITE_HPP
#define BLAST2D_SPRITE_HPP

#include <core/math/rect.hpp>
#include <string>

namespace Blast2D {
    struct Sprite {
        Rect offset;
        Sprite(Rect _offset) : offset(_offset){
        }
    };
}



#endif
