#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <core/ecs/entity_manager.hpp>

namespace Blast2D {

	struct Application {
		bool running;
	};

	BLAST_COMPONENT(Application);
}

#endif


