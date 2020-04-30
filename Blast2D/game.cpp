#include "game.hpp"

#include <core/components/application.hpp>
#include <core/ecs/entity_manager.hpp>
#include <core/resource/resource_manager.hpp>
#include <core/system/system.hpp>
#include <modules/graphics/components/window.hpp>
#include <core/logging/easylogging++.h>

#include <game/loader.hpp>

void Blast2D::Game::run() {
    LOG(INFO) << "Blast2D Initialization";

    resourceManager.load();

    Loader::load();

    entityManager.create(WindowProperties{true});
    entityManager.create(Application{true});

    systemManager.preInit();
    systemManager.onCreate();

    this->loop();
}

void Blast2D::Game::loop() {
    auto &application = entityManager.last<Application>();
    do {
        systemManager.onUpdate();
    } while (application.running);
    systemManager.onDestroy();
}
