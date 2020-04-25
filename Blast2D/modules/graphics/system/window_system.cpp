#include "window_system.hpp"

#include <exception>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <core/logging/easylogging++.h>
#include <core/components/application.hpp>

#include <modules/graphics/components/window.hpp>
#include <modules/graphics/components/shader.hpp>
#include <modules/graphics/components/vertex_buffer.hpp>


#include <modules/graphics/libs/imgui/imgui.h>
#include <modules/graphics/libs/imgui/imgui_impl_glfw.h>
#include <modules/graphics/libs/imgui/imgui_impl_opengl3.h>

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

        entityManager.set<WindowHandler>(entity,  {window});

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

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
	});
}

void Blast2D::WindowSystem::onUpdate() {
	entityManager.forEach<WindowProperties, WindowHandler>([this](auto entity, WindowProperties& properties, WindowHandler& handler) {
		GLFWwindow* window = (GLFWwindow*) handler.handler;

		if (properties.maximize && !handler.maximized) {
			glfwMaximizeWindow(window);
			handler.maximized = true;
		}

		if (properties.vsync && !handler.vsyncOn) {
			glfwSwapInterval(1);
			handler.vsyncOn = true;
		}	

		if (!glfwWindowShouldClose(window)) {
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			SystemManager::getInstance().onRenderer();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();
		} else {
			auto& application = entityManager.last<Application>();
			application.running = false;
			entityManager.destroy(entity);
			glfwTerminate();
		}
	});
}