//@author A0086002U
#ifndef _TIME_H
#define _TIME_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std;

class Time
{
public:
	Time(void);
	Time(int, int,string);

	~Time(void);

	int getHour();
	int getMinutes();
	void setHour(int);
	void setMinutes(int);
	string getPeriod();
	void setPeriod(string);
	bool isGreaterThan(Time);
	string formatTime();
	void timeStringToObject(string time);
	bool isValidTime();
	string formatCompleteTime(Time Obj);
	void incrementTime(int mins);
	bool isEqual(Time Obj);

private:
	int hour;
	int minutes;
	string period;

	int findPeriod(string timeToBeTested);
	int hasPeriod(vector<string> tokenizedTime);
	vector<string> tokenizeTime(string timeToTokenize);


};

#endif
