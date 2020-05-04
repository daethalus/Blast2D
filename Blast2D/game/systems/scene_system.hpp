#ifndef BLAST2D_SCENE_SYSTEM_HPP
#define BLAST2D_SCENE_SYSTEM_HPP

#include <core/system/system.hpp>
#include <game/resources/scene.hpp>

namespace Blast2D{
    class SceneSystem : public System {
    public:
        void onCreate() override;

        void onUpdate() override;

        void loadScene(const Scene& scene);
    };

    BLAST_SYSTEM(SceneSystem);
}




#endif
