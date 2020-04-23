#ifndef SPRITE_SHADER_SERVICE_HPP
#define SPRITE_SHADER_SERVICE_HPP

#include "shader_service.hpp"
#include <core/graphics/color.hpp>
#include <core/math/vector2.hpp>

namespace Blast2D {

	class SpriteShaderService : public ShaderService {
	public:
		void setTexture(const Shader& shader, const int texture);
		void setColor(const Shader& shader, const Color& color);
		void setViewport(const Shader& shader, const Vector2& vector);
		void setTransform(const Shader& shader, const Matrix4& matrix4);
		Shader compile();
	};	
}

#endif // !SPRITE_SHADER_SERVICE_HPP
