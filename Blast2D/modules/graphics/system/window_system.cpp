#include "window_system.hpp"

#include <exception>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <core/logging/easylogging++.h>
#include <core/components/application.hpp>

#include <modules/graphics/components/window.hpp>

void Blast2D::WindowSystem::onCreate() {	
	entityManager.forEach<WindowProperties>([this](auto entity, WindowProperties&properties) {

		glfwSetErrorCallback([](int id, const char* description) {
			LOG(ERROR) << "GLFW ID: (" << id << ") description " << description;
		});

		if (!glfwInit()) {
            LOG(ERROR) << "Error on start glfwInit";
            return;
			//throw new std::exception("Error on start glfwInit");
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
            LOG(ERROR) << "Error on load gladLoadGLLoader";
            return;
        }

        entityManager.set<WindowHandler>(entity, WindowHandler{ window });

		glViewport(0, 0, 800, 600);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glfwSetFramebufferSizeCallback(window,[] (GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
			auto& em = EntityManager::getInstance();
			auto & wp = em.last<WindowProperties>();
			wp.size = { (float) width , (float)height };
		});
	});
}

void Blast2D::WindowSystem::onUpdate() {
	entityManager.forEach<WindowProperties, WindowHandler>([this](auto entity, WindowProperties& properties, WindowHandler& handler) {
		GLFWwindow* window = (GLFWwindow*) handler.handler;		

		if (properties.maximize && !handler.maximized) {
			glfwMaximizeWindow(window);
		}

		if (properties.vsync && !handler.vsyncOn) {
			glfwSwapInterval(1);
		}
		
		if (!glfwWindowShouldClose(window)) {

			glfwSwapBuffers(window);

			glfwPollEvents();			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
		} else {
			auto& application = entityManager.last<Application>();
			application.running = false;
			entityManager.destroy(entity);
			glfwTerminate();			
		}
	});
}