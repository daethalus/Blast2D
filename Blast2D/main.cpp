#include <iostream>
#include <functional>
#include <thread>
#include <queue>
#include <chrono>
#include <thread>

#include <core/logging/easylogging++.h>
#include <core/logging/chronometer.hpp>
#include <core/ecs/entity_manager.hpp>
#include <core/ecs/sparse_set.hpp>
#include <core/ecs/storage.hpp>
#include <core/components/application.hpp>

#include <core/system/thread_pool.hpp>
#include <core/system/system.hpp>
#include <core/system/system_manager.hpp>

#include <modules/graphics/system/window_system.hpp>
#include <modules/graphics/components/window.hpp>

INITIALIZE_EASYLOGGINGPP

struct Position {
	int x;
};

struct Velocity {
	int y;
};

struct Container {
	int z;
};


int main() {

	Blast2D::SystemManager sm;

	sm.add<Blast2D::WindowSystem>("Blast2D_WindowSystem");
	

	LOG(INFO) << "Starting engine";
	Blast2D::EntityManager &entityManager = Blast2D::EntityManager::getInstance();
	entityManager.createComponent<Blast2D::WindowProperties>();
	entityManager.createComponent<Blast2D::WindowHandler>();
    entityManager.createComponent<Blast2D::Application>();

	entityManager.create(
		Blast2D::WindowProperties{true}
	);

	entityManager.create(
		Blast2D::Application{ true }
	);

	sm.create();
	auto& application = entityManager.last<Blast2D::Application>();
	do {		
		sm.update();		
	} while (application.running);		
}
