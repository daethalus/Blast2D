#include "camera_system.hpp"

#include <core/input/input.hpp>

void Blast2D::CameraSystem::onUpdate() {
    if (input.isKeyHolding(Keys::A)){
        LOG(INFO) << "Key A holding";
    }
}
