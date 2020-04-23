#ifndef BLAST2D_TEXTURE_SERVICE_HPP
#define BLAST2D_TEXTURE_SERVICE_HPP

#include <memory>
#include <unordered_map>

#include <core/graphics/image.hpp>
#include <modules/graphics/resources/Texture2D.hpp>


namespace Blast2D{
    class TextureService {
    private:
        TextureService() {}
        std::unordered_map<GLuint,std::unique_ptr<Texture2D>> textures;
    public:
        TextureService(TextureService const&) = delete;
        TextureService& operator=(TextureService const&) = delete;
        Texture2D& loadTexture(Image &image);
        Texture2D& getTexture(unsigned int ID);
        void bind(const Texture2D&);
        void bind(const unsigned int ID);
    };
}


#endif
