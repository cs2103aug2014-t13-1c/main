#include "TimeData.h"

Time::Time(void)
{
	hour=0;
	minutes=0;
	period="";
}

Time::Time(int hour, int minutes, string period)
{
	hour = hour;
	minutes = minutes;
	period = period;
}

void Time::setPeriod(string period)
{
	this->period=period;
}

string Time::getPeriod()
{
	return period;
}

void Time::setHour(int hour)
{
	this->hour=hour;
}

int Time::getHour()
{
	return hour;
}

void Time::setMinutes(int minutes)
{
	this->minutes=minutes;
}

int Time::getMinutes()
{
	return minutes;
}

bool Time::isGreaterThan(Time time2)
{
	bool flag;
	int temphour1=0,temphour2=0;
	if(this->period=="am" && time2.period=="pm")
		flag=false;
	else if(this->period=="pm" && time2.period=="am")
		flag=true;
	else
	{
		if(this->hour==12)
			temphour1=0;
		else 
			temphour1=this->hour;
		
		if(time2.hour==12)
			temphour2=0;
		else 
			temphour2=time2.hour;
		
		if( temphour1 > temphour2)
			flag=true;
		else if(temphour1 < temphour2)
			flag=false;
		else if(this->minutes > time2.minutes)
			flag=true;
		else if(this->minutes <= time2.minutes)
			flag=false;
	}

	return flag;

}

string Time::formatTime()
{
	int hour=getHour(), min= getMinutes();
	string period=getPeriod();
	stringstream result;
	
	result << hour;
	if (min!=0)
	{
		result << ".";
	
		if (min<10)
			result <<'0';
		result << min;
	}
	return result.str();
}

string Time::formatCompleteTime(Time Obj)
{
	
	string formattedTime =formatTime();
	if (Obj.getPeriod()!="")
	{
		formattedTime+=" to ";
		formattedTime+=Obj.formatTime();
	}
	return formattedTime;
}

void Time::timeStringToObject(string time)
{
	vector<string> tokenizedTime=tokenizeTime(time);
	if(tokenizedTime.size()==2) //4pm, 5pm
	{
		if(hasPeriod(tokenizedTime)==1)
		{
			int hour=atoi(tokenizedTime[0].c_str());
			string period=tokenizedTime[1];

			setHour(hour);
			setPeriod(period);
		}
	}
	else if(tokenizedTime.size()==3) //430pm, 530pm
	{
		if(hasPeriod(tokenizedTime)==2)
		{
			int hour=atoi(tokenizedTime[0].c_str());
			int minutes=atoi(tokenizedTime[1].c_str());
			string am_pm=tokenizedTime[2];

			setHour(hour);
			setMinutes(minutes);
			setPeriod(period);
		}
	}
}

bool Time::isValidTime()
{
	bool flag=true;
	if(getHour()<1 || getHour()>12)
		flag=false;
	if(getMinutes()<0 || getMinutes()>59)
		flag=false;
	return flag;
}

int Time::hasPeriod(vector<string> tokenizedTime)
{
	for(unsigned int i=0;i<tokenizedTime.size();i++)
	{
		if((tokenizedTime[i] == "am") || (tokenizedTime[i] == "pm"))
			return i;
	}
	return -1;
}

vector<string> Time::tokenizeTime(string timeToTokenize)
{
	vector<string> tokenizedTime;
	char *pch, *str;
	str = new char [timeToTokenize.size()+1];
	strcpy(str, timeToTokenize.c_str());
	string tempTime;

	pch = strtok(str,":. ");
	while(pch!=NULL)
	{
		tempTime=pch;
		if(tempTime.size()>2)
		{
			int index=findPeriod(tempTime);
			if(index!=-1)
			{
				tokenizedTime.push_back(tempTime.substr(0,index));
				tokenizedTime.push_back(tempTime.substr(index,2));
			}
			else
				tokenizedTime.push_back(tempTime);
		}
		else
			tokenizedTime.push_back(tempTime);
		pch=strtok(NULL,":. ");
	}
	return tokenizedTime;
}

int Time::findPeriod(string timeToBeTested)
{
	int pos=timeToBeTested.find("am");
	int pos2=timeToBeTested.find("pm");
	
	if(pos>-1)
		return pos;
	else if (pos2>-1)
		return pos2;
	return -1;
}

void Time::incrementTime(int mins)
{
	assert(mins>=0);
	for(int i=1;i<=mins;i++)
	{
		minutes++;
		if (minutes==60)
		{
			hour++;
			if(hour==12)
			{
				if (period=="am")
					period="pm";
	
				else 
				{
					period="am";
					hour=0;
				}
			}
			minutes = 0;
		}
	}
	return;
}

bool Time::isEqual(Time Obj)
{
	if (period==Obj.getPeriod())
	{
		if (minutes ==Obj.getMinutes() && hour==Obj.getHour())
			return true;
	}
	return false;
}

Time::~Time(void)
{
}
