#ifndef BLAST2D_IMAGE_HPP
#define BLAST2D_IMAGE_HPP

namespace Blast2D{

    struct Image{
        int width;
        int height;
        int nrChannels;
        unsigned char* data;
    };
}

#endif //BLAST2D_IMAGE_HPP
