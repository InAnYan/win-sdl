// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#include "logger.h"

using namespace boost::posix_time;

bool duplicateConsole;
ofstream file;
ptime now;

void logInit(string p, bool d)
{
	duplicateConsole = d;
    now = second_clock::local_time();
    //now = time(0);
	//t = localtime(&now);
	//file.open(p+"_"+to_string(t->tm_mday)+"."+to_string(t->tm_mon)+"."+to_string(t->tm_year+1900)+"_"+to_string(t->tm_hour)+":"+to_string(t->tm_min)+":"+to_string(t->tm_sec)+".log");
	file.open(p+"_"+to_string(now.date().year())+"."+to_string(now.date().month())+"."+to_string(now.date().day())+"_"+to_string(now.time_of_day().hours())+"."+to_string(now.time_of_day().minutes())+"."+to_string(now.time_of_day().seconds())+".log");
	file << "Logger created" << endl;
}

void logDeInit()
{
	file.close();
}

void logInfo(string text)
{
    now = second_clock::local_time();
	if(duplicateConsole == true)
	{
		cout << "[" << now.time_of_day().hours() << ":" << now.time_of_day().minutes() << ":" << now.time_of_day().seconds() << "] INFO: " << text << endl;
	}
	file << "[" << now.time_of_day().hours() << ":" << now.time_of_day().minutes() << ":" << now.time_of_day().seconds() << "] INFO: " << text << endl;
}

void logWarning(string text)
{
	now = second_clock::local_time();
	if(duplicateConsole == true)
	{
		cout << "[" << now.time_of_day().hours() << ":" << now.time_of_day().minutes() << ":" << now.time_of_day().seconds() << "] WARNING: " << text << endl;
	}
	file << "[" << now.time_of_day().hours() << ":" << now.time_of_day().minutes() << ":" << now.time_of_day().seconds() << "] WARNING: " << text << endl;
}

void logError(string text)
{
	now = second_clock::local_time();
	if(duplicateConsole == true)
	{
		cout << "[" << now.time_of_day().hours() << ":" << now.time_of_day().minutes() << ":" << now.time_of_day().seconds() << "] ERROR: " << text << endl;
	}
	file << "[" << now.time_of_day().hours() << ":" << now.time_of_day().minutes() << ":" << now.time_of_day().seconds() << "] ERROR: " << text << endl;
}

void logDebug(string text)
{
	//now = time(0);
	//t = localtime(&now);
	//if(duplicateConsole == true)
	//{
	//	cout << "[" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << "] DEBUG: " << text << endl;
	//}
	//file << "[" << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << "] DEBUG: " << text << endl;
	now = second_clock::local_time();
	if(duplicateConsole == true)
	{
		cout << "[" << now.time_of_day().hours() << ":" << now.time_of_day().minutes() << ":" << now.time_of_day().seconds() << "] DEBUG: " << text << endl;
	}
	file << "[" << now.time_of_day().hours() << ":" << now.time_of_day().minutes() << ":" << now.time_of_day().seconds() << "] DEBUG: " << text << endl;
}
