#include "pugixml.hpp"
#include <Windows.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <algorithm>


using namespace std;

multimap <string, int> stopTram;
set<string> tramR;
multimap <string, int> stopBus;
set<string> busR;
multimap <string, int> stopTrolleybus;
set<string> trolleybusR;
string zeroName;
vector<pair<string, int>> streets;

struct xmlTab 
{
	string typeOfTransport;
	bool stop = false;
	string site;
	string firstSite;
	string secondSite;
	double coordinatesOne = 0;
	double coordinatesTwo = 0;
};

vector<xmlTab> container;
void mySplit(string str, string& subStr1, string& subStr2)
{
	auto sp = str.find(',');
	for (auto i = 0; i < str.length(); i++) 
	{
		if (i < sp)
			subStr1.push_back(str[i]);
		if (i > sp)
			subStr2.push_back(str[i]);
	}
}

void Parsing(string str, int index, int indexOfStop)
{
	if (index % 8 == 1)
		container[indexOfStop].typeOfTransport = str;
	if (index % 8 == 2)
	{
		if (indexOfStop == 0)
			zeroName = str;
		else
			container[indexOfStop].stop = (str == zeroName);
	}
	if (index % 8 == 5)
	{
		int flag;
		container[indexOfStop].site = str;
		string subStr1, subStr2;
		mySplit(str, subStr1, subStr2);
		container[indexOfStop].firstSite = subStr1;
		container[indexOfStop].secondSite = subStr2;
		flag = 0;
		if (container[indexOfStop].stop == 1)
		{
			if (!streets.empty())
				for (auto i = 0; i < streets.size(); i++)
					if (streets[i].first == container[indexOfStop].firstSite && (!container[indexOfStop].firstSite.empty()))
					{
						flag = 1;
						streets[i].second += 1;
					}
					else if (streets[i].first == container[indexOfStop].secondSite && (!container[indexOfStop].firstSite.empty()))
					{
						flag = 2;
						streets[i].second += 1;
					}
			    if (flag == 0)
					streets.push_back(make_pair(container[indexOfStop].firstSite, 1));
				else
				{
					streets.push_back(make_pair(container[indexOfStop].firstSite, 1));
					streets.push_back(make_pair(container[indexOfStop].secondSite, 1));
				}
		}
	}
	if (index % 8 == 6)
	{
		string buffer;
		buffer.clear();
		if (container[indexOfStop].stop == 1)
		{
			if (indexOfStop < 888)
			{
				for (auto value : str)
				{
					if (value != ',')
						buffer.push_back(value);
					else
					{
						stopTram.insert(make_pair(buffer, indexOfStop));
						tramR.insert(buffer);
						buffer.clear();
					}
				}
				stopTram.insert(make_pair(buffer, indexOfStop));
				tramR.insert(buffer);
				buffer.clear();
			}
			else if (indexOfStop >= 888 && indexOfStop < 2080)
			{
				for (auto value : str)
					if (value != ',')
						buffer.push_back(value);
					else
					{
						stopTrolleybus.insert(make_pair(buffer, indexOfStop));
						trolleybusR.insert(buffer);
						buffer.clear();
					}
				stopTrolleybus.insert(make_pair(buffer, indexOfStop));
				trolleybusR.insert(buffer);
				buffer.clear();
			}
			else
			{
				for (auto value : str)
					if (value != ',')
						buffer.push_back(value);
					else
					{
						stopBus.insert(make_pair(buffer, indexOfStop));
						busR.insert(buffer);
						buffer.clear();
					}
				stopBus.insert(make_pair(buffer, indexOfStop));
				busR.insert(buffer);
				buffer.clear();
			}
		}
	}
	if (index % 8 == 7)
	{
		double coordinates1, coordinates2;
		string subStr1, subStr2;
		mySplit(str, subStr1, subStr2);
		coordinates1 = stof(subStr1);
		coordinates2 = stof(subStr2);
		container[indexOfStop].coordinatesOne = coordinates1;
		container[indexOfStop].coordinatesTwo = coordinates2;
	}
}

double lenght(double firstStop, double secondStop)
{
	double firstSin;
	firstSin = sin((container[secondStop].coordinatesOne - container[firstStop].coordinatesOne) / 2);
	double secondSin;
	secondSin = sin((container[secondStop].coordinatesTwo - container[firstStop].coordinatesTwo) / 2);
	return asin(sqrt(firstSin * firstSin + secondSin * secondSin * cos(container[firstStop].coordinatesOne) * cos(container[secondStop].coordinatesOne)));
}

int main()
{
	SetConsoleOutputCP(1251);
	int index, indexOfStop = 0;
	container.resize(8000);
	
	//******************************************************UTF**********************************************************************
	system("chcp 65001");
	
	
	//*******************************************************OPENXML****************************************************************
	pugi::xml_document input;
	if(!input.load_file(R"(C:\Users\root\source\repos\homework3\homework3\input.xml)")) return -1;
	
	
	
	//*******************************************************INPUT*******************************************************************
	for (pugi::xml_node tools = input.child("dataset").child("transport_station"); tools; tools = tools.next_sibling()) 
	{
		index = 0;
		for (pugi::xml_node tool = tools.first_child(); tool; tool = tool.next_sibling())
		{
			string s = tool.child_value();
			Parsing(s, index, indexOfStop);
			index++;
		}
		indexOfStop++;
	}



	//********************************************************TASK1**************************************************************************
	string route;
	int countOfStop = 0;
	cout << "Task 1 :" << endl;
	for (auto value : busR)
		if (countOfStop < stopBus.count(value))
		{
			countOfStop = stopBus.count(value);
			route = value;
		}
	cout << "Number of route bus: " << route << " - Quantity of bus stop: " << countOfStop << endl;
	countOfStop = 0;
	for (auto value : trolleybusR)
		if (countOfStop < stopTrolleybus.count(value))
		{
			countOfStop = stopTrolleybus.count(value);
			route = value;
		}
	cout << "Number of route trolleybus: " << route << " - Quantity of trolleybus stop: " << countOfStop << endl;
	countOfStop = 0;
	for (auto value : tramR)
		if (countOfStop < stopTram.count(value))
		{
			countOfStop = stopTram.count(value);
			route = value;
		}
	cout << "Number of route tram: " << route << " - Quantity of tram stop: " << countOfStop << endl;
	
	

	//*********************************************************TASK2***************************************************************************
	cout << "Task 2: " << endl;
	double thisLenght = 0, maxLenght = 0;
	string rout;
	double tempValue;
	for (auto value : busR)
	{
		multimap<string, int>::iterator iter = stopBus.find(value);
		if (iter != stopBus.end())
			while (iter->first == value)
			{
				tempValue = iter->second;
				iter++;
				if (iter != stopBus.end())
					if (iter->first == value)
						thisLenght += lenght(tempValue, iter->second);
					else
						continue;
				else
					break;
			}
		if (maxLenght < thisLenght)
		{
			maxLenght = thisLenght;
			rout = value;
		}
		thisLenght = 0;
	}
	cout << "Rout with max lenght for bus - " << rout << endl;
	maxLenght = 0;
	for (auto value : tramR)
	{
		multimap<string, int>::iterator iter = stopTram.find(value);
		if (iter != stopTram.end())
			while (iter->first == value)
			{
				tempValue = iter->second;
				iter++;
				if (iter != stopTram.end())
					if (iter->first == value)
						thisLenght += lenght(tempValue, iter->second);
					else
						continue;
				else
					break;
			}
		if (maxLenght < thisLenght)
		{
			maxLenght = thisLenght;
			rout = value;
		}
		thisLenght = 0;
	}
	cout << "Rout with max lenght for tram - " << rout << endl;
	maxLenght = 0;
	for (auto value : trolleybusR)
	{
		multimap<string, int>::iterator iter = stopTrolleybus.find(value);
		if (iter != stopTrolleybus.end())
			while (iter->first == value)
			{
				tempValue = iter->second;
				iter++;
				if (iter != stopTrolleybus.end())
					if (iter->first == value)
						thisLenght += lenght(tempValue, iter->second);
					else
						continue;
				else
					break;
			}
		if (maxLenght < thisLenght)
		{
			maxLenght = thisLenght;
			rout = value;
		}
		thisLenght = 0;
	}
	cout << "Rout with max lenght for trolleybus - " << rout << endl;


	//*********************************************************TASK3***************************************************************************
	int streetStop = 0;
	int position = 0;
	for (auto it = 0; it < streets.size(); it++)
		if (streets[it].second > streetStop && !streets[it].first.empty())
		{
			streetStop = streets[it].second;
			position = it;
		}
	cout << "Task 3 :\nName of street with max quantity of stop - " << streets[position].first << endl;
}