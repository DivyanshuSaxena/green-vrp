#include "Classes.h"
#include <iostream>
using namespace std;

bool Vehicle::timingCondition(Customer customer) {
    time_type currDeptTime = this->route.at(this->route.size()-1).departure_time;
    return (travelTimes.at(this->currentNodeId).at(customer.id) + currDeptTime) < customer.timeWindowEnds;
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
    double distance = travelCosts.at(this->currentNodeId).at(customer.id);
    return (this->distanceRemaining > distance);
}

void Vehicle::updateTotalCost() {
    double fixedCost = this->type==1 ? fixedCost1 : fixedCost2;
    this->totalCost = this->travellingCost + this->waitingCost + this->chargingCost + fixedCost;
}

void Vehicle::addCustomer(Customer customer) {
    Node node;
    node.id = customer.id;
    time_type timeTaken = travelTimes.at(this->currentNodeId).at(customer.id);
    double travelCost = travelCosts.at(this->currentNodeId).at(customer.id);
    
    node.arrival_time = this->route.back().departure_time + timeTaken;
    node.departure_time = node.arrival_time + serviceTime;
    this->currentNodeId = customer.id;
    this->route.push_back(node);
    
    // Update costs
    this->travellingCost += travelCost;
    double waitCost = (customer.timeWindowStarts > node.arrival_time) ? (customer.timeWindowStarts - node.arrival_time)*waiting_factor : 0; 
    this->waitingCost += waitCost;
    updateTotalCost();
}