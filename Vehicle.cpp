#include "Classes.h"
#include <iostream>
using namespace std;

bool Vehicle::timingCondition(Customer customer) {
    
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