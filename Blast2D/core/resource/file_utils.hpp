#ifndef BLAST2D_FILE_UTILS_HPP
#define BLAST2D_FILE_UTILS_HPP


#include <fstream>
#include <iostream>
#include <core/logging/easylogging++.h>
#include <sstream>

namespace Blast2D{

    class FileUtils {
    public:
        static std::string loadTextFile(std::string filePath) {
            try {
                std::ifstream file(filePath);
                std::stringstream strStream;
                strStream << file.rdbuf();
                file.close();
                return strStream.str();
            } catch (std::exception e) {
                LOG(ERROR) <<  "Failed to load asset file:" << filePath << " error " << e.what() << std::endl;
                return "";
            }
        }

    };

}

#endif
