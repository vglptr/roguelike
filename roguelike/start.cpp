#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include "timer.hpp"
#include "vertexgenerator.hpp"
#include "tile.hpp"
#include <deque>
#include <vector>

GLFWwindow* window;
Timer timer;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W) {
		Cam::getInstance().translate(glm::vec3(0, 0, -timer.getDelta() * 3));
	}
	if (key == GLFW_KEY_S) {
		Cam::getInstance().translate(glm::vec3(0, 0, timer.getDelta() * 3));
	}
	if (key == GLFW_KEY_A) {
		Cam::getInstance().translate(glm::vec3(-timer.getDelta() * 3, 0, 0));
	}
	if (key == GLFW_KEY_D) {
		Cam::getInstance().translate(glm::vec3(timer.getDelta() * 3, 0, 0));
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Cam::getInstance().setProjection(
    	glm::perspective(45.0f, width * 1.0f / height * 1.0f, 0.1f, 100.0f));
}


void initGlfw() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, GL_TRUE);
	window = glfwCreateWindow(800, 800, "OpenGL", nullptr, nullptr); // Windowed
	//glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
}

void initGlew() {
	glewExperimental = GL_TRUE;
	glewInit();
}

int main() {
	initGlfw();
	initGlew();
	
	Cam& cam = Cam::getInstance();
	cam.setPos(glm::vec3(5,5,10));
	cam.setLookAt(glm::vec3(5,5,0));
	cam.setHead(glm::vec3(0,1,0));

	std::vector<Drawable*>* drawables = new std::vector<Drawable*>;
	for(int i = 0; i < 100; i++) {
		for(int j = 0; j < 100; j++) {				
			//tiles.emplace_back(constuctor formal parameters can go here);
			//tiles.emplace_back();
			Tile* t = new Tile();
			drawables->push_back(t);
			t->translate(glm::vec3(0.4 * i, 0.4 * j, 0.0));
		}
	}

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		//cam.translate(glm::vec3(0, 0, -timer.getDelta() * 2));
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for(int i = 0; i < drawables->size(); i++) {
			drawables->at(i)->draw(timer);
		}
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
