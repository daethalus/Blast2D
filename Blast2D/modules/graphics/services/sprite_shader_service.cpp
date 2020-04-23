#include "sprite_shader_service.hpp"

void Blast2D::SpriteShaderService::setTexture(const Shader& shader, const int texture) {
	setInteger(shader, "text", texture);
}

void Blast2D::SpriteShaderService::setColor(const Shader& shader, const Color& color) {
	setVector4(shader, "customColor", 
			   {	(float) color.red / 255,
					(float) color.green / 255, 
					(float) color.blue / 255,
					(float) color.alpha / 255
			   });
}

void Blast2D::SpriteShaderService::setViewport(const Shader& shader, const Vector2& vector) {
	setMatrix4(shader, "projection", Matrix4::ortho(0.0f, vector.x, vector.y, 0.0f, -1.0f, 1.0f));
}

void Blast2D::SpriteShaderService::setTransform(const Shader& shader, const Matrix4& matrix4) {
	setMatrix4(shader, "matrix", matrix4);
}

Blast2D::Shader Blast2D::SpriteShaderService::compile() {

	const char* vertex =
		"#version 330 core \n "
		"layout(location = 0) in vec3 vertex; \n "
		"layout(location = 1) in vec2 texCoords; \n "
		"layout(location = 2) in vec4 aColor; \n "
		"\n "
		"out vec2 TexCoords; \n "
		"out vec4 ourColor; \n "
		"\n "
		"uniform mat4 matrix; \n "
		"uniform mat4 projection; \n "
		"\n "
		"void main() { "
		"\n "
		"	TexCoords = texCoords; \n "
		"	ourColor = aColor; \n "
		"	gl_Position = projection * matrix * vec4(vertex.x, vertex.y, vertex.z, 1.0); \n "
		//"	gl_Position = vec4(vertex.x, vertex.y, vertex.z, 1.0); \n "
		"}";

	const char* fragment =
		"#version 330 core \n "
		"in vec2 TexCoords; \n "
		"out vec4 color; \n "
		"\n "
		"uniform sampler2D text; \n "
		"uniform vec4 customColor; \n "
		"in vec4 ourColor; \n "
		"\n "
		"void main() { \n"
		//"	color = ourColor * customColor * texture(text, TexCoords); \n "
		"	color = ourColor * customColor; \n "
		"} ";

	return ShaderService::compile(vertex, fragment);
}
