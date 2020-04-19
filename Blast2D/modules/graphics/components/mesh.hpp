#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <core/math/vector2.hpp>
#include <core/math/vector3.hpp>
#include <core/math/vector4.hpp>

namespace Blast2D {

	struct Mesh {
		std::vector<Vector3> vertices;
		std::vector<Vector2> uvs;
		std::vector<Vector4> colors;
		std::vector<std::uint32_t> indices;
	};
}

#endif // !MESH_HPP
