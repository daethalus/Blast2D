#ifndef VECTOR4_HPP
#define VECTOR4_HPP

namespace Blast2D {

	struct Vector4 {
		float x;
		float y;
		float z;
		float w;
		Vector4() : x(0), y(0), z(0), w(0) {
		}
		Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {
		}
	};
}



#endif


