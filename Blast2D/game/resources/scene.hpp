#ifndef BLAST2D_SCENE_HPP
#define BLAST2D_SCENE_HPP

#include <vector>
#include <string>

#include <core/resource/resource_manager.hpp>

namespace Blast2D{

    struct SceneComponent{
        std::string component;
        std::string value;
    };

    struct SceneItem {
        std::vector<SceneComponent> components;
    };

    struct Scene {
        std::vector<SceneItem> items;
        bool loadOnStart = false;
        std::string loadWith;
    };

    BLAST_RESOURCE(Scene)
}

#endif //BLAST2D_SCENE_HPP
