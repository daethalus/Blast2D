#ifndef VERTEX_BUFFER_SERVICE_HPP
#define VERTEX_BUFFER_SERVICE_HPP

#include <modules/graphics/components/vertex_buffer.hpp>
#include <modules/graphics/components/mesh.hpp>

namespace Blast2D{
	class VertexBufferService {
	public:
		VertexBufferService(const VertexBufferService&) = delete;
		VertexBufferService operator=(const VertexBufferService&) = delete;

		static VertexBufferService& getInstance() {
			static VertexBufferService vertex;
			return vertex;
		}

		VertexBuffer generate();		

		void draw(const VertexBuffer& vextexBuffer);
		void updateData(const VertexBuffer& vextexBuffer, const Mesh& mesh);
		void clearData(const VertexBuffer& vextexBuffer);

	private:
		VertexBufferService() {}
	};
}

#endif

