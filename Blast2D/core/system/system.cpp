#include "system.hpp"

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

