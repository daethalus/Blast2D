#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include <vector>
#include <cstdint>

#include <core/ecs/entity_manager.hpp>

namespace Blast2D {
	struct VertexBuffer {
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;
		std::size_t size;
	};

	BLAST_COMPONENT(VertexBuffer);
}


#endif // !VERTEX_BUFFER


