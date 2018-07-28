#include <iostream>
#include <fstream>
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
	// Call certain file from here which will scan .csv(excel) file
	// and fill customerpool accordingly.

	//reading vehicle type below
	ifstream infile;
	infile.open("input_vehicle_type.csv");
	

		string temp;
		getline(infile,temp,'\n');

	    getline(infile,temp,',');
	    getline(infile,temp,',');
	    getline(infile,temp,',');
		capVolType1=stod(temp);
	    getline(infile,temp,',');
		capVolType1=stod(temp);	

	    getline(infile,temp,',');

	    getline(infile,temp,',');
		distanceType1=stod(temp);
		
	    getline(infile,temp,',');
		chargeTime1=stod(temp);
		
	    getline(infile,temp,',');
		unitTransCost1=stod(temp);
		
	    getline(infile,temp,'\n');
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