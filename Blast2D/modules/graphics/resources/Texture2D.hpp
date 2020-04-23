#ifndef BLAST2D_TEXTURE2D_HPP
#define BLAST2D_TEXTURE2D_HPP

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
    };
}

#endif
