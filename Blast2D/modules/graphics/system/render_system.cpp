#include "render_system.hpp"

#include <modules/graphics/components/mesh.hpp>
#include <modules/graphics/components/shader.hpp>
#include <modules/graphics/components/vertex_buffer.hpp>

#include <modules/graphics/services/texture_service.hpp>

void Blast2D::RenderSystem::onUpdate() {
	entityManager.forEach<Mesh>([this](auto entity, Mesh& mesh) {
		auto vertexBuffer = VertexBufferService::getInstance().generate();
		vertexBuffer.size = mesh.indices.size();
		vertexBuffer.texture = mesh.spriteSheet->textureId;
		VertexBufferService::getInstance().updateData(vertexBuffer, mesh);
		entityManager.remove<Mesh>(entity);
		entityManager.set<VertexBuffer>(entity, vertexBuffer);
	});
}

void Blast2D::RenderSystem::onRenderer() {
	entityManager.forEach<VertexBuffer, Shader>([this](auto entity, VertexBuffer& vertexBuffer, Shader& shader) {
		TextureService::getInstance().bind(vertexBuffer.texture);
		ShaderService::getInstance().apply(shader);
		VertexBufferService::getInstance().draw(vertexBuffer);
	});
}
