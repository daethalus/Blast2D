#ifndef BLAST2D_RESOURCE_LOADER_HPP
#define BLAST2D_RESOURCE_LOADER_HPP

#include <string>

namespace Blast2D{

    class ResourceLoader{
        virtual void loadFile(std::string path) = 0;
    };
}

#endif
