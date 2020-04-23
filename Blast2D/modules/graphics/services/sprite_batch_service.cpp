#include "sprite_batch_service.hpp"

void Blast2D::SpriteBatchService::draw(Mesh& mesh) {
	float x = 100.0f;
	float y = 100.0f;
	float size = 200;
	mesh.vertices.emplace_back(x, y + size, 1, 0, 0, 1, 0.5, 1, 1);
	mesh.vertices.emplace_back(x+ size, y, 1, 0, 0, 1, 0.5, 1, 1);
	mesh.vertices.emplace_back(x, y, 1, 0, 0, 1, 0.5, 1, 1);
	mesh.vertices.emplace_back(x+ size, y+ size, 1, 0, 0, 1, 0.5, 1, 1);

	mesh.indices.emplace_back(2);
	mesh.indices.emplace_back(0);
	mesh.indices.emplace_back(3);
	mesh.indices.emplace_back(1);
	mesh.indices.emplace_back(2);
	mesh.indices.emplace_back(3);
}


