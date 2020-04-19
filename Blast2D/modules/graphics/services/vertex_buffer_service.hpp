#ifndef VERTEX_BUFFER_SERVICE_HPP
#define VERTEX_BUFFER_SERVICE_HPP

#include <modules/graphics/components/vertex_buffer.hpp>
#include <modules/graphics/components/mesh.hpp>

namespace Blast2D{
	class VertexBufferService {
	public:
		VertexBuffer generate();
		void draw(const VertexBuffer& vextexBuffer);
		void updateData(const VertexBuffer& vextexBuffer, const Mesh& mesh);
		void clearData(const VertexBuffer& vextexBuffer);
	};
}

#endif

