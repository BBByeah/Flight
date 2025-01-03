#pragma once
#include <vector>
#include <ctime>     
using namespace std;

class Site {
public:
	int siteCode;
	double longitude;
	double latitude;
	char siteName[20];
	vector<int> relatedRouteCode;
};

class Route {
public:
	int routeCode;
	int relatedSites[2];
	double distance;
	double price[3];//依次是头等舱，公务舱，经济舱的价格
	tm duration;
};

class Flight {
public:
	int startSiteCode;
	int endSiteCode;
	//途经航线
	struct PassingByRoute {
		int routeCode;
		PassingByRoute* nextRoute;
	}routeHead;
	tm departureTime;
	tm landingTime;
	double totalPrice[3];
	tm totalDuration;
};