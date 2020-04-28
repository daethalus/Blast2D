#ifndef BLAST2D_CAMERA_SYSTEM_HPP
#define BLAST2D_CAMERA_SYSTEM_HPP

#include <core/system/system.hpp>

namespace Blast2D{

    class CameraSystem : public System {
    public:
        void onUpdate() override;
    };

    BLAST_SYSTEM(CameraSystem);
}
#endif
