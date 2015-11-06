#ifndef Error_hpp_
#define Error_hpp_

#include <iostream>

enum GinesError {
	General = 1000,
};

enum TimeError {
	General = 2000,
};

enum TextError {
	General = 3000,
};

enum GLSLProgramError {
	General = 4000,
};

enum ResourceManagerError {
	General = 5000,
};

enum InputManagerError {
	General = 6000,
};

enum PhysicsError {
	General = 7000,
};

void Error(GinesError error) {
	switch (error)
	{
	case General:
		std::cout << "Gines General Error: " << error << std::endl;
		break;
	default:
		std::cout << "Gines Undefined Error: " << error << std::endl;
		break;
	}
}

void Error(TimeError error) {
	switch (error)
	{
	case General:
		std::cout << "Time General Error: " << error << std::endl;
		break;
	default:
		std::cout << "Time Undefined Error: " << error << std::endl;
		break;
	}
}

void Error(TextError error) {
	switch (error)
	{
	case General:
		std::cout << "Text General Error: " << error << std::endl;
		break;
	default:
		std::cout << "Text Undefined Error: " << error << std::endl;
		break;
	}
}

void Error(GLSLProgramError error) {
	switch (error)
	{
	case General:
		std::cout << "GLSL Program General Error: " << error << std::endl;
		break;
	default:
		std::cout << "GLSL Program Undefined Error: " << error << std::endl;
		break;
	}
}

void Error(ResourceManagerError error) {
	switch (error)
	{
	case General:
		std::cout << "Resource Manager General Error: " << error << std::endl;
		break;
	default:
		std::cout << "Resource Manager Undefined Error: " << error << std::endl;
		break;
	}
}

void Error(InputManagerError error) {
	switch (error)
	{
	case General:
		std::cout << "Input Manager General Error: " << error << std::endl;
		break;
	default:
		std::cout << "Input Manager Undefined Error: " << error << std::endl;
		break;
	}
}

void Error(PhysicsError error) {
	switch (error)
	{
	case General:
		std::cout << "Physics General Error: " << error << std::endl;
		break;
	default:
		std::cout << "Physics Undefined Error: " << error << std::endl;
		break;
	}
}

#endif