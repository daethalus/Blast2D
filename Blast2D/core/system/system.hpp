#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <core/ecs/entity_manager.hpp>

namespace Blast2D {
	class System {
	public:		
		EntityManager& entityManager = EntityManager::getInstance();
		virtual void onCreate() {};
		virtual void onUpdate() = 0;
	};
}

#endif