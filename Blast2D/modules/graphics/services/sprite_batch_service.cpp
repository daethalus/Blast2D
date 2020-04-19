#include "sprite_batch_service.hpp"

void Blast2D::SpriteBatchService::draw(Mesh& mesh) {
	mesh.vertices.emplace_back(0, 10, 0);
	mesh.uvs.emplace_back(0, 0);
	mesh.colors.emplace_back(1, 1, 1, 1);

	mesh.vertices.emplace_back(10, 0, 0);
	mesh.uvs.emplace_back(0, 0);
	mesh.colors.emplace_back(1, 1, 1, 1);

	mesh.vertices.emplace_back(0, 0, 0);
	mesh.uvs.emplace_back(0, 0);
	mesh.colors.emplace_back(1, 1, 1, 1);

	mesh.vertices.emplace_back(10, 10, 0);
	mesh.uvs.emplace_back(0, 0);
	mesh.colors.emplace_back(1, 1, 1, 1);

	mesh.indices.emplace_back(2);
	mesh.indices.emplace_back(0);
	mesh.indices.emplace_back(3);
	mesh.indices.emplace_back(1);
	mesh.indices.emplace_back(2);
	mesh.indices.emplace_back(3);
}
