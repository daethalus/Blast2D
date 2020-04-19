#include <iostream>
#include <functional>
#include <thread>
#include <queue>
#include <chrono>
#include <thread>

#include <core/logging/easylogging++.h>
#include <core/logging/chronometer.hpp>
#include <core/ecs/entity_manager.hpp>
#include <core/ecs/sparse_set.hpp>
#include <core/ecs/storage.hpp>
#include <core/components/application.hpp>

#include <core/system/thread_pool.hpp>
#include <core/system/system.hpp>
#include <core/system/system_manager.hpp>

#include <modules/graphics/system/window_system.hpp>
#include <modules/graphics/system/render_system.hpp>
#include <modules/graphics/components/window.hpp>
#include <modules/graphics/components/vertex_buffer.hpp>
#include <modules/graphics/services/sprite_shader_service.hpp>
#include <modules/graphics/services/sprite_batch_service.hpp>

#include <core/math/matrix4.hpp>

INITIALIZE_EASYLOGGINGPP

struct Position {
	int x;
};

struct Velocity {
	int y;
};

struct Container {
	int z;
};


int main() {

	Blast2D::Matrix4::ortho(0.0f, (float)1920, (float)1017, 0.0f, -1.0f, 1.0f);

	Blast2D::SystemManager sm;
	
	sm.add<Blast2D::WindowSystem>("Blast2D_WindowSystem");
	sm.add<Blast2D::RenderSystem>("Blast2D_RenderSystem");
	

	LOG(INFO) << "Starting engine";
	Blast2D::EntityManager &entityManager = Blast2D::EntityManager::getInstance();
	entityManager.createComponent<Blast2D::WindowProperties>();
	entityManager.createComponent<Blast2D::WindowHandler>();
    entityManager.createComponent<Blast2D::Application>();
	entityManager.createComponent<Blast2D::Mesh>();
	entityManager.createComponent<Blast2D::Shader>();
	entityManager.createComponent<Blast2D::Shader>();
	entityManager.createComponent<Blast2D::VertexBuffer>();

	entityManager.create(
		Blast2D::WindowProperties{true}
	);

	entityManager.create(
		Blast2D::Application{ true }
	);

	sm.create();

	Blast2D::SpriteShaderService sp;
	auto& shader = sp.compile();

	sp.apply(shader);
	sp.setTransform(shader, Blast2D::Matrix4(1));
	sp.setViewport(shader, { 1920, 1017});
	sp.setTexture(shader, 0);
	sp.setColor(shader, { 255,255,255,255 });

	Blast2D::SpriteBatchService sbp;
	auto& mesh = Blast2D::Mesh();
	sbp.draw(mesh);

	auto entity = entityManager.create();
	entityManager.set<Blast2D::Shader>(entity, Blast2D::Shader(shader));
	entityManager.set<Blast2D::Mesh>(entity, Blast2D::Mesh(mesh));

	auto& application = entityManager.last<Blast2D::Application>();
	do {		
		sm.update();		
	} while (application.running);		
}
