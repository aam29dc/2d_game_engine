#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>
#include <iostream>

class Time {
public:
	static float current;
	static float last;
	static float delta;

	/*static void calc() {
		currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
	}*/

	static void print() {
		std::cout << "cT: " << current << "\n" << "dT: " << delta << "\n" << "lT: " << last << "\n\n";
	}
private:
	Time();
};

#endif