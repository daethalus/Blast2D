#include "window_system.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <core/logging/easylogging++.h>
#include <core/components/application.hpp>

#include <modules/graphics/components/window.hpp>

void Blast2D::WindowSystem::onCreate(EntityManager& entityManager) {
	entityManager.forEach<WindowProperties>([&entityManager](auto entity, WindowProperties&properties) {

		glfwSetErrorCallback([](int id, const char* description) {
			LOG(ERROR) << "GLFW ID: (" << id << ") description " << description;
		});

		if (!glfwInit()) {
			throw new std::exception("Error on start glfwInit");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(800, 600, "Evolutio", NULL, NULL);
		if (!window) {
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw new std::exception("Error on load gladLoadGLLoader");
		}

		glViewport(0, 0, 800, 600);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSwapInterval(1);

		glfwSetFramebufferSizeCallback(window,[] (GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);			
		});

		entityManager.set<WindowHandler>(entity, { window });
	});
}

void Blast2D::WindowSystem::onUpdate(EntityManager& entityManager) {
	entityManager.forEach<WindowProperties, WindowHandler>([&entityManager](auto entity, WindowProperties& properties, WindowHandler& handler) {
		GLFWwindow* window = (GLFWwindow*) handler.handler;		
		if (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glfwSwapBuffers(window);
		} else {
			auto& application = entityManager.last<Application>();
			application.running = false;
			entityManager.destroy(entity);
			glfwTerminate();			
		}
	});
}