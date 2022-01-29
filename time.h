#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

class Time {
public:
	static float currentTime;
	static float lastTime;
	static float deltaTime;

	static void calc() {
		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		if (deltaTime >= 1.0f) {
			lastTime = currentTime;
		}
	}
private:
	Time();
};

#endif