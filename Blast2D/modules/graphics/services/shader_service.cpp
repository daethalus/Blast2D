#include "shader_service.hpp"
#include <core/logging/easylogging++.h>

void Blast2D::ShaderService::apply(const Shader& shader) {
	//if (shader.ID != ShaderService::activeShader.ID) {
	//	activeShader = shader;
	//	glUseProgram(shader.ID);
	//}
	glUseProgram(shader.ID);
}

Blast2D::Shader Blast2D::ShaderService::compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource) {
	GLuint sVertex, sFragment, gShader;

	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");

	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");
	
	if (geometrySource != nullptr) {
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}

    Shader shader;
	
	shader.ID = glCreateProgram();

	glAttachShader(shader.ID, sVertex);
	glAttachShader(shader.ID, sFragment);

	if (geometrySource != nullptr) {
		glAttachShader(shader.ID, gShader);
	}
		
	glLinkProgram(shader.ID);

	checkCompileErrors(shader.ID, "PROGRAM");	

	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr) {
		glDeleteShader(gShader);
	}
	return shader;
}

void Blast2D::ShaderService::setInteger(const Shader& shader, const GLchar* name, const int value) {
	glUniform1i(glGetUniformLocation(shader.ID, name), value);
}

void Blast2D::ShaderService::setVector2(const Shader& shader, const GLchar* name, const Vector2& value) {
	glUniform2f(glGetUniformLocation(shader.ID, name), value.x, value.y);
}

void Blast2D::ShaderService::setVector3(const Shader& shader, const GLchar* name, const Vector3& value) {
	glUniform3f(glGetUniformLocation(shader.ID, name), value.x, value.y, value.z);
}

void Blast2D::ShaderService::setVector4(const Shader& shader, const GLchar* name, const Vector4& value) {
	glUniform4f(glGetUniformLocation(shader.ID, name), value.x, value.y, value.z, value.w);
}

void Blast2D::ShaderService::setMatrix4(const Shader& shader, const GLchar* name, const Matrix4& matrix) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, name), 1, GL_FALSE, &matrix.m[0]);
}

void Blast2D::ShaderService::checkCompileErrors(GLuint object, std::string type) {
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			LOG(ERROR) << "SHADER: Compile-time error: Type: " << type << "\n" << infoLog << "\n";
		}
	} else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			LOG(ERROR) << "Shader: Link-time error: Type: " << type << "\n" << infoLog << "\n";
		}
	}
}
