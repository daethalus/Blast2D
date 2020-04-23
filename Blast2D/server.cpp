#include <iostream>

#include <core/logging/easylogging++.h>
#include <core/ecs/entity_manager.hpp>

INITIALIZE_EASYLOGGINGPP

struct Server {

};

BLAST_COMPONENT(Server);

int main() {
    LOG(INFO) << "server starting";
    Blast2D::EntityManager &em = Blast2D::EntityManager::getInstance();
    auto entity = em.create(Server{});
    LOG(INFO) << " entity created : " << entity;

}