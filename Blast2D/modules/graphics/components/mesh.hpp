#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "vertex_position_color_texture.hpp"
#include <cstdint>

namespace Blast2D {

	struct Mesh {
		std::vector<VertexPositionColorTexture> vertices;
		std::vector<uint32_t> indices;
	};
}

#endif // !MESH_HPP
