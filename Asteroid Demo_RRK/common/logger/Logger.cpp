#include "Logger.h"

static const std::string g_LogString = "[Logger] ";
static const std::string g_InfoString = " -INFO- %s";
static const std::string g_WarningString = " *WARNING* %s";
static const std::string g_ErrorString = " ***ERROR*** %s";

Logger::Logger()
{
	m_File = NULL;
	printMsg(INFO, "Logger has started");
}

Logger::~Logger() 
{
	// Added by Rakesh Msc.Games Programming (module assignment)
	if(m_File)
	{
		m_File->close();
		delete m_File;
		m_File = NULL;
	}
}

void Logger::printMsg(LogSeverity state, const char *msg)
{
	std::string s = g_LogString;
	std::string str_msg(msg);
	str_msg.append("\n\0");
	switch(state)
	{
	case INFO:
		s.append(g_InfoString);
		printf(s.c_str(), str_msg.c_str());
		//cout << g_LogString << g_InfoString << msg << endl;
		break;
	case WARNING:
		s.append(g_WarningString);
		printf(s.c_str(), str_msg.c_str());
		//cout << g_LogString << g_WarningString << msg << endl;
		break;
	case ERRORLOG:
		s.append(g_ErrorString);
		printf(s.c_str(), str_msg.c_str());
		//cout << g_LogString << g_ErrorString << msg << endl;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
//Added by Ram

/*
  pszfileName -> The file name to be created ( if path is not provided it be will created inside
  the working directory
*/
bool Logger::InitializeLog(const char *pszFileName) 
{
	m_File = new std::ofstream();
	m_File->open(pszFileName);
	if(!m_File)
	{
		printMsg(WARNING, "Creation of Log File failed");
		//cout<<"Creation of Log File failed"<<endl;
		return false ;
	}
	return true ;
}

bool Logger::WriteTolog(const char *pszFileName, const int size) 
{
	if(m_File)
	{
		m_File->write(pszFileName, size);
		return true ;
	}
	return false ;
}
//////////////////////////////////////////////////////////////////////////