#include "resource_manager.hpp"
#include "file_utils.hpp"
#include <core/logging/easylogging++.h>

void Blast2D::ResourceManager::load() {
    this->load("C:/dev/Blast2D/resources");
}

void Blast2D::ResourceManager::load(std::string baseFolder) {
    LOG(INFO) << "ResourceManager Initialization base folder(" << baseFolder << ")";

    auto resourceDirectory = fs::directory_entry(fs::path(baseFolder));
    for (const fs::directory_entry& child : fs::directory_iterator(resourceDirectory)) {
        if (fs::is_directory(child)) {
            auto fileName = child.path().stem().string();
            loadDirectory(fileName, child);
        }
    }
}

void Blast2D::ResourceManager::loadDirectory(const std::string module, const fs::directory_entry& entry) {
    for (const fs::directory_entry& child : fs::directory_iterator(entry)) {
        if (fs::is_directory(child)) {
            loadDirectory(module, child);
        } else {
            for (const auto& loader: loaders) {
                if (child.path().extension().string() == "." + loader->fileExtension) {
                    loader->loadFile({module, child.path().string(), FileUtils::loadTextFile(child.path().string())});
                }
            }
        }
    }
}


