#ifndef BLAST2D_SCENE_LOADER_HPP
#define BLAST2D_SCENE_LOADER_HPP

#include <core/resource/resource_manager.hpp>

namespace Blast2D{

    class SceneLoader : public ResourceLoader {
    public:
        void loadFile(const ResourceConfigFile &&configFile) override;
    };

    BLAST_RESOURCE_LOADER(SceneLoader, scene)
}

#endif
