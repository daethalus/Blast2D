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

//#include <modules/graphics/system/window_system.hpp>
//#include <modules/graphics/components/window.hpp>

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

	//sm.add<Blast2D::WindowSystem>("Blast2D_WindowSystem");
	

	LOG(INFO) << "Starting engine";
	Blast2D::EntityManager &entityManager = Blast2D::EntityManager::getInstance();

	entityManager.createComponent<Position>();
	entityManager.createComponent<Velocity>();
//	entityManager.createComponent<Blast2D::WindowProperties>();
//	entityManager.createComponent<Blast2D::WindowHandler>();
    entityManager.createComponent<Blast2D::Application>();
	
	auto containerIndex1 = entityManager.runtimeComponent<Container>();
	auto containerIndex2 = entityManager.runtimeComponent<Container>();

//	entityManager.create(
//		Blast2D::WindowProperties{true}
//	);

	entityManager.create(
		Blast2D::Application{ true }
	);

	auto chrono = Blast2D::Chronometer::create();

	for (int x = 99; x >= 0; --x) {
		entityManager.create(Position{ x }, Velocity{ x * 2 });
	}

	chrono.lap();
	long long value = 0;


	entityManager.forEach<Position>([&value](auto& entity, auto& position) {
	    LOG(INFO) << position.x;
	});
	
	LOG(INFO) << value;

	value = 0;

	chrono.lap();

	auto lambda = [&entityManager, &value](auto entity){
		auto& position = entityManager.get<Position>(entity);
		value++;
	};

	std::vector<Blast2D::Index> comps;

	comps.push_back(Blast2D::TypeInfo<Position>::index());
	comps.push_back(containerIndex2);

	entityManager.runtimeView(lambda, comps);

	LOG(INFO) << value;

	chrono.end();

	sm.create();
	auto& application = entityManager.last<Blast2D::Application>();
	do {		
		sm.update();		
	} while (application.running);		
}
