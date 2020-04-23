#ifndef BLAST2D_SPRITE_HPP
#define BLAST2D_SPRITE_HPP

#include <core/math/rect.hpp>
#include <string>

namespace Blast2D {
    struct Sprite {
        std::string id;
        Rect offset;
    };
}



#endif
