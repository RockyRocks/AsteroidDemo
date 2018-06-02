#ifndef __LOGGER_H
#define __LOGGER_H

#include <iostream>
#include <strstream>
#include <fstream>
#include <string>
#include "..\utils\Singleton.h"


static const enum LogSeverity
{
	INFO,
	WARNING,
	ERRORLOG
};

// Logger Description
//
// A simple logger that will output a formatted message depending on the severity
// specified.
//
// Usage:
//
// Logger::GetInstance()->printMsg(INFO, "Test message");
//
// Print to file by first initializing the log and then using the "WriteToLog" function
class Logger : public Singleton<Logger>
{
	friend Singleton<Logger>;
public:
	void printMsg(LogSeverity severity, const char * msg);
	//// Added by RAM
	bool InitializeLog(const char *pszFileName) ;
	bool WriteTolog(const char *pszFileName, const int size) ;


private:
	Logger();
	~Logger();
	Logger(const Logger&);
	Logger& operator=(const Logger);
	std::ofstream *m_File; // Added by RAM
};

#endif
