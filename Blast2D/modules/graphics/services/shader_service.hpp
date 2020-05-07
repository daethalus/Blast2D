#ifndef SHADER_SERVICE_HPP
#define SHADER_SERVICE_HPP

#include <string>
#include <modules/graphics/components/shader.hpp>

#include <core/math/vector2.hpp>
#include <core/math/vector3.hpp>
#include <core/math/vector4.hpp>

#include <core/math/matrix4.hpp>

namespace Blast2D {
	class ShaderService {
	public:
		ShaderService(ShaderService const&) = delete;
		ShaderService& operator=(ShaderService const&) = delete;

		static ShaderService& getInstance() {
			static ShaderService shaderService;
			return shaderService;
		}

		void apply(const Shader& shader);
		Shader compile(const const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

		void setInteger(const Shader& shader, const char* name, const int value);
		void setVector2(const Shader& shader, const char* name, const Vector2& value);
		void setVector3(const Shader& shader, const char* name, const Vector3& value);
		void setVector4(const Shader& shader, const char* name, const Vector4& value);
		void setMatrix4(const Shader& shader, const char* name, const Matrix4& matrix);
	protected:
		ShaderService() {
		}
	private:		
		void checkCompileErrors(unsigned int object, std::string type);
	};
}

#endif