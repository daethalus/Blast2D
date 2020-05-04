#ifndef BLAST2D_RESOURCE_MANAGER_HPP
#define BLAST2D_RESOURCE_MANAGER_HPP

#include <string>
#include "resource_loader.hpp"
#include <unordered_map>
#include <memory>
#include <filesystem>
#include "resource.hpp"
#include <core/ecs/type_info.hpp>
#include <assert.h>
#include <core/logging/easylogging++.h>

#define BLAST_RESOURCE_LOADER(Type, FileType) inline const bool resource_loader_##Type = Blast2D::ResourceManager::getInstance().registerResourceLoader<Type>(#FileType);
#define BLAST_RESOURCE(Type) inline const static bool resource##T = Blast2D::ResourceManager::getInstance().createResource<Type>();

namespace fs = std::filesystem;

namespace Blast2D{

    class ResourceManager {
    private:
        ResourceManager() = default;

        //TODO - why?
        inline static std::vector<std::unique_ptr<ResourceLoader>> loaders = std::vector<std::unique_ptr<ResourceLoader>>();
        inline static std::vector<std::unique_ptr<ResourceStorage>> resources = std::vector<std::unique_ptr<ResourceStorage>>();

        void loadDirectory(const std::string module, const fs::directory_entry& entry);
        template<typename Type>
        ResourceTypeStorage<Type>& assure() {
            const auto index = TypeInfo<Type>::index(-1);
            assert(resources.size() > index);
            return static_cast<ResourceTypeStorage<Type>&>(*resources[index]);
        }

    public:
        static ResourceManager& getInstance() {
            static ResourceManager resourceManager;
            return resourceManager;
        }

        template<typename Type>
        bool createResource() {
            TypeInfo<Type>::index(resources.size());
            resources.push_back({std::unique_ptr<ResourceStorage>{new ResourceTypeStorage<Type>()}});
            return true;
        }

        template<typename Type>
        bool registerResourceLoader(std::string fileType) {
            LOG(INFO) << "Resource loader loaded: " << typeid(Type).name() <<  " file type: " << fileType;
            auto loader = std::make_unique<Type>();
            loader->fileExtension = fileType;
            loaders.push_back(std::move(loader));
            return true;
        }


        template<typename Type>
        Type& load(std::string resourceId) {
            auto& storage = assure<Type>();
            return storage.findResource(resourceId);
        }

        template<typename Type>
        std::unordered_map<std::string, Type>& loadAll() {
            auto& storage = assure<Type>();
            return storage.findAll();
        }



        std::vector<std::string> getFilesFromFolder(std::string folder);

        void load();

        void load(std::string baseFolder);
    };

    static ResourceManager &resourceManager = ResourceManager::getInstance();
}

#endif
