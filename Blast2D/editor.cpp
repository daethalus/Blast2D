#include <queue>
#include <core/logging/easylogging++.h>
#include <core/ecs/entity_manager.hpp>
#include <core/components/application.hpp>
#include <core/system/system.hpp>
#include <modules/graphics/components/window.hpp>
#include <modules/graphics/components/vertex_buffer.hpp>
#include <modules/graphics/services/sprite_shader_service.hpp>
#include <modules/graphics/services/sprite_batch_service.hpp>
#include <modules/graphics/services/image_service.hpp>
#include <modules/graphics/services/texture_service.hpp>

#include <core/math/matrix4.hpp>

INITIALIZE_EASYLOGGINGPP


struct Position  {
	int x;
};

struct Velocity {
	int y;
};

struct Container {
	int z;
};


int main() {	
	
	Blast2D::SystemManager &systemManager = Blast2D::SystemManager::getInstance();
    Blast2D::EntityManager &entityManager = Blast2D::EntityManager::getInstance();


	LOG(INFO) << "Starting engine";

	entityManager.create(
		Blast2D::WindowProperties{true}
	);

	entityManager.create(
		Blast2D::Application{ true }
	);

	systemManager.create();

    Blast2D::SpriteShaderService sp;
    auto shader = sp.compile();
    sp.apply(shader);
    sp.setTransform(shader, Blast2D::Matrix4(1));
    sp.setViewport(shader, { 1920, 1017});
    sp.setTexture(shader, 0);
    sp.setColor(shader, { 255,255,255,255 });

	auto& imageService = Blast2D::ImageService::getInstance();

    auto img = imageService.loadImage("test-engineer.png");
    Blast2D::SpriteSheetBuilder spriteSheetBuilder;
    imageService.pack(spriteSheetBuilder, *img);
    auto spriteSheet = imageService.buildSpriteSheet(spriteSheetBuilder);

	Blast2D::SpriteBatchService sbp;
	//auto mesh = Blast2D::Mesh();

	auto entity = entityManager.create();
	entityManager.set<Blast2D::Shader>(entity, shader);
    auto&mesh = entityManager.assign<Blast2D::Mesh>(entity);
    mesh.spriteSheet = spriteSheet;
    Blast2D::Transform transform = {{100,100,1},{300,300},0};
    sbp.draw(mesh,spriteSheet->sprites.front(),transform);

	auto& application = entityManager.last<Blast2D::Application>();
	do {		
		systemManager.update();
	} while (application.running);
}
