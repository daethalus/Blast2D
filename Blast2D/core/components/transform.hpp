#ifndef BLAST2D_TRANSFORM_HPP
#define BLAST2D_TRANSFORM_HPP

#include <core/math/vector3.hpp>
#include <core/math/vector2.hpp>

#include <core/ecs/entity_manager.hpp>

namespace Blast2D{

    struct Transform {
        Vector3 position;
        Vector2 size;
        int rotation;
    };
    BLAST_COMPONENT(Transform);
}

#endif
