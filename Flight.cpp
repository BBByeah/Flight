#include <Windows.h>
#include <conio.h>

#include <stdexcept>
#include <limits>
#include <iostream>
#include "dataType.h"
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

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
				<< "4.Back" << endl;
			cin >> action;
			Sleep(100);
			system("cls");
			switch (action) {
			case 1:
				Sleep(100);
				SortSiteListByCode();
				ifEnd = true;
				break;
			case 2:
				Sleep(100);
				SortSiteListByName();
				ifEnd = true;
				break;
			case 3:
				Sleep(100);
				ifEnd = true;
				break;
			case 4:
				Sleep(100);
				ifShow = false;
				ifEnd = true;
				break;
			}
		}

		if (ifShow == true) {
			Sleep(100);
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

	void SortRouteList(SortType sortType) {
		vector<time_t> timeVector;
		vector<string> nameVector;
		vector<int> codeVector;

		// 根据不同排序类型准备数据
		for (auto route : routeList) {
			switch (sortType) {
			case ByTimeLength:
				timeVector.push_back(route.timeLength);
				break;
			case ByName:
				nameVector.push_back(route.routeName); 
				break;
			case ByCode:
				codeVector.push_back(route.routeCode);
				break;
			default:
				cout << "Invalid sort type!" << endl;
				return;
			}
		}

		// 获取排序后的索引
		vector<int> sortedIndex;
		switch (sortType) {
		case ByTimeLength:
			sortedIndex = SortByTimeLength(timeVector);
			break;
		case ByName:
			// 按名称字母顺序排序
			sort(nameVector.begin(), nameVector.end());
			break;
		case ByCode:
			// 按编号大小排序
			sort(codeVector.begin(), codeVector.end());
			break;
		}

		// 显示排序后的路线列表
		ShowRouteList();
	}

	void ShowRouteList() {
		if (routeList.empty()) {
			cout << "No routes available!" << endl;
			return;
		}

		cout << "Route List:" << endl;
		cout << setw(10) << "Code" 
			 << setw(20) << "Name"
			 << setw(15) << "Start Site"
			 << setw(15) << "End Site"
			 << setw(15) << "Time(min)" << endl;
		
		for (const auto& route : routeList) {
			cout << setw(10) << route.routeCode
				 << setw(20) << route.routeName
				 << setw(15) << route.startSite
				 << setw(15) << route.endSite
				 << setw(15) << route.timeLength << endl;
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
		routeCsv << "RouteCode,StartSite,EndSite,Distance,EconomyPrice,BusinessPrice,FirstClassPrice,Duration\n";
		for (auto route : routeList) {
			routeCsv << route.routeCode << ","
				<< route.relatedSites[0] << ","
				<< route.relatedSites[1] << ","
				<< route.distance << ","
				<< route.price[0] << ","
				<< route.price[1] << ","
				<< route.price[2] << ","
				<< route.duration << "\n";
		}
		routeCsv.close();

		// Save flight information
		ofstream flightCsv("flights.csv");
		flightCsv << "Status,StartSite,EndSite,DepartureTime,ArrivalTime,EconomyRemaining,BusinessRemaining,FirstClassRemaining,EconomyPrice,BusinessPrice,FirstClassPrice,TotalDuration\n";
		for (auto flight : flightList) {
			flightCsv << flight.ifValidFlight << ","
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
				<< flight.totalDuration << "\n";
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

				if (getline(ss, token, ',')) flight.ifValidFlight = (token == "1");
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
		cout << "Please choose an action:" << endl;

		cin >> action;
		system("cls");
		switch (action) {
		case 1:
			Sleep(100);
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
	SavingSystem savingSystem;
	while (ifExit != true) {
		Sleep(100);
		cout << "1.Site System" << endl
			 << "2.Route System" << endl
			 << "3.Flight System" << endl
			 << "4.Ticketing System" << endl
		  	 << "5.Save" << endl
			 << "6.Read" << endl
			 << "7.Exit" << endl;
		cout << "Please choose an action:" << endl;

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
/*
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
*/
	HomeScreen();
}