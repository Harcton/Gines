#ifndef Error_hpp_
#define Error_hpp_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

enum class GinesError {
	General = 1000,
};

enum class TimeError {
	General = 2000,
};

enum class TextError {
	General = 3000,
};

enum class GLSLProgramError {
	General = 4000,
};

enum class ResourceManagerError {
	General = 5000,
};

enum class InputManagerError {
	General = 6000,
};

enum class PhysicsError {
	General = 7000,
};

enum class ComponentError {
	General = 8000,
};

enum class GameObjectError {
	General						=	9000,
	
	AddComponentGeneral			=	9010,
		MonoComponentFound		=	9011,
		AddingMonoComponent		=	9012,
		
	RemoveComponentGeneral		=	9020,
		ComponentNotFound		=	9021,

	GetComponentGeneral			=	9030,
		ComponentDoesNotExist	=	9031,

	GetComponentsGeneral		=	9040,
		ComponentsDoNotExist	=	9041,
};

//LogError is called from within the Error Function, do not use it.
void logError(std::string errorText)
{
	time_t rawtime;
	struct tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	std::stringstream errorMsg;
	errorMsg << "[" << timeinfo.tm_mday << "." << timeinfo.tm_mon + 1 << "." << timeinfo.tm_year + 1900 << " - " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << "] - " << errorText << std::endl;

	std::cout << errorMsg.str() << std::endl;
	std::ofstream log_file("ErrorLog.txt", std::ios_base::out | std::ios_base::app);
	log_file << errorMsg.str();
}

void Error(GinesError error) {
	std::string errorText;
	switch (error)
	{
	case GinesError::General:
		errorText = "Gines General Error: 1000";
		break;
	default:
		errorText = "Gines Undefined Error";
		break;
	}
	logError(errorText);
}

void Error(TimeError error) {
	std::string errorText;
	switch (error)
	{
	case TimeError::General:
		errorText = "Time General Error: 2000";
		break;
	default:
		errorText = "Time Undefined Error";
		break;
	}
	logError(errorText);
}

void Error(TextError error) {
	std::string errorText;
	switch (error)
	{
	case TextError::General:
		errorText = "Text General Error: 3000";
		break;
	default:
		errorText = "Text Undefined Error";
		break;
	}
	logError(errorText);
}

void Error(GLSLProgramError error) {
	std::string errorText;
	switch (error)
	{
	case GLSLProgramError::General:
		errorText = "GLSL Program General Error: 4000";
		break;
	default:
		errorText = "GLSL Program Undefined Error";
		break;
	}
	logError(errorText);
}

void Error(ResourceManagerError error) {
	std::string errorText;
	switch (error)
	{
	case ResourceManagerError::General:
		errorText = "Resource Manager General Error: 5000";
		break;
	default:
		errorText = "Resource Manager Undefined Error";
		break;
	}
	logError(errorText);
}

void Error(InputManagerError error) {
	std::string errorText;
	switch (error)
	{
	case InputManagerError::General:
		errorText = "Input Manager General Error: 6000";
		break;
	default:
		errorText = "Input Manager Undefined Error";
		break;
	}
	logError(errorText);
}

void Error(PhysicsError error) {
	std::string errorText;
	switch (error)
	{
	case PhysicsError::General:
		errorText = "Physics General Error: 7000";
		break;
	default:
		errorText = "Physics Undefined Error";
		break;
	}
	logError(errorText);
}

void Error(ComponentError error) {
	std::string errorText;
	switch (error)
	{
	case ComponentError::General:
		errorText = "Component General Error: 8000";
		break;
	default:
		errorText = "Component Undefined Error";
		break;
	}
	logError(errorText);
}

void Error(GameObjectError error) {
	std::string errorText;
	switch (error)
	{
	case GameObjectError::General:
		errorText = "GameObject General Error: 9000";
		break;
	case GameObjectError::AddComponentGeneral:
		errorText = "Something happened: 9010";
		break;
	case GameObjectError::MonoComponentFound:
		errorText = "There can only be one instance of a component of the given type: 9011";
		break;
	case GameObjectError::AddingMonoComponent:
		errorText = "Discard previous error, adding MonoComponent: 9012";
		break;
	case GameObjectError::RemoveComponentGeneral:
		errorText = "Something happened: 9020";
		break;
	case GameObjectError::ComponentNotFound:
		errorText = "Component could not be removed, because it was not found: 9021";
		break;
	case GameObjectError::GetComponentGeneral:
		errorText = "Something happened: 9030";
		break;
	case GameObjectError::ComponentDoesNotExist:
		errorText = "No component of the given type exist: 9031";
		break;
	case GameObjectError::GetComponentsGeneral:
		errorText = "Something happened: 9040";
		break;
	case GameObjectError::ComponentsDoNotExist:
		errorText = "No components of the given type exist: 9041";
		break;
	default:
		errorText = "GameObject Undefined Error";
		break;
	}
	logError(errorText); 
}
#endif