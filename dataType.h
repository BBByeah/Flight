#pragma once
#include <vector>
#include <ctime>     
using namespace std;

struct Site {
	int siteCode;
	double longitude;
	double latitude;
	char siteName[20];
	vector<int> relatedRouteCode;
};

struct Route {
	int routeCode;
	int relatedSites[2];
	double distance;
	double price[3];//依次是头等舱，公务舱，经济舱的价格
	tm duration;
};

struct Flight {
	bool ifValidFlight = false;
	int startSiteCode;
	int endSiteCode;
	//途经航线
	struct PassingByRoute {
		int routeCode;
		PassingByRoute* nextRoute;
	}routeHead;
	tm departureTime;
	tm landingTime;
	int remainingTickets[3];
	double totalPrice[3];
	tm totalDuration;
};

struct Ticket {
	int flightCode;
	int customerID;
	char customerName[20];
	tm boughtTime;
};