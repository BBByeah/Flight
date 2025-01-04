#pragma once
#include <vector>
#include <ctime>  
#include <string>
using namespace std;

struct Site {
	int siteCode;
	double longitude;
	double latitude;
	string siteName;
	vector<int> relatedRouteCode;
};

struct Route {
	int routeCode;
	int relatedSites[2];
	double distance;
	double price[3];//依次是头等舱，公务舱，经济舱的价格
	time_t duration;
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
	time_t departureTime;
	time_t landingTime;
	int remainingTickets[3];
	double totalPrice[3];
	time_t totalDuration;
};

struct Ticket {
	int flightCode;
	int customerID;
	char customerName[20];
	time_t boughtTime;
};
