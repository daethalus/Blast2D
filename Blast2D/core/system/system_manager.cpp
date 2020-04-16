#include "system_manager.hpp"

void Blast2D::SystemManager::update(EntityManager& entityManager) {
	for (auto& systemInfo : systems) {
		systemInfo.second.system->onUpdate(entityManager);
	}
}