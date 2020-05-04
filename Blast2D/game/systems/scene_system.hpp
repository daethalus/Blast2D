#ifndef BLAST2D_SCENE_SYSTEM_HPP
#define BLAST2D_SCENE_SYSTEM_HPP

#include <core/system/system.hpp>

namespace Blast2D{
    class SceneSystem : public System {
    public:
        void onCreate() override;

        void onUpdate() override;
    };


    BLAST_SYSTEM(SceneSystem);
}




#endif
