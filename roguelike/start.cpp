#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include "timer.hpp"
#include "vertexgenerator.hpp"
#include "tile.hpp"

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
	glfwSwapInterval(0);
}

void initGlew() {
	glewExperimental = GL_TRUE;
	glewInit();
}

int main() {
	initGlfw();
	initGlew();
	Timer timer;
	Tile tile(0.5, 0.5, 0.5);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		tile.draw(timer);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
