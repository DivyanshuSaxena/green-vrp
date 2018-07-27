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
	int distanceRemaining;    	// distance can be covered by current charging level
	int currentNodeId;			// This must be updated whenever a change in the route is made

	bool timingCondition(Customer);
	bool capacityCondition(Customer);
	bool chargingCondition(Customer);
	void addCustomer(Customer);
	bool checkRouteFeasibility();
};

class Node {
public:
	int id;
	time_t arrival_time;
	time_t departure_time;
};

class Customer {
public:
	int id;
	double demandWeight;
	double demandVol;
	time_t timeWindowStarts;
	time_t timeWindowEnds;
};

vector<Customer> customers;

// Numbers
int numChargingStations;
int numCustomers;
int numNodes;

// Starting and End Ids
int mainDepotId;
int csStartId, csEndId;
int custStartId, custEndId;

// Vehicle Constants
double capVolType1, capVolType2;
double capWeightType1, capWeightType2;
double distanceType1, distanceType2;

vector<vector<double>> travelCosts;
vector<vector<time_t>> travelTimes;