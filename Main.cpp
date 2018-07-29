#include <iostream>
#include <fstream>
#include "Classes.h"
using namespace std;


	const int depot=0;
	const int startCustomer=1,endCustomer=1000;
	const int startCharging=1001,endCharging=1100;

void fillGlobalVariables();
double checknewCustomerCost(int id1,int id2);

int main() {

	vector<Vehicle> vehiclepool;
	vector<int> customerpool;//consisting only of customers. NOT"charging station" NOT"depot"
	int currentvehicle=0;


	fillGlobalVariables();

	while(customerpool.size()!=0){
		bool stoppingcondition=false;

		Vehicle v;//new object of type:vehicle
		//intialize the members of object "v" of type Vehicle 
		vehiclepool.push_back(v);
		// vehiclepool.get(currentvehicle).addNode(depot);
		while(stoppingcondition!=true){
			int mincustomer;
			double minCost=-1;
			double checkcost;

			for(int counter=0;counter<customerpool.size();counter++){
				if(vehiclepool.at(currentvehicle).feasible(customerpool.at(counter) )==true){
					checkcost=vehiclepool.at(currentvehicle).totalcost + checknewCustomerCost(customerpool.at(counter) , vehiclepool.at(currentvehicle).currentNodeid) ;
					//checknewCustomerCost should give travellingCost+waitingCost here.
					if(minCost>checkcost || minCost==-1){
						mincustomer= customerpool.at(counter);
						minCost=checkcost;
					}
				
				}
			}

		if(minCost!=-1){
			vehiclepool.at(currentvehicle).addCustomer(mincustomer);
			customerpool.remove(mincustomer);
		}
		else{//NO customer is feasible for adding
			stoppingcondition= functionAddingChargingStationOrDepot(vehiclepool.at(currentvehicle));
		}	



		}
	currentvehicle++;

	}
	// All customers are served until this line.
	return 0;
}

// stoppingcondition--will be true if vehicle timing is over w.r.t. customers.//after that we will add new vehicle.

void fillGlobalVariables() {
	// Call certain file from here which will scan .csv(excel) file
	// and fill customerpool accordingly.

	//reading vehicle type below
	ifstream infile;
	infile.open("input_vehicle_type.csv");
	

		string temp;
		getline(infile,temp,'\n');

	    getline(infile,temp,',');//id
	    getline(infile,temp,',');//type
	    getline(infile,temp,',');//vol max
		capVolType1=stod(temp);
	    getline(infile,temp,',');//max weight
		capVolType1=stod(temp);	

	    getline(infile,temp,',');//driving cnt--unlimited

	    getline(infile,temp,',');//driving range--per full charge
		distanceType1=stod(temp);
		
	    getline(infile,temp,',');//charging time--sae for both
		chargeTime1=stod(temp);
		
	    getline(infile,temp,',');//unit cost--per distance
		unitTransCost1=stod(temp);
		
	    getline(infile,temp,'\n');//fixed cost
		fixedCost1=stod(temp);
		

	    getline(infile,temp,',');
	    getline(infile,temp,',');
	    getline(infile,temp,',');
		capVolType2=stod(temp);
	    getline(infile,temp,',');
		capVolType2=stod(temp);	

	    getline(infile,temp,',');

	    getline(infile,temp,',');
		distanceType2=stod(temp);
		
	    getline(infile,temp,',');
		chargeTime2=stod(temp);
		
	    getline(infile,temp,',');
		unitTransCost2=stod(temp);
		
	    getline(infile,temp,'\n');
		fixedCost2=stod(temp);
		//readingn vehicle info end
		//input of distance_time begins

		std::string file_path= "input_distance-time.txt";
	//   std::cout<<"hi"<<std::endl;
		std::ifstream fin(file_path.c_str());
		// std::cout<<"hi"<<std::endl;
		std::string temp;
		getline(fin, temp);//ignoring the first line with heading
		for(long i=0;i<=1211099;i++)
		{
			long fromNode,toNode;
			getline(fin,temp,',');
			fromNode=stoi(temp);
			getline(fin,temp,',');
			toNode=stoi(temp);
			getline(fin,temp,',');

			travelDistance[fromNode][toNode]=stod(temp);
			getline(fin,temp,',');
			travelTimes[fromNode][toNode]=stod(temp);
		}
		//distance-time input end between nodes
		//reading the input_node file below

		numChargingStations=100;
		numCustomers=1000;

		for (int k=1;k<=numCustomers;k++){
			customerpool.push_back(k);
		}//1-1000

		numNodes=1101;
		ifstream infile;
		infile.open("input_vehicle_type.csv");
		string s_temp;
		getline(infile,s_temp,'\n');//enter heading lines
		//importing depot info

		Customer depot;
		getline(infile,s_temp,',');//id
		depot.id=stoi(s_temp);
		getline(infile,s_temp,',');//type
		getline(infile,s_temp,',');//lng
		// depot.lng=stod(s_temp);
		getline(infile,s_temp,',');//lat
		// depot.lat=stod(s_temp);
		getline(infile,s_temp,',');
		getline(infile,s_temp,',');
		getline(infile,s_temp,',');//start time
/*debug it*/		depot.timeWindowStarts=stoi(s_temp);
		getline(infile,s_temp,'\n');//end time
/*debug it*/		depot.timeWindowEnds=stoi(s_temp);
		
		customers.push_back(depot);
		
		
		
		
		
		
		getline(infile,s_temp,',');
		
		for(int i=1;i<=1000;i++)
		{
			string s_temp;
			Customer tempNode;
			getline(infile,s_temp,',');//id
			tempNode.id=stoi(s_temp);
			getline(infile,s_temp,',');//type
			getline(infile,s_temp,',');//lng
			// tempNode.lng=stod(s_temp);
			getline(infile,s_temp,',');//lat
			// tempNode.lat=stod(s_temp);
			getline(infile,s_temp,',');//weight
			tempNode.demandWeight=stod(s_temp);
			getline(infile,s_temp,',');//volume
			tempNode.demandVol=stod(s_temp);			
			getline(infile,s_temp,',');//start time
	/*debug it*/		tempNode.timeWindowStarts=stoi(s_temp);
			getline(infile,s_temp,'\n');//end time
	/*debug it*/		tempNode.timeWindowEnds=stoi(s_temp);
			
			customers.push_back(tempNode);
		}
		for(int i=1001;i<=1100;i++)
		{
			string s_temp;
			Customer csNode;
			getline(infile,s_temp,',');//id
			csNode.id=stoi(s_temp);
			getline(infile,s_temp,',');//type
			getline(infile,s_temp,',');//lng
			// csNode.lng=stod(s_temp);
			getline(infile,s_temp,',');//lat
			// csNode.lat=stod(s_temp);
			getline(infile,s_temp,',');//weight
			getline(infile,s_temp,',');//volume
			getline(infile,s_temp,',');//start time
			getline(infile,s_temp,'\n');//end time
			
			customers.push_back(csNode);

		}
//reading input node end




	    // getline(infile,capVolType1,',');

		// getline(infile,capWeightType1,',');
	    // getline(infile,temp,',');
	    // getline(infile,distanceType1,',');
	    // getline(infile,chargeTime1,',');
	    // getline(infile,unitTransCost1,',');
	    // getline(infile,fixedCost1,'\n');

	    // getline(infile,temp,',');
	    // getline(infile,temp,',');
	    // getline(infile,capVolType2,',');
	    // getline(infile,capWeightType2,',');
	    // getline(infile,temp,',');
	    // getline(infile,capVolType2,',');
	    // getline(infile,chargeTime2,',');
	    // getline(infile,unitTransCost2,',');
	    // getline(infile,fixedCost2,'\n');
		


		
		


    // vector<char*> values;
    // const int MAXSIZE = 4;
    // char thisVal[MAXSIZE];
    // while(in.getline(thisVal,MAXSIZE,',')) {
    //     values.resize(values.size() + 1);
    //     values.back() = new char[MAXSIZE];
    //     strcpy(values.back(), thisVal);
    // }
    // in.close();
    // for (char* cp: values) cout<<*cp<<endl;


	
}

double checknewCustomerCost(int id1,int id2){
	double waitingcostid12,travellingcostid12; //id1--id2
	 travellingcostid12=travelDistance[id1][id2] * unitTransCost1;

	 time_type currDeptTime = vehiclepool.at(currentvehicle).route.at(vehiclepool.at(currentvehicle).route.size()-1).departure_time;
	  if((travelTimes.at(id1).at(id2) + currDeptTime) < customers.at(id2).timeWindowStarts){
	  	waitingcostid12=(customers.at(id2).timeWindowStarts - (travelTimes.at(id1).at(id2) + currDeptTime)) * 24; //no varible here just value check agan
	  }
	  else{
	  waitingcostid12= 0; 	
	  }

		  double totalcostid12=waitingcostid12+travellingcostid12;
		 return totalcostid12;


}