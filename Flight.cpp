#include <iostream>
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
		originVector[smallestIndex] = -1;
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
			if (cloestTime >= nowTime) {
				smallestIndex = elementIndex;
			}
			elementIndex++;
		}
		finalIndexVector.push_back(smallestIndex);
		originVector[smallestIndex] = -1;
	}
	return finalIndexVector;
}

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
		string smallestStr;
		int elementIndex = 0;
		int smallestIndex = 0;

		//初始化最小值
		for (string initStr : originVector) {
			if (initStr != "-1") {
				smallestStr = initStr;
				break;
			}
		}

		for (auto nowStr : originVector) {
			if (smallestStr > nowStr && nowStr != "-1") {
				smallestIndex = elementIndex;
				smallestStr = nowStr;
			}
			elementIndex++;
		}

		finalIndexVector.push_back(smallestIndex);
		originVector[smallestIndex] = "-1";
	}
	return finalIndexVector;
}

vector<int> SortByByCode(vector<int> originVector) {
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
		int smallestCode;
		int elementIndex = 0;
		int smallestIndex = 0;

		//初始化最小值
		for (int initCode : originVector) {
			if (initCode != -1) {
				smallestCode = initCode;
				break;
			}
		}

		for (auto nowCode : originVector) {
			if (smallestCode > nowCode && nowCode != -1) {
				smallestIndex = elementIndex;
				smallestCode = nowCode;
			}
			elementIndex++;
		}
		originVector[smallestIndex] = -1;
		finalIndexVector.push_back(smallestIndex);
	}
	for (int index : finalIndexVector) {
		cout << index;
	}
	return finalIndexVector;
}

//TODO
class SiteSystem {
public:

	void SortSiteListByName() {
		vector<int> newIndexVector;
		vector<Site> newSiteList;
		vector<string> nameVector;
		for (Site site : siteList) {
			nameVector.push_back(site.siteName);
		}
		newIndexVector = SortByByName(nameVector);
		for (int index : newIndexVector) {
			newSiteList.push_back(siteList[index]);
		}
		siteList.clear();
		siteList = newSiteList;
	}

	void SortSiteListByCode() {
		vector<int> newIndexVector = {};
		vector<Site> newSiteList = {};
		vector<int> codeVector = {};
		for (Site site : siteList) {
			codeVector.push_back(site.siteCode);
		}
		newIndexVector = SortByByCode(codeVector);
		for (int index : newIndexVector) {
			newSiteList.push_back(siteList[index]);
		}
		siteList.clear();
		siteList = newSiteList;
	}

	void ShowSiteList() {
		bool ifEnd = false;
		bool ifShow = true;
		int action = 0;
		while (ifEnd != true) {
			cout << "1.List by code" << endl
				<< "2.List by name" << endl
				<< "3.List directly" << endl
				<< "4.Back";
			cin >> action;
			system("cls");
			switch (action) {
			case 1:
				SortSiteListByCode();
				ifEnd = true;
				break;
			case 2:
				SortSiteListByName();
				ifEnd = true;
				break;
			case 3:
				ifEnd = true;
				break;
			case 4:
				ifShow = false;
				ifEnd = true;
				break;
			}
		}

		if (ifShow == true) {
			cout << "Site Code   " << "Site Name           " << "longitude " << "latitude" << endl;
			for (Site site : siteList) {
				cout << left << setw(12) << site.siteCode;
				cout << left << setw(20) << site.siteName;
				cout << left << setw(10) << site.longitude;
				cout << left << setw(10) << site.latitude << endl;
			}
			_getch();
			system("cls");
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
	Site testSiteA = { 3, 1, 1, "A",{1,2} };
	Site testSiteB = { 1, 2, 2, "C",{3,4} };
	Site testSiteC = { 2, 3, 3, "B" };
	Site testSiteD = { 3, 4, 4, "A",{1,2} };
	Site testSiteE = { 1, 5, 5, "C",{3,4} };
	Site testSiteF = { 2, 6, 6, "B" };
	
	siteList.push_back(testSiteA);
	siteList.push_back(testSiteB);
	siteList.push_back(testSiteC);
	siteList.push_back(testSiteD);
	siteList.push_back(testSiteE);
	siteList.push_back(testSiteF);
	HomeScreen();
}