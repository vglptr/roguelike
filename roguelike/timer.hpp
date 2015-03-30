#include <GLFW/glfw3.h>
#include <iostream>

class Timer {
private:
	Timer(Timer const&) = delete;
    void operator= (Timer const&) = delete;
	Timer() { };
	
	int fps = 0;
	GLfloat delta = 0;
	GLfloat lastTime = 0;
	GLfloat currentTime = 0;
	
public:
	static Timer& getInstance() {
        static Timer instance;
        return instance;
    }
	
	float getDelta() {		
		return delta;
	}
	
	void updateDelta() {
		currentTime = (GLfloat)glfwGetTime();
		delta = currentTime - lastTime;
		lastTime = currentTime;
	}
	
	int getFps() {
		return 1 / delta;
	}

	GLfloat getTime() {
		return (GLfloat)glfwGetTime();
	}
};
