#ifndef SHADER_SERVICE_HPP
#define SHADER_SERVICE_HPP

#include <string>

#include <glad/glad.h>

#include <modules/graphics/components/shader.hpp>

#include <core/math/vector2.hpp>
#include <core/math/vector3.hpp>
#include <core/math/vector4.hpp>

#include <core/math/matrix4.hpp>

namespace Blast2D {
	class ShaderService {
	public:
		//static Shader activeShader;

		void apply(const Shader& shader);
		Shader& compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource = nullptr);

		void setInteger(const Shader& shader, const GLchar* name, const int value);
		void setVector2(const Shader& shader, const GLchar* name, const Vector2& value);
		void setVector3(const Shader& shader, const GLchar* name, const Vector3& value);
		void setVector4(const Shader& shader, const GLchar* name, const Vector4& value);
		void setMatrix4(const Shader& shader, const GLchar* name, const Matrix4& matrix);

	private:
		void checkCompileErrors(GLuint object, std::string type);
	};
}

#endif