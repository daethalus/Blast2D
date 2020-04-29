#include "game.hpp"

#include <core/ecs/entity_manager.hpp>
#include <core/components/application.hpp>
#include <core/system/system.hpp>
#include <modules/graphics/components/window.hpp>
#include <core/logging/easylogging++.h>

INITIALIZE_EASYLOGGINGPP

void Blast2D::Game::run() {

    entityManager.create(WindowProperties{true});
    entityManager.create(Blast2D::Application{true});

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
