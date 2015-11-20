#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <time.h>

class Log
{
public:
	//Trace	-	Only when I would be "tracing" the code and trying to find one part of a function specifically
	//Debug	-	Information that is diagnostically helpful to people more than just developers (IT, sysadmins, etc)
	//Info	-	Generally useful information to log (service start / stop, configuration assumptions, etc). Info I want to always have available but usually dont care about under normal circumstances. This is my out - of - the - box config level
	//Warn	-	Anything that can potentially cause application oddities, but for which I am automatically recoverring(such as switching from a primary to backup server, retrying an operation, missing secondary data, etc)
	//Error	-	Any error which is fatal to the operation but not the service or application (cant open a required file, missing data, etc). These errors will force user (administrator, or direct user) intervention. These are usually reserved (in my apps) for incorrect connection strings, missing services, etc.
	//Fatal	-	Any error that is forcing a shutdown of the service or application to prevent data loss (or further data loss). I reserve these only for the most heinous errors and situations where there is guaranteed to have been data corruption or loss.

	//GrayWizardx - StackOverflow 8.1.2010
	//http://stackoverflow.com/questions/2031163/when-to-use-log-level-warn-vs-error

	enum class Level : std::uint8_t {
		Trace,
		Debug,
		Info,
		Warning,
		Error,
		Fatal
	};

	static void Message(const char* message, Level level)
	{
		time_t rawtime;
		struct tm timeinfo;
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		std::stringstream Msg;
		std::string levelName;
		switch (level)
		{
		case Log::Level::Trace:
			levelName = "Trace";
			Msg << "[" << timeinfo.tm_mday << "." << timeinfo.tm_mon + 1 << "." << timeinfo.tm_year + 1900 << " - " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << "]  " << levelName << ": " << message << std::endl;
			std::cout << Msg.str() << std::endl;
			break;
		case Log::Level::Debug:
			levelName = "Debug";
			Msg << "[" << timeinfo.tm_mday << "." << timeinfo.tm_mon + 1 << "." << timeinfo.tm_year + 1900 << " - " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << "]  " << levelName << ": " << message << std::endl;
			std::cout << Msg.str() << std::endl;
			break;
		case Log::Level::Info:
			levelName = "Info";
			Msg << "[" << timeinfo.tm_mday << "." << timeinfo.tm_mon + 1 << "." << timeinfo.tm_year + 1900 << " - " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << "]  " << levelName << ": " << message << std::endl;
			std::cout << Msg.str() << std::endl;
			break;
		case Log::Level::Warning:
			levelName = "Warning";
			Msg << "[" << timeinfo.tm_mday << "." << timeinfo.tm_mon + 1 << "." << timeinfo.tm_year + 1900 << " - " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << "]  " << levelName << ": " << message << std::endl;
			std::cout << Msg.str() << std::endl;
			break;
		case Log::Level::Error:
			levelName = "Error";
			Msg << "[" << timeinfo.tm_mday << "." << timeinfo.tm_mon + 1 << "." << timeinfo.tm_year + 1900 << " - " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << "]  " << levelName << ": " << message << std::endl;
			std::cout << Msg.str() << std::endl;
			system("pause");
			break;
		case Log::Level::Fatal:
			levelName = "Fatal";
			Msg << "[" << timeinfo.tm_mday << "." << timeinfo.tm_mon + 1 << "." << timeinfo.tm_year + 1900 << " - " << timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec << "]  " << levelName << ": " << message << std::endl;
			std::cout << Msg.str();
			system("pause");
			break;
		default:
			break;
		}

		std::ofstream log_file("MessageLog.txt", std::ios_base::out | std::ios_base::app);
		log_file << Msg.str();
	}
};