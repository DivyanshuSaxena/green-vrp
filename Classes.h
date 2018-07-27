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
	
	double currentCapWeight;
	double currentCapVol;
	int distanceTravelled;
	
	time_t serviceStartTime;
	time_t serviceEndTime;
	int distanceRemaining;    // distance can be covered by current charging level
	int currentNodeId;

	bool timingCondition(Customer);
	bool capacityCondition(Customer);
	bool chargingCondition(Customer);
	void addCustomer(Customer);
	bool checkRouteFeasibility();
	// ADD - currentNodeid named int for getting current node's id.
};

class Node {
public:
	int id;
	time_t arrival_time;
	time_t departure_time;
};

class Customer {
	int id;
	double demandWeight;
	double demandVol;
	time_t timeWindowStarts;
	time_t timeWindowEnds;
};

vector<Customer> customers;
vector<Node> nodes;