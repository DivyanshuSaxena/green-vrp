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
bool functionAddingChargingStationOrDepot(Vehicle curr_Vehicle)
{
    for(unsigned i=0; i<Customerpool.size();i++)
    {
        double minCost=-1;
        if(timingCondition(Customerpool[i]))
        {
            if (capacityCondition(Customerpool[i]))
            {
                if(!chargingCondition(Customerpool[i]))//if charging condition is not satisfied
                {
                    //add charging station
                    curr_Vehicle.push_back(FindNearestChargingStation(i));
                    //Find the nearest charging station
                    //Then Calculate Cost
                    CalculateCost(curr_Vehicle);
                    //update min
                    if(currCost<minCost)
                    {
                        minCost=currCost;
                        minID=i;
                    }
                curr_Vehicle.pop();//remove
                    

                }//this should not happen
                else{
                    cout<<"There is some Error";
                    std::exit(0);
                }
            }
            else
            {
                //Add depot
                curr_Vehicle.push_back(mainDepotId);
                //Calculate Cost
                CalculateCost(Customerpool[i]));
                if(currCost<minCost)
                {                    
                    minCost=currCost;
                    minID=i;
                }
                curr_Vehicle.pop();//remove
                // curr_Vehicle.add(Customerpool[i]);
                
                //update min
            }
        }
        if(minCost==-1)
        {
            curr_Vehicle.push_back(min_ID);
            //update solutioncost??
            return true;
        }
        else
        {
            curr_Vehicle.push_back(mainDepotId));
            //update solutioncost??
            return true;
            //return false which means depot need to be added and vehicle is retur
        }
    }

}