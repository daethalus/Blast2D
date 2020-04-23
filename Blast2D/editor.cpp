#include <queue>
#include <core/logging/easylogging++.h>
#include <core/ecs/entity_manager.hpp>
#include <core/components/application.hpp>
#include <core/system/system.hpp>
#include <modules/graphics/components/window.hpp>
#include <modules/graphics/components/vertex_buffer.hpp>
#include <modules/graphics/services/sprite_shader_service.hpp>
#include <modules/graphics/services/sprite_batch_service.hpp>

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
	
	Blast2D::SystemManager&sm = Blast2D::SystemManager::getInstance();

	LOG(INFO) << "Starting engine";
	Blast2D::EntityManager &entityManager = Blast2D::EntityManager::getInstance();

	entityManager.create(
		Blast2D::WindowProperties{true}
	);

	entityManager.create(
		Blast2D::Application{ true }
	);

	sm.create();

	Blast2D::SpriteShaderService sp;
	auto shader = sp.compile();

	sp.apply(shader);
	sp.setTransform(shader, Blast2D::Matrix4(1));
	sp.setViewport(shader, { 1920, 1017});
	sp.setTexture(shader, 0);
	sp.setColor(shader, { 255,255,255,255 });

	Blast2D::SpriteBatchService sbp;
	//auto mesh = Blast2D::Mesh();


	auto entity = entityManager.create();
	entityManager.set<Blast2D::Shader>(entity, shader);
    auto&mesh = entityManager.assign<Blast2D::Mesh>(entity);
    sbp.draw(mesh);

	auto& application = entityManager.last<Blast2D::Application>();
	do {		
		sm.update();
	} while (application.running);
}
