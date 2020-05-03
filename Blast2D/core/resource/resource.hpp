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
            } else {
                resources[resourceId] = std::forward<Type>({});
                return findResource(resourceId);
            }
        }
    };

}

#endif
