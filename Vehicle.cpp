#include "Classes.h"
#include <iostream>
using namespace std;

bool Vehicle::timingCondition(Customer customer) {
    time_t currDeptTime = this->route.at(this->route.size()-1).departure_time;
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