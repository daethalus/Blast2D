#ifndef BLAST2D_TEXTURE_2D_HPP
#define BLAST2D_TEXTURE_2D_HPP

#include <glad/glad.h>

namespace Blast2D{

    struct Texture2D {
        unsigned int ID;
        unsigned int width, height;
        unsigned int internalFormat;
        unsigned int imageFormat;
        unsigned int wrapS;
        unsigned int wrapT;
        unsigned int filterMin;
        unsigned int filterMax;
		Texture2D():
			ID(0), width(0), height(0), internalFormat(GL_RGBA), imageFormat(GL_RGBA), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_NEAREST), filterMax(GL_NEAREST) {

		}
    };
}

#endif
