#include "Classes.h"
#include <iostream>
using namespace std;

bool Vehicle::timingCondition(Customer customer) {
    
}
bool functionAddingChargingStationOrDepot(Vehicle curr_Vehicle)
{
    double minCost=-1;
    for(unsigned i=0; i<Customerpool.size();i++)
    {
        if(timingCondition(Customerpool[i]))
        {
            if (capacityCondition(Customerpool[i]))
            {
                if(chargingCondition(Customerpool[i]))
                {
                    //calculate distance
                    //update minCOst
                }
                else
                {
                    //add charging station
                    //update min
                }
            }
            else
            {
                //add depot
                //update min
            }
        }
        if(minCost==-1)
        {
            //add to vehicle the customer with min cost
        }
        else
        {
            //return false which means depot need to be added and vehicle is retur
        }


    }
}