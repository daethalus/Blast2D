#ifndef SPRITE_BATCH_SERVICE
#define SPRITE_BATCH_SERVICE

#include <modules/graphics/components/mesh.hpp>
#include <core/components/transform.hpp>
#include <modules/graphics/resources/color.hpp>

namespace Blast2D {
	class SpriteBatchService {
	public:
        static SpriteBatchService & getInstance() {
            static SpriteBatchService spriteBatchService;
            return spriteBatchService;
        }
		void draw(Mesh& mesh);
		void draw(Mesh& mesh, const Sprite& sprite, const Transform& transform, const Color& color = {255,255,255,255});
	};

    static SpriteBatchService& spriteBatchService = SpriteBatchService::getInstance();
}

#endif


