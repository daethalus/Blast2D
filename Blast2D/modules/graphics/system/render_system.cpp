#include "render_system.hpp"

#include <modules/graphics/components/mesh.hpp>
#include <modules/graphics/components/shader.hpp>
#include <modules/graphics/components/vertex_buffer.hpp>

void Blast2D::RenderSystem::onUpdate() {
	entityManager.forEach<Mesh>([this](auto entity, Mesh& mesh) {
		auto vertexBuffer = vertexBufferService.generate();
		vertexBuffer.size = mesh.indices.size();
		vertexBufferService.updateData(vertexBuffer, mesh);		
		entityManager.remove<Mesh>(entity);
		entityManager.set<VertexBuffer>(entity, VertexBuffer(vertexBuffer));
	});

	//entityManager.forEach<VertexBuffer, Shader>([this](auto entity, VertexBuffer& vertexBuffer, Shader& shader) {
	//	shaderService.apply(shader);
	//	vertexBufferService.draw(vertexBuffer);
	//});
}
