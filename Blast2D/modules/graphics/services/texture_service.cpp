#include "texture_service.hpp"

Blast2D::Texture2D &Blast2D::TextureService::getTexture(unsigned int ID) {
    return *textures[ID].get();
}

void Blast2D::TextureService::bind(const Blast2D::Texture2D &texture) {
    this->bind(texture.ID);
}

void Blast2D::TextureService::bind(const unsigned int ID) {
    //TODO - handle with bind multiple textures
    //glActiveTexture(GL_TEXTURE0 + textureNumber);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}

Blast2D::Texture2D &Blast2D::TextureService::loadTexture(std::shared_ptr<Image> image) {
    unsigned int id;
    glGenTextures(1, &id);
    textures[id] = std::make_unique<Texture2D>();
    auto &texture = textures[id];
    texture->ID = id;
    texture->height = image->height;
    texture->width = image->width;
	bind(id);    
    glTexImage2D(GL_TEXTURE_2D, 0, texture->internalFormat, texture->width, texture->height, 0, texture->imageFormat, GL_UNSIGNED_BYTE, image->data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->filterMax);
    glBindTexture(GL_TEXTURE_2D, 0);
    return *texture;
}
