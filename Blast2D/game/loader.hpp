#ifndef BLAST2D_LOADER_HPP
#define BLAST2D_LOADER_HPP

#include <core/logging/easylogging++.h>
#include <core/ecs/entity_manager.hpp>
#include <memory>

#include <core/resource/resource_loader.hpp>
#include <core/resource/file_utils.hpp>
#include <core/libs/json.hpp>


#include <game/loaders/scene_loader.hpp>
#include <game/systems/scene_system.hpp>
#include <modules/graphics/components/sprite.hpp>


namespace Blast2D {

    class Loader {
    public:
        static void load() {
            auto entity = entityManager.create();
            //entityManager.resource<Sprite>(entity, "game-test:test.png");

        }
    };
}

#endif
