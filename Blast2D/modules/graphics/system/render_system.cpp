#include "render_system.hpp"

#include <modules/graphics/services/texture_service.hpp>
#include <modules/graphics/libs/imgui/imgui.h>

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
//	auto &window = entityManager.last<WindowProperties>();

    bool* value = new bool;
    ImGui::ShowDemoWindow(value);
}
