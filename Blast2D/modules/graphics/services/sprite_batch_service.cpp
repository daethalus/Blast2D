#include "sprite_batch_service.hpp"

void Blast2D::SpriteBatchService::draw(Mesh& mesh) {
	/*float x = 0.0f;
	float y = 0.0f;
	float size = 0.5;
	mesh.vertices.emplace_back(x, y + size, 1, 0, 0, 1, 0.5, 1, 1);
	mesh.vertices.emplace_back(x+ size, y, 1, 0, 0, 1, 0.5, 1, 1);
	mesh.vertices.emplace_back(x, y, 1, 0, 0, 1, 0.5, 1, 1);
	mesh.vertices.emplace_back(x+ size, y+ size, 1, 0, 0, 1, 0.5, 1, 1);


	mesh.indices.emplace_back(2);
	mesh.indices.emplace_back(0);
	mesh.indices.emplace_back(3);
	mesh.indices.emplace_back(1);
	mesh.indices.emplace_back(2);
	mesh.indices.emplace_back(3);*/


	mesh.vertices.emplace_back(0.5f, 0.5f, 0.0f, 0, 0, 1, 0.5, 1, 1);
	mesh.vertices.emplace_back(0.5f, -0.5f, 0.0f, 0, 0, 1, 0.5, 1, 1);
	mesh.vertices.emplace_back(-0.5f, -0.5f, 0.0f, 0, 0, 1, 0.5, 1, 1);
	mesh.vertices.emplace_back(-0.5f, 0.5f, 0.0f, 0, 0, 1, 0.5, 1, 1);

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	mesh.indices.emplace_back(0);
	mesh.indices.emplace_back(1);
	mesh.indices.emplace_back(3);
	mesh.indices.emplace_back(1);
	mesh.indices.emplace_back(2);
	mesh.indices.emplace_back(3);
}


