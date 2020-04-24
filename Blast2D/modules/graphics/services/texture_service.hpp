#ifndef BLAST2D_TEXTURE_SERVICE_HPP
#define BLAST2D_TEXTURE_SERVICE_HPP

#include <memory>
#include <unordered_map>

#include <modules/graphics/resources/image.hpp>
#include <modules/graphics/resources/texture_2d.hpp>


namespace Blast2D{
    class TextureService {
    private:
        TextureService() {}
        std::unordered_map<GLuint,std::unique_ptr<Texture2D>> textures;
    public:
        TextureService(TextureService const&) = delete;
        TextureService& operator=(TextureService const&) = delete;

        static TextureService& getInstance() {
            static TextureService textureService;
            return textureService;
        }

        Texture2D& loadTexture(std::shared_ptr<Image> image);
        Texture2D& getTexture(unsigned int ID);
        void bind(const Texture2D&);
        void bind(const unsigned int ID);
    };
}


#endif
