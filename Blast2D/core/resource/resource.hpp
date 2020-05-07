#ifndef BLAST2D_RESOURCE_HPP
#define BLAST2D_RESOURCE_HPP


namespace Blast2D{

    class ResourceStorage {
    };

    template<typename Type>
    class ResourceTypeStorage : public ResourceStorage {
    private:
        std::unordered_map<std::string,Type> resources;
    public:
        Type& findResource(std::string resourceId) {
            auto resource = resources.find(resourceId);
            if (resource != resources.end()) {
                return resource->second;
            }
            std::string err = "resource " + resourceId + " not found";
            throw new std::exception(err.c_str());
        }
        std::unordered_map<std::string,Type>& findAll() {
            return resources;
        }

        template<typename... Args>
        void emplace(std::string resourceId, Args&&... args) {
            resources.emplace(std::make_pair(resourceId, Type{std::forward<Args>(args)...}));
        }
    };

}

#endif
