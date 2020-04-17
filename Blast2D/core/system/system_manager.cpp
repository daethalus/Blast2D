#include "system_manager.hpp"
#include "system_manager.hpp"


void Blast2D::SystemManager::create(EntityManager& entityManager) {
	for (auto& systemInfo : systems) {
		systemInfo.second.system->onCreate(entityManager);
	}
}

void Blast2D::SystemManager::update(EntityManager& entityManager) {
	for (auto& systemInfo : systems) {
		systemInfo.second.system->onUpdate(entityManager);
	}
}

