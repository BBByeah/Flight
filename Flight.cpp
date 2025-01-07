#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <conio.h>

#include <iostream>
#include "dataType.h"
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <stdarg.h>

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
			Sleep(500);
			system("cls");
			switch (action) {
			case 1:
				Sleep(500);
				SortSiteListByCode();
				ifEnd = true;
				break;
			case 2:
				Sleep(500);
				SortSiteListByName();
				ifEnd = true;
				break;
			case 3:
				Sleep(500);
				ifEnd = true;
				break;
			case 4:
				Sleep(500);
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
			Sleep(500);
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
		cout << "Add successfully!";
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
		return 6371.0 * c;
	}

	void AddRoute(int routeCode, int siteCodeA, int siteCodeB) {
		Route newRoute;
		newRoute.routeCode = routeCode;
		newRoute.relatedSites[0] = siteCodeA;
		// Find site
		auto it1 = find_if(siteList.begin(), siteList.end(),
			[siteCodeA](const Site& site) { return site.siteCode == siteCodeA; });

		if (it1 == siteList.end()) {
			cout << "Site does not exist!" << endl;
			return;
		}
		
		newRoute.relatedSites[1] = siteCodeB;
		auto it2 = find_if(siteList.begin(), siteList.end(),
			[siteCodeB](const Site& site) { return site.siteCode == siteCodeB; });

		if (it2 == siteList.end()) {
			cout << "Site does not exist!" << endl;
			return;
		}

		double lon0, lon1, lat0, lat1;
		for (Site site : siteList) {
			if (newRoute.relatedSites[0] == site.siteCode) {
				lon0 = site.longitude;
				lat0 = site.latitude;
			}
			if (newRoute.relatedSites[1] == site.siteCode) {
				lon1 = site.longitude;
				lat1 = site.latitude;
			}
		}

		auto itA = find_if(siteList.begin(), siteList.end(),
			[siteCodeA](const Site& site) { return site.siteCode == siteCodeA; });
		itA->relatedRouteCode.push_back(routeCode);
		auto itB = find_if(siteList.begin(), siteList.end(),
			[siteCodeB](const Site& site) { return site.siteCode == siteCodeB; });
		itB->relatedRouteCode.push_back(routeCode);
		double newDistance = Haversine_distance(lat0, lon0, lat1, lon1);
		newRoute.distance = newDistance;

		//计算时间和费用
		double CRUISE_SPEED = 900.0;
		double newDuration;
		newDuration = newRoute.distance / CRUISE_SPEED;

		cout << "Economy class price:"; cin >> newRoute.price[2];
		newRoute.price[1] = newRoute.price[2] * 1.2;
		newRoute.price[0] = newRoute.price[2] * 1.5;
		newRoute.duration = newDuration * 3600;

		routeList.push_back(newRoute);
	}

	bool DeleteRoute(int routeCode) {
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


		// Delete route code in sites
		int relatedSiteCodeA;
		int relatedSiteCodeB;
		relatedSiteCodeA = it->relatedSites[0];
		relatedSiteCodeB = it->relatedSites[1];
		for (Site& site : siteList) {
			if (site.siteCode == relatedSiteCodeA) {
				auto itA = find(site.relatedRouteCode.begin(), site.relatedRouteCode.end(), routeCode);
				site.relatedRouteCode.erase(itA);
			}
		}
		for (Site& site : siteList) {
			if (site.siteCode == relatedSiteCodeB) {
				auto itB = find(site.relatedRouteCode.begin(), site.relatedRouteCode.end(), routeCode);
				site.relatedRouteCode.erase(itB);
			}
		}

		//delete route
		routeList.erase(it);
		return true;
	}

	bool ModifyRoute(int routeCode, int newDepartureSiteCode, int newLandingSiteCode) {
		RouteSystem routeSystem;
		// Find route
		auto it = find_if(routeList.begin(), routeList.end(),
			[routeCode](const Route& route) { return route.routeCode == routeCode; });

		if (it == routeList.end()) {
			cout << "Route does not exist!" << endl;
			return false;
		}

		// Check if route has related flights
		if (!it->relatedFlightCode.empty()) {
			cout << "Route has related flights, cannot modify!" << endl;
			return false;
		}


		// Delete route and modify the route by create a new one
		if (routeSystem.DeleteRoute(routeCode) != true) {
			return false;
		}
		routeSystem.AddRoute(routeCode, newDepartureSiteCode, newLandingSiteCode);
		return true;
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

		if (ifShow == true) {
			cout << "Route Code    " << "|Related Sites            " 
				<< "|distance   " << "|price               " << "|duration" << endl;
			for (Route route : routeList) {
				cout << left << setw(14) << route.routeCode;
				cout << "|"  << left     << setw(12)  << route.relatedSites[0] << "-"
							 << setw(12) << route.relatedSites[1];
				cout << "|"  << left	 << setw(9)  << route.distance << "km";
				cout << "|" << left << setw(6)  << route.price[0] << "|"
					 << left << setw(6)  << route.price[1] << "|"
					 << left << setw(6)  << route.price[2] ;
				cout << "|" << left << setw(9) << route.duration / 3600 << "h" << endl;
			}
			_getch();
			system("cls");
		}
	}
};

class FlightSystem {
public:
	//手动输入时间
	time_t inputTime() {
		int year, month, day, hour, minute, second;
		std::cout << "Enter departure year: ";
		std::cin >> year;
		std::cout << "Enter month (1-12): ";
		std::cin >> month;
		std::cout << "Enter day (1-31): ";
		std::cin >> day;
		std::cout << "Enter hour (0-23): ";
		std::cin >> hour;
		std::cout << "Enter minute (0-59): ";
		std::cin >> minute;
		std::cout << "Enter second (0-59): ";
		std::cin >> second;

		tm timeinfo = {};
		timeinfo.tm_year = year - 1900; // Year since 1900
		timeinfo.tm_mon = month - 1;    // Months since January (0-11)
		timeinfo.tm_mday = day;         // Day of the month (1-31)
		timeinfo.tm_hour = hour;        // Hours since midnight (0-23)
		timeinfo.tm_min = minute;       // Minutes after the hour (0-59)
		timeinfo.tm_sec = second;       // Seconds after the minute (0-59)

		time_t rawtime = mktime(&timeinfo);
		return rawtime;
	}
	
	void AddFlight(int flightCode, int siteCodeA, int siteCodeB, int remainingTickets[3], int routeNumber, ...) {
		Flight newFlight;
		newFlight.flightCode = flightCode;
		newFlight.startSiteCode = siteCodeA;
		newFlight.endSiteCode = siteCodeB;
		va_list PBRCs;//PassingByRouteCodes
		va_start(PBRCs, routeNumber);
		for (int i = 0; i <= routeNumber; i++) {
			newFlight.passingByRouteCodes.push_back(va_arg(PBRCs, int));
		}
		va_end(PBRCs);
		newFlight.departureTime = inputTime();
		newFlight.landingTime = newFlight.departureTime;
		for (int routeCode : newFlight.passingByRouteCodes) {
			// Find route
			auto it1 = find_if(routeList.begin(), routeList.end(),
				[routeCode](const Route& route) { return route.routeCode == routeCode; });
			newFlight.totalPrice[0] += it1->price[0];
			newFlight.totalPrice[1] += it1->price[1];
			newFlight.totalPrice[2] += it1->price[2];
			newFlight.landingTime += it1->duration;
			newFlight.totalDuration += it1->duration;
			it1->relatedFlightCode.push_back(flightCode);
		}
		flightList.push_back(newFlight);
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

class SavingSystem {
public:
	// Save all data to CSV files
	// Including site information (sites.csv), route information (routes.csv),
	// flight information (flights.csv) and ticket information (tickets.csv)
	void SavingToFile() {
		// Save site information
		ofstream siteCsv("sites.csv");
		siteCsv << "SiteCode,Longitude,Latitude,SiteName,RelatedRouteCode\n";
		for (auto site : siteList) {
			siteCsv << site.siteCode << "," 
				<< site.longitude << ","
				<< site.latitude << ","
				<< site.siteName;
			for (auto routeCode : site.relatedRouteCode) {
				siteCsv << "," << routeCode;
			}
			siteCsv << "\n";
		}
		siteCsv.close();

		// Save route information
		ofstream routeCsv("routes.csv"); 
		routeCsv << "RouteCode,StartSite,EndSite,Distance,EconomyPrice,BusinessPrice,FirstClassPrice,Duration,RelatedFlightCode\n";
		for (auto route : routeList) {
			routeCsv << route.routeCode << ","
				<< route.relatedSites[0] << ","
				<< route.relatedSites[1] << ","
				<< route.distance << ","
				<< route.price[0] << ","
				<< route.price[1] << ","
				<< route.price[2] << ","
				<< route.duration;
			for (auto flightCode : route.relatedFlightCode) {
				routeCsv << "," << flightCode;
				}
			routeCsv << "\n";
		}
		routeCsv.close();


		// Save flight information
		ofstream flightCsv("flights.csv");
		flightCsv << "FlightCode,StartSite,EndSite,DepartureTime,ArrivalTime,EconomyRemaining,BusinessRemaining,FirstClassRemaining,EconomyPrice,BusinessPrice,FirstClassPrice,TotalDuration,PassingByRouteCodes\n";
		for (auto flight : flightList) {
			flightCsv << flight.flightCode << ","
				<< flight.startSiteCode << ","
				<< flight.endSiteCode << ","
				<< flight.departureTime << ","
				<< flight.landingTime << ","
				<< flight.remainingTickets[0] << ","
				<< flight.remainingTickets[1] << ","
				<< flight.remainingTickets[2] << ","
				<< flight.totalPrice[0] << ","
				<< flight.totalPrice[1] << ","
				<< flight.totalPrice[2] << ","
				<< flight.totalDuration;
				for (auto routeCode : flight.passingByRouteCodes) {
					flightCsv << "," << routeCode;
				}
				flightCsv << "\n";
		}
		flightCsv.close();

		// Save ticket information
		ofstream ticketCsv("tickets.csv");
		ticketCsv << "FlightCode,CustomerID,CustomerName,PurchaseTime\n";
		for (auto ticket : ticketList) {
			ticketCsv << ticket.flightCode << ","
				<< ticket.customerID << ","
				<< ticket.customerName << ","
				<< ticket.boughtTime << "\n";
		}
		ticketCsv.close();
	}

	// Read all data from CSV files
	// Including site information (sites.csv), route information (routes.csv),
	// flight information (flights.csv) and ticket information (tickets.csv)
	// Will output error messages if file opening fails or data format is incorrect
	void ReadingFromFile() {
		string line;
		vector<string> row;

		// Clear current data
		siteList.clear();
		routeList.clear();
		flightList.clear();
		ticketList.clear();

		// Read site information
		ifstream siteCsv("sites.csv");
		if (!siteCsv.is_open()) {
			cout << "Unable to open file: sites.csv" << endl;
			return;
		}
		getline(siteCsv, line); // Skip header
		while (getline(siteCsv, line)) {
			try {
				Site site;
				stringstream ss(line);
				string token;

				// Read site code
				if (getline(ss, token, ',')) {
					site.siteCode = stoi(token);
				}

				// Read longitude
				if (getline(ss, token, ',')) {
					site.longitude = stod(token);
				}

				// Read latitude
				if (getline(ss, token, ',')) {
					site.latitude = stod(token);
				}

				// Read site name
				if (getline(ss, token, ',')) {
					site.siteName = token;
				}

				// Read related route codes
				while (getline(ss, token, ',')) {
					if (!token.empty()) {
						site.relatedRouteCode.push_back(stoi(token));
					}
				}

				siteList.push_back(site);
			}
			catch (const exception& e) {
				cout << "Site data format error: " << e.what() << endl;
				continue;
			}
		}
		siteCsv.close();

		// Read route information
		ifstream routeCsv("routes.csv");
		if (!routeCsv.is_open()) {
			cout << "Unable to open file: routes.csv" << endl;
			return;
		}
		getline(routeCsv, line); // Skip header
		while (getline(routeCsv, line)) {
			try {
				Route route;
				stringstream ss(line);
				string token;

				if (getline(ss, token, ',')) route.routeCode = stoi(token);
				if (getline(ss, token, ',')) route.relatedSites[0] = stoi(token);
				if (getline(ss, token, ',')) route.relatedSites[1] = stoi(token);
				if (getline(ss, token, ',')) route.distance = stod(token);
				if (getline(ss, token, ',')) route.price[0] = stod(token);
				if (getline(ss, token, ',')) route.price[1] = stod(token);
				if (getline(ss, token, ',')) route.price[2] = stod(token);
				if (getline(ss, token, ',')) route.duration = stoll(token);

				routeList.push_back(route);
			}
			catch (const exception& e) {
				cout << "Route data format error: " << e.what() << endl;
				continue;
			}
		}
		routeCsv.close();

		// Read flight information
		ifstream flightCsv("flights.csv");
		if (!flightCsv.is_open()) {
			cout << "Unable to open file: flights.csv" << endl;
			return;
		}
		getline(flightCsv, line); // Skip header
		while (getline(flightCsv, line)) {
			try {
				Flight flight;
				stringstream ss(line);
				string token;

				if (getline(ss, token, ',')) flight.flightCode = (token == "1");
				if (getline(ss, token, ',')) flight.startSiteCode = stoi(token);
				if (getline(ss, token, ',')) flight.endSiteCode = stoi(token);
				if (getline(ss, token, ',')) flight.departureTime = stoll(token);
				if (getline(ss, token, ',')) flight.landingTime = stoll(token);
				if (getline(ss, token, ',')) flight.remainingTickets[0] = stoi(token);
				if (getline(ss, token, ',')) flight.remainingTickets[1] = stoi(token);
				if (getline(ss, token, ',')) flight.remainingTickets[2] = stoi(token);
				if (getline(ss, token, ',')) flight.totalPrice[0] = stod(token);
				if (getline(ss, token, ',')) flight.totalPrice[1] = stod(token);
				if (getline(ss, token, ',')) flight.totalPrice[2] = stod(token);
				if (getline(ss, token, ',')) flight.totalDuration = stoll(token);

				flightList.push_back(flight);
			}
			catch (const exception& e) {
				cout << "Flight data format error: " << e.what() << endl;
				continue;
			}
		}
		flightCsv.close();

		// Read ticket information
		ifstream ticketCsv("tickets.csv");
		if (!ticketCsv.is_open()) {
			cout << "Unable to open file: tickets.csv" << endl;
			return;
		}
		getline(ticketCsv, line); // Skip header
		while (getline(ticketCsv, line)) {
			try {
				Ticket ticket;
				stringstream ss(line);
				string token;

				if (getline(ss, token, ',')) ticket.flightCode = stoi(token);
				if (getline(ss, token, ',')) ticket.customerID = stoi(token);
				if (getline(ss, token, ',')) {
					strncpy(ticket.customerName, token.c_str(), sizeof(ticket.customerName) - 1);
					ticket.customerName[sizeof(ticket.customerName) - 1] = '\0';
				}
				if (getline(ss, token, ',')) ticket.boughtTime = stoll(token);

				ticketList.push_back(ticket);
			}
			catch (const exception& e) {
				cout << "Ticket data format error: " << e.what() << endl;
				continue;
			}
		}
		ticketCsv.close();
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
			Sleep(500);
			siteSystem.AddSite();
			system("cls");
			break;
		case 2:
			Sleep(100);
			if (siteSystem.DeleteSite() == true) {
				cout << "Delete success!" << endl;
				Sleep(500);
				_getch();
				system("cls");
			}
			else {
				cout << "Can't delete this site!" << endl;
				Sleep(500);
				_getch();
				system("cls");
			}
			break;
		case 3:
			Sleep(100);
			siteSystem.ModifySiteName();
			system("cls");
			break;
		case 4:
			Sleep(100);
			siteSystem.ShowSiteList();
			break;
		case 5:
			Sleep(100);
			ifExit = true;
			break;
		default:
			Sleep(100);
			cout << "Invalid input!" << endl;
			Sleep(1000);
			system("cls");
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
			int newAddRouteCode;
			int siteCodeA;
			int siteCodeB;
			cout << "Route code:"; cin >> newAddRouteCode;
			cout << "Departure site code:"; cin >> siteCodeA;
			cout << "Landing site code:"; cin >> siteCodeB;
			routeSystem.AddRoute(newAddRouteCode, siteCodeA, siteCodeB);
			system("cls");
			break;
		case 2:
			int deleteRouteCode;
			cout << "Enter route code to delete:";
			cin >> deleteRouteCode;
			if (routeSystem.DeleteRoute(deleteRouteCode) == true) {
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
			int modifyRouteCode;
			int newDepartureSiteCode;
			int newLandingSiteCode;
			cout << "Enter route code to modify:";
			cin >> modifyRouteCode;
			cout << "Enter new departure site code:";
			cin >> newDepartureSiteCode;
			cout << "Enter new landing site code:";
			cin >> newLandingSiteCode;
			if (routeSystem.ModifyRoute(modifyRouteCode, newDepartureSiteCode, newLandingSiteCode) == true) {
				cout << "Modify success!" << endl;
			}
			else {
				cout << "Can't modify this route!" << endl;
			}
			Sleep(500);
			_getch();
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
	//SavingSystem savingSystem;
	//savingSystem.ReadingFromFile();
	while (ifExit != true) {
		Sleep(100);
		cout << "1.Site System" << endl
			 << "2.Route System" << endl
			 << "3.Flight System" << endl
			 << "4.Ticketing System" << endl
		  	 << "5.Save" << endl
			 << "6.Read" << endl
			 << "7.Exit" << endl;
		

		cin >> action;
		Sleep(100); // 添加延迟让输出更稳定
		system("cls");
		switch (action) {
		case 1:
			Sleep(100);
			SiteScreen();
			break;
		case 2:
			Sleep(100);
			RouteScreen();
			break;
		case 3:
			Sleep(100);
			FlightScreen();
			break;
		case 4:
			Sleep(100);
			TicketingScreen();
			break;
		case 5:
			Sleep(100);
			savingSystem.SavingToFile();
			cout << "Save success!" << endl;
			Sleep(500); // 增加成功提示显示时间
			_getch();
			system("cls");
			break;
		case 6:
			Sleep(100);
			savingSystem.ReadingFromFile();
			cout << "Read success!" << endl;
			Sleep(500); // 增加成功提示显示时间
			_getch();
			system("cls");
			break;
		case 7:
			Sleep(100);
			ifExit = true;
			break;
		default:
			Sleep(100);
			cout << "Invalid input!" << endl;
			Sleep(1000);
			system("cls");
			break;
		}
	}
}


int main()
{
	HomeScreen();
}