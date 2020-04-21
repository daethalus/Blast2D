#include "system.hpp"

void Blast2D::SystemManager::create() {
	for (auto& systemInfo : systems) {
		systemInfo.second.system->onCreate();
	}
}

void Blast2D::SystemManager::update() {
	for (auto& systemInfo : systems) {
		systemInfo.second.system->onUpdate();
	}
}

