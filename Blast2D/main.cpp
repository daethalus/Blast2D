#include <iostream>
#include <logging/easylogging++.h>
#include <logging/chronometer.hpp>
#include <ecs/entity_manager.hpp>
#include <ecs/sparse_set.hpp>
#include <ecs/storage.hpp>
#include <functional>

INITIALIZE_EASYLOGGINGPP


struct Position {
	int x;
};

struct Velocity {
	int y;
};

namespace ci {
	Blast2D::CompInfo position;
}




int main() {

	LOG(INFO) << "Starting engine";
	Blast2D::EntityManager entityManager;
	ci::position = entityManager.createComponent<Position>("Position");

	auto chrono = Blast2D::Chronometer::create();

	for (int x = 999999; x>= 0; --x) {
		auto entity = entityManager.create();
		entityManager.set<Position>(ci::position, entity, Position{ 10 });
	}

	chrono.end();
	


	LOG(INFO) << ci::position;
}
