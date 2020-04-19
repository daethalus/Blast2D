#include "vertex_buffer_service.hpp"
#include <glad/glad.h>

Blast2D::VertexBuffer Blast2D::VertexBufferService::generate() {

	auto vextexBuffer = VertexBuffer();

	glGenVertexArrays(1, &vextexBuffer.VAO);
	glGenBuffers(1, &vextexBuffer.VBO);
	glGenBuffers(1, &vextexBuffer.EBO);

	glBindVertexArray(vextexBuffer.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vextexBuffer.VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return vextexBuffer;
}

void Blast2D::VertexBufferService::draw(const VertexBuffer& vextexBuffer) {
	if (vextexBuffer.size) {
		glBindVertexArray(vextexBuffer.VAO);
		glDrawElements(GL_TRIANGLES, vextexBuffer.size, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}

void Blast2D::VertexBufferService::updateData(const VertexBuffer& vextexBuffer, const Mesh& mesh) {	
	glBindVertexArray(vextexBuffer.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vextexBuffer.VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vector3), mesh.vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vextexBuffer.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Blast2D::VertexBufferService::clearData(const VertexBuffer& vextexBuffer) {
	glDeleteVertexArrays(1, &vextexBuffer.VAO);
	glDeleteBuffers(1, &vextexBuffer.VBO);
	glDeleteBuffers(1, &vextexBuffer.EBO);
	glBindVertexArray(0);
}
