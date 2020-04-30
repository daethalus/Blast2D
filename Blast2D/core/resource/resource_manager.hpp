#ifndef BLAST2D_RESOURCE_MANAGER_HPP
#define BLAST2D_RESOURCE_MANAGER_HPP

#include <string>
#include "resource_loader.hpp"
#include <unordered_map>
#include <memory>

namespace Blast2D{

    class ResourceManager {
    private:
        ResourceManager() = default;
        std::unordered_map<std::string,  std::unique_ptr<ResourceLoader>> loaders;
    public:
        static ResourceManager& getInstance() {
            ResourceManager resourceManager;
            return resourceManager;
        }

        template<typename Type>
        void registerResourceLoader(std::string fileType) {
            auto resourceLoader = std::make_unique<Type>();
            loaders[fileType] = std::static_pointer_cast<Tyoe>(resourceLoader);
        }
        void load();
    };

    static ResourceManager &resourceManager = ResourceManager::getInstance();
}

#endif
