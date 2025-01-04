﻿#include <iostream>
#include "dataType.h"
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <string>

using namespace std;

vector<Site> siteList;
vector<Route> routeList;
vector<Flight> flightList;
vector<Ticket> ticketList;
vector<int> vectorIndex;




//Route testRouteA = { 1, {1,2}, 22 };
//Route testRouteB = { };
//
//Flight testFlightA = { };
//Flight testFlightB = { };
//
//Ticket testTicketA = { };
//Ticket testTicketB = { };

enum SortType {
	ByTimeLength,
	ByLeaveTime,
	ByName,
	ByCode
};
enum QueryType {
	Shortest,
	Cheapest
};

vector<int> SortByTimeLength(vector<time_t> originVector) {
	vector<int> originIndexVector;
	int i = 0;

	//初始化传入下标vector
	for (auto trashVar : originVector) {
		originIndexVector.push_back(i);
		i++;
	}
	vector<int> finalIndexVector;
	int elementAmount = size(originIndexVector);
	for (int loopTime = 0; loopTime != elementAmount; loopTime++) {
		time_t smallestTime = 0;
		int elementIndex = 0;
		int smallestIndex = 0;
		for (auto nowTime : originVector) {
			if (smallestTime < nowTime) {
				smallestIndex = elementIndex;
			}
			elementIndex++;
		}
		finalIndexVector.push_back(smallestIndex);
	}
	return finalIndexVector;
}

vector<int> SortByLeaveTime(vector<time_t> originVector){
	vector<int> originIndexVector;
	int i = 0;

	//初始化传入下标vector
	for (auto trashVar : originVector) {
		originIndexVector.push_back(i);
		i++;
	}
	vector<int> finalIndexVector;
	int elementAmount = size(originIndexVector);
	for (int loopTime = 0; loopTime != elementAmount; loopTime++) {
		time_t cloestTime = 0;
		int elementIndex = 0;
		int smallestIndex = 0;
		for (auto nowTime : originVector) {
			if (cloestTime > nowTime) {
				smallestIndex = elementIndex;
			}
			elementIndex++;
		}
		finalIndexVector.push_back(smallestIndex);
	}
	return finalIndexVector;
}

/*
vector<int> SortByByName(vector<string> originVector) {
	vector<int> originIndexVector;
	int i = 0;

	//初始化传入下标vector
	for (auto trashVar : originVector) {
		originIndexVector.push_back(i);
		i++;
	}
	vector<int> finalIndexVector;
	int elementAmount = size(originIndexVector);
	for (int loopTime = 0; loopTime != elementAmount; loopTime++) {
		string smallestStr = originVector[0];
		int elementIndex = 0;
		int smallestIndex = 0;
		for (auto nowStr : originVector) {
			if (compare(nowStr,smallestStr) <= 0) {
				smallestIndex = elementIndex;
			}
			elementIndex++;
		}
		finalIndexVector.push_back(smallestIndex);
	}
	return finalIndexVector;
}*/

//vector<int> SortByByCode(vector<int> originVector) {}

//TODO
class SiteSystem {
public:

	//TODO
	void SortSiteList(SortType) {

	}

	void ShowSiteList() {
		cout << "Site Code   " << "Site Name           " << "longitude " << "latitude" << endl;
		for (Site site : siteList) {
			cout << left << setw(12) << site.siteCode;
			cout << left << setw(20) << site.siteName;
			cout << left << setw(10) << site.longitude;
			cout << left << setw(10) << site.latitude << endl;
		}
	}

	void AddSite() {
		Site newSite;
		cout << "Site Code:"; cin >> newSite.siteCode;
		cout << "Longitude:"; cin >> newSite.longitude;
		cout << "Latitude:"; cin >> newSite.latitude;
		cout << "Site Name:"; cin >> newSite.siteName;
		siteList.push_back(newSite);
	}

	//TODO
	bool DeleteSite() {
		return false;
	}

	//TODO
	void ModifySiteName() {

	}
};

//TODO
class RouteSystem {
public:
	//TODO
	void AddRoute() {

	}

	//TODO
	bool DeleteRoute() {
		return false;
	}

	//TODO
	void ModifyRoute() {

	}

	//TODO
	void SortRouteList(SortType) {

	}

	//TODO
	void ShowRouteList() {

	}
};

//TODO
class FlightSystem {
public:
	//TODO
	void AddFlight() {

	}

	//TODO
	bool DeleteFlight() {
		return false;
	}

	//TODO
	void ModifyFlight() {

	}

	//TODO
	void SortFlightList(SortType) {

	}

	//TODO
	void ShowFlightList() {

	}
};

//TODO
class TicketingSystem  {
public:
	Flight queryFlight;

	//TODO
	Flight* QueryFlight(QueryType) {
	}

	//TODO
	void AddTicket() {

	}
};

//TODO
class SavingSystem {
public:
	//TODO
	void SavingToFile() {

	}

	//TODO
	void ReadingFromFile() {

	}
};


void SiteScreen() {
	bool ifExit = false;
	int action = 0;
	SiteSystem siteSystem;
	while (ifExit != true) {
		cout << "1.Add new site" << endl
			<< "2.Delete site" << endl
			<< "3.Modify site name" << endl
			<< "4.Show site list" << endl
			<< "5.Back" << endl;
		cout << "Please choose an action:" << endl;

		cin >> action;
		system("cls");
		switch (action) {
		case 1:
			siteSystem.AddSite();
			system("cls");
			break;
		case 2:
			if (siteSystem.DeleteSite() == true) {
				cout << "Delete success!" << endl;
				_getch();
				system("cls");
			}
			else {
				cout << "Can't delete this site!" << endl;
				_getch();
				system("cls");
			}
			break;
		case 3:
			siteSystem.ModifySiteName();
			system("cls");
			break;
		case 4:
			siteSystem.ShowSiteList();
			break;
		case 5:
			ifExit = true;
			break;
		default:
			break;
		}
	}
}

void RouteScreen() {
	bool ifExit = false;
	int action = 0;
	RouteSystem routeSystem;
	while (ifExit != true) {
		cout << "1.Add new route" << endl
			<< "2.Delete route" << endl
			<< "3.Modify route" << endl
			<< "4.Show route list" << endl
			<< "5.Back" << endl;
		cout << "Please choose an action:" << endl;

		cin >> action;
		system("cls");
		switch (action) {
		case 1:
			routeSystem.AddRoute();
			system("cls");
			break;
		case 2:
			if (routeSystem.DeleteRoute() == true) {
				cout << "Delete success!" << endl;
				_getch();
				system("cls");
			}
			else {
				cout << "Can't delete this route!" << endl;
				_getch();
				system("cls");
			}
			break;
		case 3:
			routeSystem.ModifyRoute();
			system("cls");
			break;
		case 4:
			routeSystem.ShowRouteList();
			break;
		case 5:
			ifExit = true;
			break;
		default:
			break;
		}
	}
}

void FlightScreen() {
	bool ifExit = false;
	int action = 0;
	FlightSystem flightSystem;
	while (ifExit != true) {
		cout << "1.Add new flight" << endl
			<< "2.Delete flight" << endl
			<< "3.Modify flight" << endl
			<< "4.Show flight list" << endl
			<< "5.Back" << endl;
		cout << "Please choose an action:" << endl;

		cin >> action;
		system("cls");
		switch (action) {
		case 1:
			flightSystem.AddFlight();
			system("cls");
			break;
		case 2:
			if (flightSystem.DeleteFlight() == true) {
				cout << "Delete success!" << endl;
				_getch();
				system("cls");
			}
			else {
				cout << "Can't delete this flight!" << endl;
				_getch();
				system("cls");
			}
			break;
		case 3:
			flightSystem.ModifyFlight();
			system("cls");
			break;
		case 4:
			flightSystem.ShowFlightList();
			break;
		case 5:
			ifExit = true;
			break;
		default:
			break;
		}
	}
}

void TicketingScreen() {
	bool ifExit = false;
	int action = 0;
	TicketingSystem ticketingSystem;
	while (ifExit != true) {
		cout << "1.Add new ticket" << endl
			<< "2.Back" << endl;
		cout << "Please choose an action:" << endl;

		cin >> action;
		system("cls");
		switch (action) {
		case 1:
			ticketingSystem.AddTicket();
			system("cls");
			break;
		case 2:
			ifExit = true;
			break;
		default:
			break;
		}
	}
}

void HomeScreen() {
	bool ifExit = false;
	int action = 0;
	while (ifExit != true) {
		cout << "1.Site System" << endl
			 << "2.Route System" << endl
			 << "3.Flight System" << endl
			 << "4.Ticketing System" << endl
		  	 << "5.Save" << endl
			 << "6.Read" << endl
			 << "7.Exit" << endl;
		cout << "Please choose an action:" << endl;

		cin >> action;
		system("cls");
		switch (action) {
		case 1:
			SiteScreen();
			break;
		case 2:
			RouteScreen();
			break;
		case 3:
			FlightScreen();
			break;
		case 4:
			TicketingScreen();
			break;
		case 5:
			//TODO
			break;
		case 6:
			//TODO
			break;
		case 7:
			ifExit = true;
			break;
		default:
			break;
		}
	}
}



int main()
{
	Site testSiteA = { 1, 11, 11, "TSA",{1,2} };
	Site testSiteB = { 2, 22, 22, "TSB",{3,4} };
	
	siteList.push_back(testSiteA);
	siteList.push_back(testSiteB);
	HomeScreen();
}