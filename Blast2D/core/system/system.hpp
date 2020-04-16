#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <core/ecs/entity_manager.hpp>

namespace Blast2D {
	class System {
	public:		
		virtual void onUpdate(EntityManager& entityManager) = 0;
	};
}

#endif