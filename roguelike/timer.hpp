#include <GLFW/glfw3.h>
#include <iostream>

class Timer {
private:
	int fps = 0;
	GLfloat delta = 0;
	GLfloat lastTime = 0;
	GLfloat currentTime = 0;
	
public:
	float getDelta() {
		currentTime = (GLfloat)glfwGetTime();
		delta = currentTime - lastTime;
		lastTime = currentTime;
		return delta;
	}
	
	int getFps() {
		return 1 / delta;
	}
};
