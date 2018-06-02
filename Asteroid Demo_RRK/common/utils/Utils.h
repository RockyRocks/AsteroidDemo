#ifndef __UTILS_H
#define __UTILS_H

#include <string>
#include <iostream>
#include <sstream>
#include <direct.h>
#include <algorithm>
#include <assert.h>

namespace Utils
{
	static void clamp(float value, float min, float max)
	{
		if(value > max)
		{
			value = max;
		}
		else if(value < min)
		{
			value = min;
		}
	}

	static std::string numberToString(const int i)
	{
		std::string s;
		std::stringstream out;
		out << i;
		s = out.str();

		return s;
	}

	static std::string numberToString(const float f)
	{
		std::string s;
		std::stringstream out;
		out << f;
		s = out.str();

		return s;
	}

	static void toLowerCase(std::string &str)
	{
		std::transform(str.begin(), str.end(), str.begin(), tolower);
	}

	static void toUpperCase(std::string &str)
	{
		std::transform(str.begin(), str.end(), str.begin(), toupper);
	}

	static void trimString(std::string in, std::string out)
	{
		std::string str = in;
		size_t found;
		found = str.find_last_not_of(" ");
		if (found != std::string::npos)
			str.erase(found+1);
		else
			str.clear();            // str is all whitespace

		out = str;
	}

	static std::string getRootDir()
	{
		char * progdir;
		progdir = _getcwd(NULL, _MAX_PATH);

		assert(progdir);
		
		std::string shdir;
		shdir.assign(progdir);
		shdir.append("\\");

		return shdir;
	}
	
	static std::string getDir(const char *queryDir)
	{
		char * progdir;
		progdir = _getcwd(NULL, _MAX_PATH);

		assert(progdir);
		
		std::string shdir;
		shdir.assign(progdir);
		shdir.append(queryDir);

		return shdir;
	}

	static std::string getResourcesDir(const char *queryDir)
	{
		char * progdir;
		progdir = _getcwd(NULL, _MAX_PATH);

		assert(progdir);
		
		std::string shdir;
		shdir.assign(progdir);
		shdir.append("\\resources\\");
		shdir.append(queryDir);

		return shdir;
	}
};
#endif