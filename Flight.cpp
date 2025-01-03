#include <iostream>
#include "dataType.h"
#include <vector>
using namespace std;

vector<Site> siteList;

void ShowSiteList() {
	for (Site site : siteList) {
		cout << site.siteCode << site.longitude << site.latitude << site.siteName << endl;
	}
}

void AddNewSite() {
	Site newSite;
	cin >> newSite.siteCode >> newSite.longitude >> newSite.latitude >> newSite.siteName;
	siteList.push_back(newSite);
}

void MainInterface() {
	bool ifExit = false;
	int action = 0;
	while (ifExit != true) {
		cout << "Please choose an action:" << endl;
		cout << "1.add new site" << endl << "2.show site list" << endl;
		cin >> action;
		switch (action) {
		case 1:
			AddNewSite();
			break;
		case 2:
			ShowSiteList();
			break;
		default:
			break;
		}
	}
	
}

int main()
{
	MainInterface();
}