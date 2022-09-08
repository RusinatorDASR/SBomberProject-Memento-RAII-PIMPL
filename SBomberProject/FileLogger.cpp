#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h> 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

#include "FileLogger.h"

FileLogger::FileLogger(string str) {
	fout.open(str);
}

FileLogger::~FileLogger() {
	fout.close();
}


string FileLogger::GetCurDateTime()
{
	auto cur = std::chrono::system_clock::now();
	time_t time = std::chrono::system_clock::to_time_t(cur);
	char buf[64] = { 0 };
	ctime_s(buf, 64, &time);
	buf[strlen(buf) - 1] = '\0';
	return string(buf);
}

void __fastcall FileLogger::WriteToLog(const string& str)
{
	if (fout.is_open())
	{
		fout << GetCurDateTime() << " - " << str << endl;
	}
}

void __fastcall FileLogger::WriteToLog(const string& str, int n)
{
	if (fout.is_open())
	{
		fout << GetCurDateTime() << " - " << str << n << endl;
	}
}

void __fastcall FileLogger::WriteToLog(const string& str, double d)
{
	if (fout.is_open())
	{
		fout << GetCurDateTime() << " - " << str << d << endl;
	}
}