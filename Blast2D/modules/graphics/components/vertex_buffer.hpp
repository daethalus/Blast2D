#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include <vector>
#include <cstdint>

namespace Blast2D {
	struct VertexBuffer {
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;
		std::size_t size;
	};
}


#endif // !VERTEX_BUFFER


