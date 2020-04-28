#include "camera_system.hpp"

#include <core/input/input.hpp>
#include <modules/graphics/components/camera.hpp>

void Blast2D::CameraSystem::onUpdate() {
    //TODO - remove this code and add in some test system or lua system.
    {
        if (input.isKeyHolding(Keys::A)){
            LOG(INFO) << "Key A holding";
        }
    }
    entityManager.forEach<Camera>([](auto entity, Camera&camera){

    });
}
