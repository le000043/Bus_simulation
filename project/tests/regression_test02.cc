#include <gtest/gtest.h>
#include "src/local_simulator.h"

#include <vector>
#include <list>

#include <iostream>
#include <fstream> 

#include "src/bus.h"
#include "src/stop.h"
#include "src/route.h"
#include "passenger.h"
#include "src/data_structs.h"
#include "src/random_passenger_generator.h"

class RegTest :public ::testing::Test {
    protected:
    std::list<double> CC_EB_probs;
	std::list<double> CC_WB_probs;

  	Stop ** CC_EB_stops;
  	Stop ** CC_WB_stops;
  	std::list<Stop *> CC_EB_stops_list;
  	std::list<Stop *> CC_WB_stops_list;
  	double * CC_EB_distances;
  	double * CC_WB_distances;
	
    Route * CC_EB;
    Route * CC_WB;
};
// NOTE for whoever run this test, open terminal in test directory and then 
// make. then run ./build/bin/unittest
// then type "diff Reg01_output.txt Reg01_expected.txt". Hit Enter
// if no difference then the test passed
TEST_F (RegTest, Test01) {
    std::ofstream outfile ("Reg01_output.txt");
    CC_EB_stops = new Stop *[3];
    CC_WB_stops = new Stop *[3];
    CC_EB_distances = new double[3];
    CC_WB_distances = new double[3];
    Passenger* passenger01 =  new Passenger(2,"John");
    Passenger* passenger02 =  new Passenger(2,"Dan");
  	Passenger* passenger03 =  new Passenger(2,"Dom");
	Passenger* passenger07 =  new Passenger(2,"Ken");
	Passenger* passenger08 =  new Passenger(2,"NiceGuy");
	Passenger* passenger09 =  new Passenger(2,"NiceGal01");
	Passenger* passenger10 =  new Passenger(2,"NiceGal02");
	Passenger* passenger11 =  new Passenger(2,"NiceGal03");

	Passenger* passenger12 =  new Passenger(2,"NiceGal04");
	Passenger* passenger13 =  new Passenger(2,"NiceGal05");
	Passenger* passenger14 =  new Passenger(2,"NiceGal06");
	Passenger* passenger15 =  new Passenger(2,"NiceGal07");



    Stop * stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
    stop_CC_EB_1->AddPassengers(passenger01);
    stop_CC_EB_1->AddPassengers(passenger02);
    stop_CC_EB_1->AddPassengers(passenger03);

    StopData s1 = stop_CC_EB_1->GetStopData();

  	Stop * stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
    StopData s2 = stop_CC_EB_2->GetStopData();
	stop_CC_EB_2->AddPassengers(passenger07);
	stop_CC_EB_2->AddPassengers(passenger08);
	stop_CC_EB_2->AddPassengers(passenger09); //left off
	stop_CC_EB_2->AddPassengers(passenger10);
	stop_CC_EB_2->AddPassengers(passenger11);


  	Stop * stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);  // last stop
    StopData s3 = stop_CC_EB_3->GetStopData();

	
	 Passenger* passenger04 =  new Passenger(4,"Ninja"); // get off at 4
	 Passenger* passenger05 =  new Passenger(5,"Hacker01");
	 Passenger* passenger06 =  new Passenger(5,"Hacker02");
	 Stop * stop_CC_WB_1 = new Stop(3, 44.975392, -93.226632);
	 stop_CC_WB_1->AddPassengers(passenger04);
	 StopData s4 = stop_CC_WB_1->GetStopData();
	 
	 Stop * stop_CC_WB_2 = new Stop(4, 44.984482, -93.181657);
	 stop_CC_WB_2->AddPassengers(passenger05);
	 stop_CC_WB_2->AddPassengers(passenger06);
	 stop_CC_WB_2->AddPassengers(passenger12);
	 stop_CC_WB_2->AddPassengers(passenger13);
	 stop_CC_WB_2->AddPassengers(passenger14);
	 stop_CC_WB_2->AddPassengers(passenger15); //left off


	 StopData s5 = stop_CC_WB_2->GetStopData();
	 
	 Stop * stop_CC_WB_3 = new Stop(5, 44.983703, -93.178846);  // last stop
	 StopData s6 = stop_CC_WB_3->GetStopData();
	 

    CC_EB_probs.push_back(0);
    CC_EB_probs.push_back(0);
    CC_EB_probs.push_back(0);
    CC_WB_probs.push_back(0);
    CC_WB_probs.push_back(0);
    CC_WB_probs.push_back(0);
    
    CC_EB_stops_list.push_back(stop_CC_EB_1);
  	CC_EB_stops[0] = stop_CC_EB_1;
    CC_EB_stops_list.push_back(stop_CC_EB_2);
  	CC_EB_stops[1] = stop_CC_EB_2;
    CC_EB_stops_list.push_back(stop_CC_EB_3);
  	CC_EB_stops[2] = stop_CC_EB_3;
    CC_EB_distances[0] = 2;
 	CC_EB_distances[1] = 1;
 	
 	CC_WB_stops_list.push_back(stop_CC_WB_1);
  	CC_WB_stops[0] = stop_CC_WB_1;
    CC_WB_stops_list.push_back(stop_CC_WB_2);
  	CC_WB_stops[1] = stop_CC_WB_2;
    CC_WB_stops_list.push_back(stop_CC_WB_3);
  	CC_WB_stops[2] = stop_CC_WB_3;
    CC_WB_distances[0] = 1;
 	CC_WB_distances[1] = 2;
 	
	RandomPassengerGenerator* CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);;
    CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops,CC_EB_distances, 3, CC_EB_generator);
    
    RandomPassengerGenerator* CC_WB_generator = new RandomPassengerGenerator(CC_WB_probs, CC_WB_stops_list);;
    CC_WB = new Route("Campus Connector - Westbound", CC_WB_stops,CC_WB_distances, 3, CC_WB_generator);
	// std::cout << "DONE setting up\n";
    RouteData data1 = CC_EB->GetRouteData(); // UpdateRouteData is called in GetRouteData
    EXPECT_EQ(data1.id,"Campus Connector - Eastbound");
    std::vector<StopData>::iterator it1;
    it1 = data1.stops.begin();
    EXPECT_EQ((*it1).num_people,3);
    
    RouteData data2 = CC_WB->GetRouteData(); // UpdateRouteData is called in GetRouteData
    EXPECT_EQ(data2.id,"Campus Connector - Westbound");
    std::vector<StopData>::iterator it2;
    it2 = data2.stops.begin();
    EXPECT_EQ((*it2).num_people,1);

	// 44.972392, -93.243774
	EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),3);
  // creating new bus then update bus in one time step.
    Bus * bus1 = new Bus ("1000", CC_EB,CC_WB, 5, 1);
    EXPECT_EQ(bus1->GetCapacity(),5);
    EXPECT_EQ(bus1->GetNumPassengers(),3);
    EXPECT_EQ(bus1->GetNextStop(),stop_CC_EB_2);
    EXPECT_EQ(bus1->GetBusPreviousStop()->GetId(),0);

    //output result to txt file
    outfile << "                                   -------BEGIN SIMULATION------\n";
    outfile << "                                   -------Time now is 0------\n";
    bus1->Update();
    CC_EB->Update();
    CC_WB->Update();
    outfile << "~~~~~~~~~Routes report~~~~~~~~~\n";
    CC_EB->Report(outfile);
    CC_WB->Report(outfile);
    outfile << "~~~~~~~~~Busses report~~~~~~~~~\n";
    bus1->Report(outfile);

    for (int i=1;i<=6;i++) {
    outfile << "                                   -------Time now is "<< i <<"------\n";
    outfile << "~~~~~~~~~Routes report~~~~~~~~~\n";    
    bus1->Update();
    CC_EB->Update();
    CC_WB->Update();

    CC_EB->Report(outfile);
    CC_WB->Report(outfile);
    outfile << "~~~~~~~~~Busses report~~~~~~~~~\n";
    bus1->Report(outfile);
    }
    outfile << "                                   -------COMPLETE SIMULATION------\n"; 

    outfile.close();
}