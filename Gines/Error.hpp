#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <time.h>

//Trace	- Only when I would be "tracing" the code and trying to find one part of a function specifically
//Debug	- Information that is diagnostically helpful to people more than just developers (IT, sysadmins, etc)
//Info	- Generally useful information to log (service start / stop, configuration assumptions, etc). Info I want to always have available but usually dont care about under normal circumstances. This is my out - of - the - box config level
//Warn	- Anything that can potentially cause application oddities, but for which I am automatically recoverring(such as switching from a primary to backup server, retrying an operation, missing secondary data, etc)
//Error	- Any error which is fatal to the operation but not the service or application (cant open a required file, missing data, etc). These errors will force user (administrator, or direct user) intervention. These are usually reserved (in my apps) for incorrect connection strings, missing services, etc.
//Fatal	- Any error that is forcing a shutdown of the service or application to prevent data loss (or further data loss). I reserve these only for the most heinous errors and situations where there is guaranteed to have been data corruption or loss.

//GrayWizardx - StackOverflow 8.1.2010
//http://stackoverflow.com/questions/2031163/when-to-use-log-level-warn-vs-error

namespace gines
{
	enum class Message : std::uint32_t {
		//Trace - Only when I would be "tracing" the code and trying to find one part of a function specifically
		Trace,
		//Debug - Information that is diagnostically helpful to people more than just developers (IT, sysadmins, etc)
		Debug,
		//Info - Generally useful information to log (service start / stop, configuration assumptions, etc). Info I want to always have available but usually dont care about under normal circumstances. This is my out - of - the - box config level
		Info,
		//Warn - Anything that can potentially cause application oddities, but for which I am automatically recoverring(such as switching from a primary to backup server, retrying an operation, missing secondary data, etc)
		Warning,
		//Error - Any error which is fatal to the operation but not the service or application (cant open a required file, missing data, etc). These errors will force user (administrator, or direct user) intervention. These are usually reserved (in my apps) for incorrect connection strings, missing services, etc.
		Error,
		//Fatal - Any error that is forcing a shutdown of the service or application to prevent data loss (or further data loss). I reserve these only for the most heinous errors and situations where there is guaranteed to have been data corruption or loss.
		Fatal
	};

	static void logMessage(const char* message, Message level, const char* file, int line)
	{
		//Save the current time
		time_t rawtime;
		struct tm timeinfo;
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		char* tempMessage = (char*)message;
		std::uint32_t i = 0;
		while (tempMessage[i] != NULL) {
			if (tempMessage[i] == '\n') { tempMessage[i] = NULL; }
			i++;
		}

		std::stringstream Msg;
		std::ofstream log_file("MessageLog.txt", std::ios_base::out | std::ios_base::app);

		//Format time so it's uniform in all cases
		if (timeinfo.tm_mday < 10) { Msg << "[0" << timeinfo.tm_mday << "."; }
		else { Msg << "[" << timeinfo.tm_mday << "."; }
		if (timeinfo.tm_mon < 9) { Msg << "0" << timeinfo.tm_mon + 1 << "." << timeinfo.tm_year + 1900 << " - "; }
		else { Msg << timeinfo.tm_mon + 1 << "." << timeinfo.tm_year + 1900 << " - "; }
		if (timeinfo.tm_hour < 10) { Msg << "0" << timeinfo.tm_hour << ":"; }
		else { Msg << timeinfo.tm_hour << ":"; }
		if (timeinfo.tm_min < 10) { Msg << "0" << timeinfo.tm_min << ":"; }
		else { Msg << timeinfo.tm_min << ":"; }
		if (timeinfo.tm_sec < 10) { Msg << "0" << timeinfo.tm_sec << "]"; }
		else { Msg << timeinfo.tm_sec << "]"; }

		//Print message and depending on the case do something else
		//Filename and linenumber will be removed from some of the messages, but for debugging purposes will be left for now
		switch (level)
		{
		case gines::Message::Trace:
			Msg << "\tTrace: " << tempMessage << "\n\t\t\tFile: " << file << "\n\t\t\tLine: " << line << std::endl;
			std::cout << Msg.str();
			break;
		case gines::Message::Debug:
			Msg << "\tDebug: " << tempMessage << "\n\t\t\tFile: " << file << "\n\t\t\tLine: " << line << std::endl;
			std::cout << Msg.str();
			break;
		case gines::Message::Info:
			Msg << "\tInfo: " << tempMessage << "\n\t\t\tFile: " << file << "\n\t\t\tLine: " << line << std::endl;
			std::cout << Msg.str();
			break;
		case gines::Message::Warning:
			Msg << "\tWarning: " << tempMessage << "\n\t\t\tFile: " << file << "\n\t\t\tLine: " << line << std::endl;
			std::cout << Msg.str();
			break;
		case gines::Message::Error:
			Msg << "\tError: " << tempMessage << "\n\t\t\tFile: " << file << "\n\t\t\tLine: " << line << std::endl;
			std::cout << Msg.str();

			//Handle error
			//Coming in a long time ago
			//Into a galaxy near you
			system("pause");
			break;
		case gines::Message::Fatal:
			Msg << "\tFatal: " << message << "\n\t\t\tFile: " << file << "\n\t\t\tLine: " << line << std::endl;
			std::cout << Msg.str();

			system("pause");

			//Save message to MessageLog.txt
			log_file << Msg.str();
			log_file.close();

			std::terminate();
			break;
		default:
			break;
		}

		//Save message to MessageLog.txt
		log_file << Msg.str();
		log_file.close();
	}
}

#define Message(message, messageLevel) gines::logMessage(message, messageLevel, __FILE__, __LINE__)