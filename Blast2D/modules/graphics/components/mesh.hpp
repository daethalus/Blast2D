#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "vertex_position_color_texture.hpp";

namespace Blast2D {

	struct Mesh {
		std::vector<VertexPositionColorTexture> vertices;
		std::vector<std::uint32_t> indices;
	};
}

#endif // !MESH_HPP
