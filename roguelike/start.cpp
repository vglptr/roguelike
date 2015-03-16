#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include "timer.hpp"
#include "vertexgenerator.hpp"
#include "tile.hpp"
#include <vector>

GLFWwindow* window;

void initGlfw() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	window = glfwCreateWindow(800, 800, "OpenGL", nullptr, nullptr); // Windowed
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
	Timer timer;
	Cam& cam = Cam::getInstance();
	cam.setPos(glm::vec3(4,3,3));
	cam.setLookAt(glm::vec3(0,0,0));
	cam.setHead(glm::vec3(0,1,0));

	std::vector<Tile> tiles;
	//std::deque<Tile> tiles;
	for(int i = 0; i < 10; i++) {
		//tiles.emplace_back(constuctor formal parameters);
		//dont create temp instance here
		//usage: tiles.back().tranlsate()...
		//nothing from below here
		Tile tile;
		tile.translate(glm::vec3(0.4 * i, 0.0, 0.0));
		//use dequeue instead, that one does not call ~Tile, use emplace
		//tiles.emplace_back()
		
		tiles.push_back(tile);
	}

	
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		//cam.translate(glm::vec3(timer.getDelta(), 0, 0));
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for(int j = 0; j < 10; j++) {
			tiles.at(j).draw(timer);
		}
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
