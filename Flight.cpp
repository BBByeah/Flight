#include <iostream>
#include "dataType.h"
#include <vector>
#include <iomanip>
#include <stdlib.h>

using namespace std;

vector<Site> siteList;
vector<Route> routeList;
vector<Flight> flightList;
vector<Ticket> ticketList;

enum SortType {
	ByTime,
	ByName
};
enum QueryType {
	Shortest,
	Cheapest
};

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

//TODO
void SiteScreen() {

}

//TODO
void RouteScreen() {

}

//TODO
void FlightScreen() {

}

//TODO
void TicketingScreen() {

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
	HomeScreen();
}