#ifndef BLAST2D_CAMERA_HPP
#define BLAST2D_CAMERA_HPP

#include <core/math/vector3.hpp>
#include <core/math/vector2.hpp>
#include <core/ecs/entity_manager.hpp>

namespace Blast2D{

    struct Camera {
        Vector3 position;
        Vector2 zoom;
        unsigned int moveSpeed = 20;
        int state;
    };

    BLAST_COMPONENT(Camera);
}

#endif
