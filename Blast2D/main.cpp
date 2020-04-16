#include <iostream>
#include <logging/easylogging++.h>
#include <logging/chronometer.hpp>
#include <ecs/entity_manager.hpp>
#include <ecs/sparse_set.hpp>
#include <ecs/storage.hpp>
#include <functional>
#include <thread>

#include <system/thread_pool.hpp>

#include <queue>

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

	LOG(INFO) << "Starting engine";
	Blast2D::EntityManager entityManager;
	entityManager.createComponent<Position>();
	entityManager.createComponent<Velocity>();	
	auto containerIndex1 = entityManager.runtimeComponent<Container>();
	auto containerIndex2 = entityManager.runtimeComponent<Container>();

	auto chrono = Blast2D::Chronometer::create();

	for (int x = 99; x >= 0; --x) {
		auto entity = entityManager.create();
		entityManager.set<Position>(entity, { x });
		//entityManager.set<Velocity>(entity, { x });		
		//entityManager.set<Container>(containerIndex1, entity, { 10 });
		entityManager.set<Container>(containerIndex2, entity, { 10 });
	}

	chrono.lap();
	long long value = 0;


	entityManager.forEach<Position>([&value](auto& position) {
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

	std::string aaa;
	std::cin >> aaa;
}
