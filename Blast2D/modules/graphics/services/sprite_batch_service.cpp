#include "sprite_batch_service.hpp"

void Blast2D::SpriteBatchService::draw(Mesh &mesh) {
    float x = 100.0f;
    float y = 100.0f;
    float size = 200;
    mesh.vertices.emplace_back(x, y + size, 1, 0, 0, 1, 0.5, 1, 1);
    mesh.vertices.emplace_back(x + size, y, 1, 0, 0, 1, 0.5, 1, 1);
    mesh.vertices.emplace_back(x, y, 1, 0, 0, 1, 0.5, 1, 1);
    mesh.vertices.emplace_back(x + size, y + size, 1, 0, 0, 1, 0.5, 1, 1);

    mesh.indices.emplace_back(2);
    mesh.indices.emplace_back(0);
    mesh.indices.emplace_back(3);
    mesh.indices.emplace_back(1);
    mesh.indices.emplace_back(2);
    mesh.indices.emplace_back(3);
}

void Blast2D::SpriteBatchService::draw(Blast2D::Mesh &mesh, const Blast2D::Sprite &sprite,
                                       const Blast2D::Transform &transform, const Blast2D::Color &color) {

    mesh.vertices.emplace_back(transform.position.x,
                               transform.position.y + transform.size.y,
                               transform.position.z,
                               sprite.offset.x / mesh.spriteSheet->width,
                               ((float) sprite.offset.y + sprite.offset.height) / mesh.spriteSheet->height,
                               color.red / 255, color.green / 255, color.blue / 255, color.alpha / 255);

    mesh.vertices.emplace_back(transform.position.x + transform.size.x,
                               transform.position.y,
                               transform.position.z,
                               ((float) sprite.offset.x + sprite.offset.width) / mesh.spriteSheet->width,
                               sprite.offset.y / mesh.spriteSheet->height,
                               color.red / 255, color.green / 255, color.blue / 255, color.alpha / 255);

    mesh.vertices.emplace_back(transform.position.x,
                               transform.position.y,
                               transform.position.z,
                               sprite.offset.x / mesh.spriteSheet->width,
                               sprite.offset.y / mesh.spriteSheet->height,
                               color.red / 255, color.green / 255,color.blue / 255,color.alpha / 255);

    mesh.vertices.emplace_back(transform.position.x + transform.size.x,
                               transform.position.y + transform.size.y,
                               transform.position.z,
                               ((float) sprite.offset.x + sprite.offset.width) / mesh.spriteSheet->width,
                               ((float) sprite.offset.y + sprite.offset.height) / mesh.spriteSheet->height,
                               color.red / 255,color.green / 255,color.blue / 255, color.alpha / 255);

    mesh.indices.emplace_back(mesh.index + 2);
    mesh.indices.emplace_back(mesh.index + 0);
    mesh.indices.emplace_back(mesh.index + 3);
    mesh.indices.emplace_back(mesh.index + 1);
    mesh.indices.emplace_back(mesh.index + 2);
    mesh.indices.emplace_back(mesh.index + 3);
    mesh.index = mesh.index + 4;
}


