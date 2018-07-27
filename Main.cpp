#include <iostream>
#include "Classes.h"
using namespace std;

void fillGlobalVariables();

int main() {

	vector<Vehicle> vehiclepool;
	vector<Node> customerpool;//consisting only of customers. NOT"charging station" NOT"depot"
	int currentvehicle=0;

	fillGlobalVariables();

	while(customerpool.size()!=0){
		bool stoppingcondition=false;

		Vehicle v;//new object of type:vehicle
		//intialize the members of object "v" of type Vehicle 
		vehiclepool.push_back(v);
		// vehiclepool.get(currentvehicle).addNode(depot);
		while(stoppingcondition!=true){
			Node mincustomer;
			double minCost=-1;
			double checkcost;

			for(int c=0;c<customerpool.size();c++){
				if(vehiclepool.get(currentvehicle).feasible(c)==true){
					checkcost=vehiclepool.get(currentvehicle).totalcost + checknewCustomerCost(c.id , vehiclepool.get(currentvehicle).currentNodeid) ;
					//checknewCustomerCost should give travellingCost+waitingCost here.
					if(minCost>checkcost || minCost==-1){
						mincustomer= c;
						minCost=checkcost;
					}
				
				}
			}

		if(minCost!=-1){
			vehiclepool.get(currentvehicle).addNode(mincustomer);
			customerpool.remove(mincustomer);
		}
		else{//NO customer is feasible for adding
			stoppingcondition= functionAddingChargingStationOrDepot(vehiclepool.get(currentvehicle));
		}	



		}
	currentvehicle++;

	}
	// All customers are served until this line.
	return 0;
}

// stoppingcondition--will be true if vehicle timing is over w.r.t. customers.//after that we will add new vehicle.

void fillGlobalVariables() {
	// Call certain file from here which will scan .xls(excel) file
	// and fill customerpool accordingly.

}