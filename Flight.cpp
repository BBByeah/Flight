#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <conio.h>

#include <stdexcept>
#include <limits>
#include <iostream>
#include "dataType.h"
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <sstream>
#include <math.h>

#define EARTH_RADIUS 6371.0
#define PI 3.14159265358979323846

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

		//初始化变量为未选择过的元素对应初始值
		int j = 0;
		for (time_t initTime : originVector) {
			if (initTime != -1) {
				smallestTime = initTime;
				smallestIndex = j;
				break;
			}
			j++;
		}
		for (auto nowTime : originVector) {
			if (smallestTime > nowTime) {
				smallestIndex = elementIndex;
				smallestTime = nowTime;
			}
			elementIndex++;
		}
		originVector[smallestIndex] = -1;
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

		//初始化变量为未选择过的元素对应初始值
		int j = 0;
		for (time_t initTime : originVector) {
			if (initTime != -1) {
				cloestTime = initTime;
				smallestIndex = j;
				break;
			}
			j++;
		}
		for (auto nowTime : originVector) {
			if (cloestTime > nowTime) {
				smallestIndex = elementIndex;
				cloestTime = nowTime;
			}
			elementIndex++;
		}
		originVector[smallestIndex] = -1;
		finalIndexVector.push_back(smallestIndex);
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
		int smallestIndex;

		//初始化变量为未选择过的元素对应初始值
		int j = 0;
		for (string initStr : originVector) {
			if (initStr != "-1") {
				smallestStr = initStr;
				smallestIndex = j;
				break;
			}
			j++;
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
		int smallestIndex;

		//初始化变量为未选择过的元素对应初始值
		int j = 0;
		for (int initCode : originVector) {
			if (initCode != -1) {
				smallestCode = initCode;
				smallestIndex = j;
				break;
			}
			j++;
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
	return finalIndexVector;
}

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
				<< "4.Back" << endl;
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

	bool DeleteSite() {
		int siteCode;
		cout << "Enter site code to delete:";
		cin >> siteCode;

		// Check if site exists
		auto it = find_if(siteList.begin(), siteList.end(),
			[siteCode](const Site& site) { return site.siteCode == siteCode; });

		if (it == siteList.end()) {
			cout << "Site does not exist!" << endl;
			return false;
		}

		// Check if site has related routes
		if (!it->relatedRouteCode.empty()) {
			cout << "Site has related routes, cannot delete!" << endl;
			return false;
		}

		// Display site information
		cout << "\nSite Information:" << endl;
		cout << "Site Code: " << it->siteCode << endl;
		cout << "Site Name: " << it->siteName << endl;
		cout << "Longitude: " << it->longitude << endl;
		cout << "Latitude: " << it->latitude << endl;

		// Confirm deletion
		char confirm;
		cout << "\nConfirm deletion? (Y/N): ";
		cin >> confirm;
		if (confirm != 'Y' && confirm != 'y') {
			cout << "Deletion cancelled!" << endl;
			return false;
		}

		// Delete site
		siteList.erase(it);
		return true;
	}

	void ModifySiteName() {
		int siteCode;
		string newName;
		cout << "Enter site code to modify:";
		cin >> siteCode;

		// Find site
		auto it = find_if(siteList.begin(), siteList.end(),
			[siteCode](const Site& site) { return site.siteCode == siteCode; });

		if (it == siteList.end()) {
			cout << "Site does not exist!" << endl;
			return;
		}

		cout << "Enter new site name:";
		cin >> newName;
		it->siteName = newName;
		cout << "Modification successful!" << endl;
	}
};

class RouteSystem {
public:
	double Degree2rad(double degree) {
		return (degree * PI / 180);
	}

	//计算地球上两点距离
	double Haversine_distance(double lat1, double lon1, double lat2, double lon2) {
		double dLat = Degree2rad(lat2 - lat1);
		double dLon = Degree2rad(lon2 - lon1);
		double a = sin(dLat / 2) * sin(dLat / 2) +
			cos(Degree2rad(lat1)) * cos(Degree2rad(lat2)) *
			sin(dLon / 2) * sin(dLon / 2);
		double c = 2 * atan2(sqrt(a), sqrt(1 - a));
		return EARTH_RADIUS * c;
	}

	void AddRoute() {
		Route newRoute;
		cout << "Route code:"; cin >> newRoute.routeCode;
		cout << "Departure site code:"; cin >> newRoute.relatedSites[0];
		cout << "Landing site code::"; cin >> newRoute.relatedSites[1];
		double lon0, lon1, lat0, lat1;
		for (Site site : siteList) {
			if (newRoute.relatedSites[0] == site.siteCode) {
				lon0 = site.longitude;
				lat0 = site.latitude;
				site.relatedRouteCode.push_back(newRoute.routeCode);
			}
			if (newRoute.relatedSites[1] == site.siteCode) {
				lon1 = site.longitude;
				lat1 = site.latitude;
				site.relatedRouteCode.push_back(newRoute.routeCode);
			}
		}
		double newDistance = Haversine_distance(lat0, lon0, lat1, lon1);
		newRoute.distance = newDistance;

		//计算时间和费用
		const double CRUISE_SPEED = 900.0;
		const double FUEL_CONSUMPTION_RATE = 1.0;
		const double FUEL_PRICE_PER_TON = 1500.0;
		double newDuration;
		double fuelConsumption;
		double fuelCost;
		newDuration = newRoute.distance / CRUISE_SPEED;
		fuelConsumption = FUEL_CONSUMPTION_RATE * newDuration;
		fuelCost = fuelConsumption * FUEL_PRICE_PER_TON;

		newRoute.price[2] = fuelCost * 1.5;
		newRoute.price[1] = newRoute.price[2] * 1.2;
		newRoute.price[0] = newRoute.price[2] * 1.5;
		newRoute.duration = newDuration;

		routeList.push_back(newRoute);
	}

	bool DeleteRoute() {
		int routeCode;
		cout << "Enter route code to delete:";
		cin >> routeCode;

		// Check if route exists
		auto it = find_if(routeList.begin(), routeList.end(),
			[routeCode](const Route& route) { return route.routeCode == routeCode; });

		if (it == routeList.end()) {
			cout << "Route does not exist!" << endl;
			return false;
		}

		// Check if route has related flights
		if (!it->relatedFlightCode.empty()) {
			cout << "Route has related flights, cannot delete!" << endl;
			return false;
		}

		Route route;

		// Display route information
		cout << "\nRoute Information:" << endl;
		cout << "Route Code: " << it->routeCode << endl;
		cout << "Related Sites: " << it->relatedSites[0] << "<->" << it->relatedSites[1] << endl;
		cout << "Price: " << it->price[0] << "|" << it->price[1] << "|" << it->price[2] << endl;
		cout << "duration: " << it->duration << " h" << endl;

		// Confirm deletion
		char confirm;
		cout << "\nConfirm deletion? (Y/N): ";
		cin >> confirm;
		if (confirm != 'Y' && confirm != 'y') {
			cout << "Deletion cancelled!" << endl;
			return false;
		}

		// Delete route
		routeList.erase(it);
		return true;
		return false;
	}

	void ModifyRoute() {
		int routeCode;
		int newDepartureSiteCode;
		int newLandingSiteCode;
		cout << "Enter route code to modify:";
		cin >> routeCode;

		// Find route
		auto it = find_if(routeList.begin(), routeList.end(),
			[routeCode](const Route& route) { return route.routeCode == routeCode; });

		if (it == routeList.end()) {
			cout << "Route does not exist!" << endl;
			return;
		}

		cout << "Enter new departure site code:";
		cin >> newDepartureSiteCode;
		cout << "Enter new landing site code:";
		cin >> newLandingSiteCode;

		// Delete route
		routeList.erase(it);

		//modify the route by create a new one
		Route newRoute;
		newRoute.routeCode = routeCode;
		newRoute.relatedSites[0] = newDepartureSiteCode;
		newRoute.relatedSites[1] = newLandingSiteCode;
		double lon0, lon1, lat0, lat1;
		for (Site site : siteList) {
			if (newRoute.relatedSites[0] == site.siteCode) {
				lon0 = site.longitude;
				lat0 = site.latitude;
				site.relatedRouteCode.push_back(newRoute.routeCode);
			}
			if (newRoute.relatedSites[1] == site.siteCode) {
				lon1 = site.longitude;
				lat1 = site.latitude;
				site.relatedRouteCode.push_back(newRoute.routeCode);
			}
		}
		double newDistance = Haversine_distance(lat0, lon0, lat1, lon1);
		newRoute.distance = newDistance;

		//计算时间和费用
		const double CRUISE_SPEED = 900.0;
		const double FUEL_CONSUMPTION_RATE = 1.0;
		const double FUEL_PRICE_PER_TON = 1500.0;
		double newDuration;
		double fuelConsumption;
		double fuelCost;
		newDuration = newRoute.distance / CRUISE_SPEED;
		fuelConsumption = FUEL_CONSUMPTION_RATE * newDuration;
		fuelCost = fuelConsumption * FUEL_PRICE_PER_TON;

		newRoute.price[2] = fuelCost * 1.5;
		newRoute.price[1] = newRoute.price[2] * 1.2;
		newRoute.price[0] = newRoute.price[2] * 1.5;
		newRoute.duration = newDuration;

		routeList.push_back(newRoute);
		cout << "Modification successful!" << endl;
	}

	void SortRouteListByCode() {
		vector<int> newIndexVector = {};
		vector<Route> newRouteList = {};
		vector<int> codeVector = {};
		for (Route route : routeList) {
			codeVector.push_back(route.routeCode);
		}
		newIndexVector = SortByByCode(codeVector);
		for (int index : newIndexVector) {
			newRouteList.push_back(routeList[index]);
		}
		routeList.clear();
		routeList = newRouteList;
	}

	void ShowRouteList() {
		bool ifEnd = false;
		bool ifShow = true;
		int action = 0;
		while (ifEnd != true) {
			cout << "1.List by code" << endl
				<< "2.List directly" << endl
				<< "3.Back" << endl;
			cin >> action;
			system("cls");
			switch (action) {
			case 1:
				SortRouteListByCode();
				ifEnd = true;
				break;
			case 2:
				ifEnd = true;
				break;
			case 3:
				ifShow = false;
				ifEnd = true;
				break;
			}
		}

		Route route;

		if (ifShow == true) {
			cout << "Route Code   " << "Related Sites           " << "distance " << "price         " << "duration" << endl;
			for (Route route : routeList) {
				cout << left << setw(12) << route.routeCode;
				cout << left << setw(25) << reinterpret_cast<string&>(route.relatedSites[0]) + "-" + reinterpret_cast<string&>(route.relatedSites[1]);
				cout << left << setw(10) << route.distance;
				cout << left << setw(15) << reinterpret_cast<string&>(route.price[0]) + "|" + reinterpret_cast<string&>(route.price[1]) + "|" + reinterpret_cast<string&>(route.price[2]) << endl;
				cout << left << setw(9) << route.duration;
			}
			_getch();
			system("cls");
		}
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