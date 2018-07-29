#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

#define infinity 999999999;
typedef double time_type;

class Vehicle {
public:
	Vehicle();
	int type;
	int id;
	vector<Node> route;
	
	double totalCost;
	double chargingCost;
	double travellingCost;
	double waitingCost;
	
	double currentCapWeight;
	double currentCapVol;
	double distanceTravelled;
	
	time_type serviceStartTime;
	time_type serviceEndTime;
	double distanceRemaining;    				// Distance can be covered by current charging level
	int currentNodeId;						// This must be updated whenever a change in the route is made

	bool timingCondition(Customer);			// Checks if the timing conditions shall be satisfied if Customer is added at the end of the current route
	bool capacityCondition(Customer);		// Checks the capacity constraints (Both Volume and Weight)
	bool chargingCondition(Customer);		// Checks the charging constraints
	bool feasible(int);						// Checks all the conditions together

	void addCustomer(int);				// Adds Customer at the end of the current route and updates all costs
	void addCustomerCS(int, int);
	void addCustomerDepot(int);

	double costAddCustomerCS(Customer,int); // Returns cost of adding customer at the end of the current route after adding Charging Station
	double costAddCustomerDepot(Customer);	// Returns cost of adding customer at the end of the current route after adding Depot
	void updateTotalCost();
	
	bool checkRouteFeasibility();
	bool addChargingStationOrDepot();
};

class Node {
public:
	Node();
	int id;
	time_type arrival_time;
	time_type departure_time;
};

class Customer {
public:
	int id;
	// double latitude, longitude;
	double demandWeight;
	double demandVol;
	double lng,lat;
	time_type timeWindowStarts;
	time_type timeWindowEnds;

	int findNearestCS() {
		double minCost = -1;
		int nearestCS = -1;
		for(int id = csStartId; id <= csEndId; id++) {
			double cost = travelCosts.at(id).at(this->id);
			if ((minCost > cost) || nearestCS == -1) {
				nearestCS = id;
				minCost = cost;
			} 
		}
		return nearestCS;
	}
};

vector<Customer> customers;
vector<Vehicle> vehicles;

// Numbers
int numChargingStations;
int numCustomers;
int numNodes;

// Starting and End Ids
int mainDepotId;
int csStartId, csEndId;					// Charging Station Start and End Id
int custStartId, custEndId;				// Customers Start and End Id

// Vehicle Constants
double capVolType1, capVolType2;
double capWeightType1, capWeightType2;
double distanceType1, distanceType2;
double fixedCost1, fixedCost2;
double unitTransCost1, unitTransCost2;
double chargeTime1, chargeTime2;

// Miscellaneous
time_type serviceTime=30;					// Service time for customers
time_type startTime, endTime;
time_type chargingTimeCS, chargingTimeDepot;

// Factors
int waiting_factor;
int charging_factor;
double chargingCostStation;
double waitingCostDepot;

vector<vector<double>> travelCosts;		// To be pre-processed based on the data form input
vector<vector<double>> travelDistance;		// To be pre-processed based on the data form input
vector<vector<time_type>> travelTimes;	// To be input from the user
vector<int> customerPool;				// The vector that will store the indexes of all Customers (in customers vector) that have not been added in any of the vehicles