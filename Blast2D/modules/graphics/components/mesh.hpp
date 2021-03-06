#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <cstdint>

#include "vertex_position_color_texture.hpp"

#include <core/ecs/entity_manager.hpp>
#include <modules/graphics/resources/sprite_sheet.hpp>

namespace Blast2D {

	struct Mesh {
		std::vector<VertexPositionColorTexture> vertices;
		std::vector<uint32_t> indices;
		std::shared_ptr<SpriteSheet> spriteSheet;
		unsigned int index;
        Mesh() : index(0){}
        //Mesh(const Mesh&) = delete;
        //const Mesh& operator=(Mesh const&) = delete;
	};

	BLAST_COMPONENT(Mesh);
}

#endif // !MESH_HPP
