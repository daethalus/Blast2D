#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <cstdint>

#include "vertex_position_color_texture.hpp"

#include <core/ecs/entity_manager.hpp>

namespace Blast2D {

	struct Mesh {
		std::vector<VertexPositionColorTexture> vertices;
		std::vector<uint32_t> indices;
	};

	BLAST_COMPONENT(Mesh);
}

#endif // !MESH_HPP
