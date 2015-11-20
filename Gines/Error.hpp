#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

enum class GinesLog {
	GeneralError = 1000,
};

enum class TimeLog {
	GeneralError = 2000,
};

enum class TextLog {
	GeneralError = 3000,
};

enum class GLSLProgramLog {
	GeneralError = 4000,
};

enum class ResourceManagerLog {
	GeneralError = 5000,
};

enum class InputManagerLog {
	GeneralError = 6000,
};

enum class PhysicsLog {
	GeneralError = 7000,
};

enum class ComponentLog {
	GeneralError = 8000,
};

enum class GameObjectLog {
	GeneralError				=	9000,
	
	AddComponentGeneral			=	9010,
		MonoComponentFound		=	9011,
		
	RemoveComponentGeneral		=	9020,
		ComponentNotFound		=	9021,

	GetComponentGeneral			=	9030,
		ComponentDoesNotExist	=	9031,

	GetComponentsGeneral		=	9040,
		ComponentsDoNotExist	=	9041,
};

namespace Message
{
	//LogMessage is called from within the Log Function, do not use it.
	//Level 1 = Error, Level 2 = Warning, Level 3 = Log
	void logMessage(const std::string& message, int level)
	{
		time_t rawtime;
		struct tm timeinfo;
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		std::stringstream Msg;
		if (level == 1) {
			Msg << "[" << timeinfo.tm_mday << "." << timeinfo.tm_mon + 1 << "." << timeinfo.tm_year + 1900 << " - " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << "] - " << "ERROR:   " << message << std::endl;
		}
		else if (level == 2) {
			Msg << "[" << timeinfo.tm_mday << "." << timeinfo.tm_mon + 1 << "." << timeinfo.tm_year + 1900 << " - " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << "] - " << "WARNING: " << message << std::endl;
		}
		else {
			Msg << "[" << timeinfo.tm_mday << "." << timeinfo.tm_mon + 1 << "." << timeinfo.tm_year + 1900 << " - " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << "] - " << "LOG:     " << message << std::endl;
		}
		std::cout << Msg.str() << std::endl;
		std::ofstream log_file("ErrorLog.txt", std::ios_base::out | std::ios_base::app);
		log_file << Msg.str();
		if (level == 1) { system("pause"); }
	}

	void Log(GinesLog error) {
		std::string message;
		int level;
		switch (error)
		{
		case GinesLog::GeneralError:
			message = "Gines General Error: 1000";
			level = 1;
			break;
		default:
			message = "Gines Undefined Error";
			level = 1;
			break;
		}
		logMessage(message, level);
	}

	void Log(TimeLog error) {
		std::string message;
		int level;
		switch (error)
		{
		case TimeLog::GeneralError:
			message = "Time General Error: 2000";
			level = 1;
			break;
		default:
			message = "Time Undefined Error";
			level = 1;
			break;
		}
		logMessage(message, level);
	}

	void Log(TextLog error) {
		std::string message;
		int level;
		switch (error)
		{
		case TextLog::GeneralError:
			message = "Text General Error: 3000";
			level = 1;
			break;
		default:
			message = "Text Undefined Error";
			level = 1;
			break;
		}
		logMessage(message, level);
	}

	void Log(GLSLProgramLog error) {
		std::string message;
		int level;
		switch (error)
		{
		case GLSLProgramLog::GeneralError:
			message = "GLSL Program General Error: 4000";
			level = 1;
			break;
		default:
			message = "GLSL Program Undefined Error";
			level = 1;
			break;
		}
		logMessage(message, level);
	}

	void Log(ResourceManagerLog error) {
		std::string message;
		int level;
		switch (error)
		{
		case ResourceManagerLog::GeneralError:
			message = "Resource Manager General Error: 5000";
			level = 1;
			break;
		default:
			message = "Resource Manager Undefined Error";
			level = 1;
			break;
		}
		logMessage(message, level);
	}

	void Log(InputManagerLog error) {
		std::string message;
		int level;
		switch (error)
		{
		case InputManagerLog::GeneralError:
			message = "Input Manager General Error: 6000";
			level = 1;
			break;
		default:
			message = "Input Manager Undefined Error";
			level = 1;
			break;
		}
		logMessage(message, level);
	}

	void Log(PhysicsLog error) {
		std::string message;
		int level;
		switch (error)
		{
		case PhysicsLog::GeneralError:
			message = "Physics General Error: 7000";
			level = 1;
			break;
		default:
			message = "Physics Undefined Error";
			level = 1;
			break;
		}
		logMessage(message, level);
	}

	void Log(ComponentLog error) {
		std::string message;
		int level;
		switch (error)
		{
		case ComponentLog::GeneralError:
			message = "Component General Error: 8000";
			level = 1;
			break;
		default:
			message = "Component Undefined Error";
			level = 1;
			break;
		}
		logMessage(message, level);
	}

	void Log(GameObjectLog error) {
		std::string message;
		int level;
		switch (error)
		{
		case GameObjectLog::GeneralError:
			message = "GameObject General Error: 9000";
			level = 1;
			break;
		case GameObjectLog::AddComponentGeneral:
			message = "Something happened: 9010";
			level = 2;
			break;
		case GameObjectLog::MonoComponentFound:
			message = "There can only be one instance of a component of the given type: 9011";
			level = 2;
			break;
		case GameObjectLog::RemoveComponentGeneral:
			message = "Something happened: 9020";
			level = 2;
			break;
		case GameObjectLog::ComponentNotFound:
			message = "Component could not be removed, because it was not found: 9021";
			level = 2;
			break;
		case GameObjectLog::GetComponentGeneral:
			message = "Something happened: 9030";
			level = 2;
			break;
		case GameObjectLog::ComponentDoesNotExist:
			message = "No component of the given type exist: 9031";
			level = 3;
			break;
		case GameObjectLog::GetComponentsGeneral:
			message = "Something happened: 9040";
			level = 2;
			break;
		case GameObjectLog::ComponentsDoNotExist:
			message = "No components of the given type exist: 9041";
			level = 3;
			break;
		default:
			message = "GameObject Undefined Error";
			level = 1;
			break;
		}
		logMessage(message, level);
	}
}