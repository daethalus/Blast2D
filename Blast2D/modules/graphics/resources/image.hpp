#ifndef BLAST2D_IMAGE_HPP
#define BLAST2D_IMAGE_HPP

#include <string>

namespace Blast2D{
    struct Image{
        int width;
        int height;
        int nrChannels;
        unsigned char* data;
        std::string path;
        Image(int _width, int _height, int _nrChannels, unsigned char* _data, std::string _path):
            width(_width), height(_height), nrChannels(_nrChannels), data(_data), path(_path)  {
            if (data == nullptr) {
                int size = width * height * nrChannels;
                data = new unsigned char[size];

                for (int sourceY = 0; sourceY < height; ++sourceY) {
                    for (int sourceX = 0; sourceX < width; ++sourceX) {
                        int posPixel = (nrChannels * (sourceY * width + sourceX));
                        data[posPixel++] = '\0';
                        data[posPixel++] = '\0';
                        data[posPixel++] = '\0';
                        data[posPixel] = '\0';
                    }
                }
            }
        }
    };
}

#endif
