#include "scene_system.hpp"
#include <core/resource/resource_manager.hpp>
#include <core/logging/easylogging++.h>

void Blast2D::SceneSystem::onCreate() {
    for (const auto& scene: resourceManager.loadAll<Scene>()) {
        if (scene.second.loadOnStart){
            this->loadScene(scene.second);
        }
    }
}


void Blast2D::SceneSystem::onUpdate() {

}

void Blast2D::SceneSystem::loadScene(const Blast2D::Scene &scene) {

}


