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


namespace Blast2D {

//    class SceneLoader : public ResourceLoader{
//    public:
//        void loadFile(const ResourceConfigFile &&configFile) override {
//            LOG(INFO) << "module: " << configFile.module << " file: " << configFile.path << " value from file: " << configFile.content;
//        }
//    };

//    BLAST_RESOURCE_LOADER(SceneLoader, scene)

    class Loader {
    public:
        static void load() {

        }
    };
}

#endif
