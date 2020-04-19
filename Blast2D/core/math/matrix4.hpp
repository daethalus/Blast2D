#ifndef MATRIX4_HPP
#define MATRIX4_HPP

namespace Blast2D {

	struct Matrix4 {
		float m[16];

		float operator[](int index) const {
			return m[index];
		}

		float& operator[](int index) {
			return m[index];
		}

		Matrix4() {
			m[0] = m[3] = 1.0f;
			m[1] = m[2] = 0.0f;			
		}

		
		static Matrix4 ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
			Matrix4 mat;
			mat[0] = 2 / (right - left);
			mat[5] = 2 / (top - bottom);
			mat[10] = -2 / (zFar - zNear);
			mat[12] = -(right + left) / (right - left);
			mat[13] = -(top + bottom) / (top - bottom);
			mat[14] = -(zFar + zNear) / (zFar - zNear);
			return mat;
		}
	};
}

#endif // !MATRIX4_HPP


