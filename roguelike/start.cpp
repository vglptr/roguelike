#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include "timer.hpp"
#include "vertexgenerator.hpp"
#include "tile.hpp"
#include "box.hpp"
#include <deque>
#include <vector>

GLFWwindow* window;
int width;
int height;
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float mouseSpeed = 0.5f;
glm::vec3 camDirection;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W) {
		Cam::getInstance().translate(glm::vec3(camDirection * Timer::getInstance().getDelta() * 40.0f));
	}
	if (key == GLFW_KEY_S) {
		Cam::getInstance().translate(glm::vec3(-camDirection * Timer::getInstance().getDelta() * 40.0f));
	}
	if (key == GLFW_KEY_A) {
		Cam::getInstance().translate(glm::vec3(camDirection * Timer::getInstance().getDelta() * 40.0f));
	}
	if (key == GLFW_KEY_D) {
		Cam::getInstance().translate(glm::vec3(camDirection * Timer::getInstance().getDelta() * 40.0f));
	}
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {	
	horizontalAngle += mouseSpeed * Timer::getInstance().getDelta() * float(width / 2 - xpos );
	verticalAngle   += mouseSpeed * Timer::getInstance().getDelta() * float(height / 2 - ypos );
	camDirection = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle));
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f));
	glm::vec3 up = glm::cross( right, camDirection );
	Cam::getInstance().setHead(up);	
	Cam::getInstance().setLookAt(Cam::getInstance().getPosition() + camDirection);
	glfwSetCursorPos(window, width/2, height/2);
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
	width = w;
	height = h;
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
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	glfwGetWindowSize(window, &width, &height);
}

void initGlew() {
	glewExperimental = GL_TRUE;
	glewInit();
}

int main() {
	initGlfw();
	initGlew();
	
	Cam& cam = Cam::getInstance();
	cam.setPos(glm::vec3(0,0,10));
	cam.setLookAt(glm::vec3(0,0,0));
	cam.setHead(glm::vec3(0,1,0));

	std::vector<Drawable*> drawables;
	std::vector<Drawable*> drawables2;
	drawables.reserve(10 * 10 * 2);
	
	
	
	
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {				
			Box* b = new Box();
			drawables2.push_back(b);
			b->translate(glm::vec3(0.4 * i, 0.4 * j, 10.0));
		}
	}
	
	//last type gets drawn...opengl buffer overwritten?
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {				
			//tiles.emplace_back(constuctor formal parameters can go here);
			//tiles.emplace_back();
			Tile* t = new Tile();
			drawables.push_back(t);
			t->translate(glm::vec3(0.4 * i, 0.4 * j, 0.0));
		}
	}
	

	while (!glfwWindowShouldClose(window)) {
		Timer::getInstance().updateDelta();
		glfwPollEvents();
		
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		//cam.translate(glm::vec3(0, 0, Timer::getInstance().getDelta() * 2));
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		for(int i = 0; i < drawables.size(); i++) {
			drawables.at(i)->draw(Timer::getInstance().getDelta());
			drawables2.at(i)->draw(Timer::getInstance().getDelta());
		}
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
