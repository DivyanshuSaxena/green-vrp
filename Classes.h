#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

class Vehicle {
public:
	int type;
	int id;
	vector<Node> route;
	double totalCost;
	double fixedCost;
	double chargingCost;
	double travellingCost;
	double waitingCost;
	int distanceTravelled;
	double currentCapWeight;
	double currentCapVol;
	time_t serviceStartTime;
	time_t serviceEndTime;
	int currentChargingDistance;    // distance can be covered by current charging level 

//ADD--currentNodeid named int for getting current node's id.
};

class Node {
public:
	int id;

};

class Customer {
	int id;
	double demandWeight;
	double demandVol;
	time_t timeWindowStarts;
	time_t timeWindowEnds;

};