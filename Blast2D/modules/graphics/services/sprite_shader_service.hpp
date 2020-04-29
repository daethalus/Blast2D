#ifndef SPRITE_SHADER_SERVICE_HPP
#define SPRITE_SHADER_SERVICE_HPP

#include "shader_service.hpp"
#include <modules/graphics/resources/color.hpp>
#include <core/math/vector2.hpp>

namespace Blast2D {

	class SpriteShaderService : public ShaderService {
	public:
		SpriteShaderService(const SpriteShaderService&) = delete;
		SpriteShaderService operator=(const SpriteShaderService) = delete;

		static SpriteShaderService& getInstance() {
			static SpriteShaderService spriteShaderService;
			return spriteShaderService;
		}

		void setTexture(const Shader& shader, const int texture);
		void setColor(const Shader& shader, const Color& color);
		void setViewport(const Shader& shader, const Vector2& vector);
		void setTransform(const Shader& shader, const Matrix4& matrix4);
		void setCamera(Shader& shader, const Entity entity);
		Shader compile();
	private:
		SpriteShaderService(){}
	};

    static SpriteShaderService& spriteShaderService = SpriteShaderService::getInstance();
}

#endif // !SPRITE_SHADER_SERVICE_HPP
