#ifndef SHADER_HPP
#define SHADER_HPP

#include <core/ecs/entity_manager.hpp>

namespace Blast2D {

	struct Shader {
		unsigned int ID;
		Entity camera = NULL_ID;
	};

	BLAST_COMPONENT(Shader);
}

#endif


