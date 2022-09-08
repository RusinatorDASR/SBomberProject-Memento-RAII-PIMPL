#pragma once
#include <string>
#include <fstream>

using namespace std;
class FileLogger
{
public:

	FileLogger(string str);
	~FileLogger();

	string GetCurDateTime();

	void __fastcall WriteToLog(const std::string& str);

	void __fastcall WriteToLog(const std::string& str, int n);

	void __fastcall WriteToLog(const std::string& str, double d);

private:
	ofstream fout;
};

