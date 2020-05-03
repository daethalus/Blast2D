#include "system.hpp"

void Blast2D::SystemManager::preInit() {
    for (auto& systemInfo : systems) {
        systemInfo.second.system->preInit();
    }
}

void Blast2D::SystemManager::onCreate() {
	for (auto& systemInfo : systems) {
		systemInfo.second.system->onCreate();
	}
}

void Blast2D::SystemManager::onUpdate() {
	for (auto& updaters : updaters) {
		updaters.second.system->onUpdate();		
	}
}

void Blast2D::SystemManager::onRenderer() {
	for (auto& Renderer : renderers) {
		Renderer.second.system->onRenderer();
	}
}

void Blast2D::SystemManager::onDestroy() {
    for (auto& systemInfo : systems) {
        systemInfo.second.system->onDestroy();
    }
}

