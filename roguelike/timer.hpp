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
		//even if getDelta() is not called for a long time we dont want to make it huge
		if (delta > 1.0f / 30) {
			delta = 1.0f / 30;
		}
		return delta;
	}
	
	int getFps() {
		return 1 / delta;
	}

	GLfloat getTime() {
		return (GLfloat)glfwGetTime();
	}
};
