#ifndef BLAST2D_RESOURCE_LOADER_HPP
#define BLAST2D_RESOURCE_LOADER_HPP

#include <string>

namespace Blast2D{

    struct ResourceConfigFile {
        std::string module;
        std::string path;
        std::string folder;
        std::string content;
    };

    class ResourceLoader{
    public:
        std::string fileExtension;
        virtual void loadFile(const ResourceConfigFile&& configFile) = 0;
    };
}

#endif
