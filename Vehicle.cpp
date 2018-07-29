#include "Classes.h"
#include <iostream>
using namespace std;

Vehicle::Vehicle() {
    // Add depot at both ends of the route
    type = 1;
    currentNodeId = 0;
    Node start;
    start.id = 0;
    start.arrival_time = -1;
    start.departure_time = startTime;
    Node end;
    end.id = 0;
    end.arrival_time = 0;
    end.departure_time = -1;
    this->route.push_back(start);
    this->route.push_back(end);
}

bool Vehicle::feasible(int customerid) {
	bool timingbool=timingCondition(customers.at(customerid));
	bool chargingbool=chargingCondition(customers.at(customerid));
	bool capacitybool=capacityCondition(customers.at(customerid));
	bool feasiblebool= timingbool && chargingbool && capacitybool ;
	return feasiblebool;
}

bool Vehicle::timingCondition(Customer customer) {
    time_type currDeptTime = this->route.at(this->route.size()-2).departure_time;
    time_type expectedTime = travelTimes.at(this->currentNodeId).at(customer.id) + currDeptTime;
    time_type timeToEnd = travelTimes.at(0).at(customer.id);
    this->route.back().arrival_time = expectedTime + serviceTime + timeToEnd;
    return (expectedTime < customer.timeWindowEnds && this->route.back().arrival_time < endTime);
}

bool Vehicle::capacityCondition(Customer customer) {
    double volumeCap = this->type==1 ? capVolType1 : capVolType2;
    double weightCap = this->type==2 ? capVolType1 : capVolType2;
    bool volume = (this->currentCapVol + customer.demandVol) <= volumeCap;
    bool weight = (this->currentCapWeight + customer.demandWeight) <= weightCap;
    return (volume && weight);
}

bool Vehicle::chargingCondition(Customer customer) {
    // Distance till Depot check must be thought of
    // Find the nearest charging station to the customer
    double distance = travelCosts.at(this->currentNodeId).at(customer.id) + travelCosts.at(0).at(customer.id) - travelCosts.at(this->currentNodeId).at(0);
    return (this->distanceRemaining > distance);
}

void Vehicle::updateTotalCost() {
    double fixedCost = this->type==1 ? fixedCost1 : fixedCost2;
    this->totalCost = this->travellingCost + this->waitingCost + this->chargingCost + fixedCost;
}

double Vehicle::costAddCustomerCS(Customer customer, int chargingStation) {
    double costNodeCS = travelCosts.at(this->currentNodeId).at(chargingStation);
    double costCustomerCS = travelCosts.at(customer.id).at(chargingStation);
    double endCost = travelCosts.at(customer.id).at(0);
    double additionCost = costNodeCS + costCustomerCS + endCost - travelCosts.at(this->currentNodeId).at(0);
    return additionCost;
}

double Vehicle::costAddCustomerDepot(Customer customer) {
    double costCustDepot = travelCosts.at(customer.id).at(0);
    return 2*costCustDepot;
}

void Vehicle::addCustomer(int customerId) {
    Customer customer = customers.at(customerId);
    Node node;
    node.id = customer.id;
    time_type timeTaken = travelTimes.at(this->currentNodeId).at(customer.id);
    double travelCost = travelCosts.at(this->currentNodeId).at(customer.id);
    
    node.arrival_time = this->route.at(this->route.size()-2).departure_time + timeTaken;
    node.departure_time = node.arrival_time + serviceTime;
    this->currentNodeId = customer.id;
    auto it = this->route.end();
    this->route.insert(--it, node);
    // Update costs
    double factor = this->type == 1 ? unitTransCost1 : unitTransCost2;
    this->travellingCost += (travelCost * factor);
    double waitCost = (customer.timeWindowStarts > node.arrival_time) ? (customer.timeWindowStarts - node.arrival_time)*waiting_factor : 0; 
    this->waitingCost += waitCost;
    updateTotalCost();
}

void Vehicle::addCustomerCS(int customerId, int chargingStation) {
    Node cs;
    cs.id = chargingStation;
    time_type timeToCS = travelTimes.at(this->currentNodeId).at(chargingStation);
    double travelCostCS = travelCosts.at(this->currentNodeId).at(chargingStation);
    cs.arrival_time = this->route.at(this->route.size()-2).departure_time + timeToCS;
    cs.departure_time = cs.arrival_time + chargingTimeCS;
    this->currentNodeId = chargingStation;
    auto it = this->route.end();
    this->route.insert(--it, cs);
    
    Node node;
    node.id = customerId;
    Customer customer = customers.at(customerId);
    time_type timeTaken = travelTimes.at(this->currentNodeId).at(customer.id);
    double travelCost = travelCosts.at(this->currentNodeId).at(customer.id);
    node.arrival_time = this->route.at(this->route.size()-2).departure_time + timeTaken;
    node.departure_time = node.arrival_time + serviceTime;
    this->currentNodeId = customer.id;
    it = this->route.end();
    this->route.insert(--it, node);

    // Update costs
    this->travellingCost += (travelCost + travelCostCS);
    double waitCost = (customer.timeWindowStarts > node.arrival_time) ? (customer.timeWindowStarts - node.arrival_time)*waiting_factor : 0; 
    this->waitingCost += waitCost;
    this->chargingCost += chargingCostStation;
    updateTotalCost();
}

void Vehicle::addCustomerDepot(int customerId) {
    Customer customer = customers.at(customerId);
    Node depot;
    depot.id = 0;
    this->currentNodeId = 0;
    time_type timeToDepot = travelTimes.at(this->currentNodeId).at(0);
    time_type timeDepotToCustomer = travelTimes.at(0).at(customer.id);
    double travelCostDepot = travelCosts.at(this->currentNodeId).at(0);
    depot.arrival_time = this->route.at(this->route.size()-2).departure_time + timeToDepot;
    depot.departure_time = depot.arrival_time + chargingTimeDepot;
    auto it = this->route.end();
    this->route.insert(--it, depot);

    Node node;
    node.id = customerId;
    node.arrival_time = depot.departure_time + timeDepotToCustomer;
    node.departure_time = node.arrival_time + serviceTime;
    this->currentNodeId = customer.id;
    it = this->route.end();
    this->route.insert(--it, node);

    // Update costs
    double travelCost = travelCosts.at(this->currentNodeId).at(customer.id);
    this->travellingCost += travelCost;
    double waitCost = (customer.timeWindowStarts > node.arrival_time) ? (customer.timeWindowStarts - node.arrival_time)*waiting_factor : 0; 
    this->waitingCost += (waitCost + waitingCostDepot);
    updateTotalCost();
}

bool Vehicle::addChargingStationOrDepot()
{
    double minCost = infinity;
    int minCustomerIndex = -1, minChargingStation = -1;
    int typeOfInsertion = -1; // 0 for charging station and 1 for depot
    for(unsigned i=0; i < customerPool.size(); i++)
    {
        Customer customer  = customers.at(customerPool.at(i));
        if(timingCondition(customer))
        {
            if (capacityCondition(customer))
            {
                if(!chargingCondition(customer))//if charging condition is not satisfied
                {
                    int chargingStation = customer.findNearestCS();
                    // Calculate Cost of insertion of customer and charging station
                    double currCost = costAddCustomerCS(customer, chargingStation);
                    if (currCost != -1 && currCost < minCost)
                    {
                        minCost = currCost;
                        minCustomerIndex = i;
                        minChargingStation = chargingStation;
                        typeOfInsertion = 0;
                    }
                }
                else{
                    cout<<"There is some Error";
                    std::exit(0);
                }
            }
            else
            {
                // Add depot and calculate cost
                double currCost = costAddCustomerDepot(customer);
                if (currCost != -1 && currCost < minCost)
                {                    
                    minCost = currCost;
                    minCustomerIndex = i;
                    typeOfInsertion = 1;
                }
            }
        }
    }
    if (minCost == -1) {
        return false;
    }
    // Add the suitable customer
    if (typeOfInsertion == 0) {
        addCustomerCS(minCustomerIndex, minChargingStation);
    } else {
        addCustomerDepot(minCustomerIndex);
    }
    return true;
}