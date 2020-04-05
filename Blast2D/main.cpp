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

namespace ci {
	auto position = Blast2D::EntityManager::component<Position>("Position");
}

int main() {
	LOG(INFO) << "Starting engine";
	Blast2D::EntityManager entityManager;
	auto info = ci::position;

	auto storage = Blast2D::Storage<Position>();	
	storage.assign(1, {10});

	auto pos = storage.get(1);

	storage.destroy(1);

	storage.get(1);

	LOG(INFO) << info;
}
