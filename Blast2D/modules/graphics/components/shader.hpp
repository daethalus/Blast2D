#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <core/ecs/entity_manager.hpp>

namespace Blast2D {

	struct Shader {
		GLuint ID;
	};

	BLAST_COMPONENT(Shader);
}

#endif


