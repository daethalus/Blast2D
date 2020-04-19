#ifndef VERTEX_POSITION_COLOR_TEXTURE_HPP
#define VERTEX_POSITION_COLOR_TEXTURE_HPP

namespace Blast2D {

	struct VertexPositionColorTexture {
		float x, y, z;
		float uvx, uvy;
		float r, g, b, a;

		VertexPositionColorTexture() :
			x(0), y(0), z(0), uvx(0), uvy(0), r(0), g(0), b(0), a(0) {
		}

		VertexPositionColorTexture(float _x, float _y, float _z, float _uvx, float _uuy, float _r, float _g, float _b, float _a):
			x(_x), y(_y), z(_z), uvx(_uvx), uvy(_uuy), r(_r), g(_g), b(_b), a(_a){

		}

	};
}

#endif




