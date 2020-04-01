#include <iostream>
#include <logging/easylogging++.h>
#include <logging/chronometer.hpp>
#include <ecs/entity_manager.hpp>

INITIALIZE_EASYLOGGINGPP

struct Test {
	int test;
};

struct Position {
	int value;
};

int main() {
	LOG(INFO) << "Starting engine";

	Blast2D::EntityManager entityManager;
	
	entityManager.registerComponent<Test>("Test");	
	entityManager.registerComponent<Position>("Position");

	auto entity = entityManager.createEntity();

	auto chrono = Blast2D::Chronometer::create();

	chrono.lap();

	chrono.lap();

	chrono.lap();

	chrono.end();

	entityManager.assign<Test>(entity,{ 20 });

	auto test = entityManager.get<Test>(entity);	   

	LOG(INFO) << test.test;
	

	LOG(INFO) << entity;
	
}
