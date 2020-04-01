#include <iostream>
#include <logging/easylogging++.h>
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

	entityManager.addComponentData<Test>(entity, 1 );
	//auto& test, auto& position
	entityManager.view<Test, Position>().each([]() {
		LOG(INFO) << "each";
	});
	
	//entityManager.each([](Test &test, Position &position) {
	//	LOG(INFO) << test.test;
	//});
	

	LOG(INFO) << entity;
	
}
