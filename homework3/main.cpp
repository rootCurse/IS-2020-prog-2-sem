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
	bool stop = true;
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

void dataLocation(string& data, int indexOfStop)
{
	int flag;
	container[indexOfStop].site = data;
	string subStr1, subStr2;
	mySplit(data, subStr1, subStr2);
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

void dataRoute(string& data, int indexOfStop)
{

	string buffer;
	buffer.clear();
	if (container[indexOfStop].stop == 1)
	{
		if (indexOfStop < 888)
		{
			for (auto value : data)
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
			for (auto value : data)
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
			for (auto value : data)
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

void dataCoordinates(string& data, int indexOfStop)
{
	double coordinates1, coordinates2;
	string subStr1, subStr2;
	mySplit(data, subStr1, subStr2);
	coordinates1 = stod(subStr1);
	coordinates2 = stod(subStr2);
	container[indexOfStop].coordinatesOne = coordinates1;
	container[indexOfStop].coordinatesTwo = coordinates2;
}

double lenght(int firstStop, int secondStop)
{
	double firstSin;
	firstSin = sin((container[secondStop].coordinatesOne - container[firstStop].coordinatesOne) / 2);
	double secondSin;
	secondSin = sin((container[secondStop].coordinatesTwo - container[firstStop].coordinatesTwo) / 2);
	return asin(sqrt(firstSin * firstSin + secondSin * secondSin * cos(container[firstStop].coordinatesOne) * cos(container[secondStop].coordinatesOne)));
}

//fixed const&
void Task1(const multimap<string, int> &m, const set<string>& r)
{
	string route;
	int countOfStop = 0;
	for (auto value : r)
		if (countOfStop < m.count(value))
		{
			countOfStop = m.count(value);
			route = value;
		}
	cout << "Number of route: " << route << " - Quantity of bus stop: " << countOfStop << endl;
}

void Task2(multimap<string, int> &m, const set<string> &r)
{
	double thisLenght = 0, maxLenght = 0;
	string route;
	double tempValue;
	for (auto value : r)
	{
		multimap<string, int>::iterator iter = m.find(value);
		if (iter != m.end())
			while (iter->first == value)
			{
				tempValue = iter->second;
				iter++;
				if (iter != m.end())
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
			route = value;
		}
		thisLenght = 0;
	}
	cout << "Route with max lenght for - " << route << endl;
}

int main()
{
	int indexOfStop = 0;
	container.resize(8000);

	//******************************************************UTF**********************************************************************
	system("chcp 65001");


	//*******************************************************OPENXML****************************************************************
	pugi::xml_document input;
	if (!input.load_file(R"(data.xml)")) return -1;

	pugi::xml_node test = input.child("dataset");
	for (pugi::xml_node tools = test.child("transport_station"); tools; tools = tools.next_sibling("transport_station"))
	{
		string data;
		data = tools.child_value("type_of_vehicle");
		container[indexOfStop].typeOfTransport = data;
		data = tools.child_value("location");
		dataLocation(data, indexOfStop);
		data = tools.child_value("routes");
		dataRoute(data, indexOfStop);
		data = tools.child_value("coordinates");
		dataCoordinates(data, indexOfStop);
		indexOfStop++;
	}



	//********************************************************TASK1**************************************************************************
	string route;
	int countOfStop = 0;
	cout << "Task 1 :" << endl << endl;
	cout << "Bus: " << endl;
	Task1(stopBus, busR);
	cout << "Tram: " << endl;
	Task1(stopTram, tramR);
	cout << "Trolleybus: " << endl;
	Task1(stopTrolleybus, trolleybusR);
	cout << endl << endl;

	//*********************************************************TASK2***************************************************************************
	cout << "Task 2: " << endl << endl;
	cout << "Bus: " << endl;
	Task2(stopBus, busR);
	cout << "Tram: " << endl;
	Task2(stopTram, tramR);
	cout << "Trolleybus: " << endl;
	Task2(stopTrolleybus, trolleybusR);
	cout << endl << endl;


	//*********************************************************TASK3***************************************************************************
	int streetStop = 0;
	int position = 0;
	//todo first second
	for (auto it = 0; it < streets.size(); it++)
		if (streets[it].second > streetStop && !streets[it].first.empty())
		{
			streetStop = streets[it].second;
			position = it;
		}
	cout << "Task 3 :\nName of street with max quantity of stop - " << streets[position].first << endl;
}