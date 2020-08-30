#include <gtest/gtest.h>
#include "src/local_simulator.h"

#include <vector>
#include <list>

#include "src/bus.h"
#include "src/stop.h"
#include "src/route.h"
#include "passenger.h"
#include "src/data_structs.h"
#include "src/random_passenger_generator.h"
// iteration 3's task : fix bus.cc so it can skip top and write 1 small test for it and 1 more general test
class BusTests :public ::testing::Test {
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

TEST_F (BusTests, Test01) {
	/*
   * methods tested: HowManySeatsLeft, NotFull, Update, IsTripComplete,
   *   GetHowManyPassengerOnBus, GetNextStop.
	 * passenger destinations (for later tests)
	 * bus passed this test can move, switch route when needed,
	 * dropping, picking and update passengers on bus correctly.
	 * not including skipping stop.
	 * */
    CC_EB_stops = new Stop *[3];
    CC_WB_stops = new Stop *[3];
    CC_EB_distances = new double[3];
    CC_WB_distances = new double[3];
    Passenger* passenger01 =  new Passenger();
    Passenger* passenger02 =  new Passenger();
  	Passenger* passenger03 =  new Passenger();
	Passenger* passenger07 =  new Passenger();
	Passenger* passenger08 =  new Passenger();
	Passenger* passenger09 =  new Passenger();
    Stop * stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
    stop_CC_EB_1->AddPassengers(passenger01);
    stop_CC_EB_1->AddPassengers(passenger02);
    stop_CC_EB_1->AddPassengers(passenger03);

    StopData s1 = stop_CC_EB_1->GetStopData();

  	Stop * stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
    StopData s2 = stop_CC_EB_2->GetStopData();
	stop_CC_EB_2->AddPassengers(passenger07);
	stop_CC_EB_2->AddPassengers(passenger08);
	stop_CC_EB_2->AddPassengers(passenger09);

  	Stop * stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);  // last stop
    StopData s3 = stop_CC_EB_3->GetStopData();

	
	 Passenger* passenger04 =  new Passenger(4); // get off at 4
	 Passenger* passenger05 =  new Passenger();
	 Passenger* passenger06 =  new Passenger();
	 Stop * stop_CC_WB_1 = new Stop(3, 44.975392, -93.226632);
	 stop_CC_WB_1->AddPassengers(passenger04);
	 StopData s4 = stop_CC_WB_1->GetStopData();
	 
	 Stop * stop_CC_WB_2 = new Stop(4, 44.984482, -93.181657);
	 stop_CC_WB_2->AddPassengers(passenger05);
	 stop_CC_WB_2->AddPassengers(passenger06);
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
    // time 0, don't move, only picking up
    bus1->Update(); 
    CC_EB->Update();
    CC_WB->Update();
    EXPECT_EQ(bus1->GetNumPassengers(),3);
    EXPECT_EQ(bus1->GetHowManyPassengerOnBus(),3);
    BusData busData = bus1->GetBusData();
    EXPECT_EQ(busData.num_passengers,3);
    EXPECT_EQ(bus1->HowManySeatsLeft(),2);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
    // checking passengers update
    EXPECT_EQ(passenger01->IsOnBus(),true);
    EXPECT_EQ(passenger02->IsOnBus(),true);
    EXPECT_EQ(passenger03->IsOnBus(),true);
    EXPECT_EQ(passenger07->IsOnBus(),false);
    EXPECT_EQ(passenger08->IsOnBus(),false);
    EXPECT_EQ(passenger09->IsOnBus(),false);
    EXPECT_EQ(passenger04->IsOnBus(),false);
    EXPECT_EQ(passenger05->IsOnBus(),false);
    EXPECT_EQ(passenger06->IsOnBus(),false);
    
    EXPECT_EQ(passenger01->GetTotalWait(),1);
    EXPECT_EQ(passenger02->GetTotalWait(),1);
    EXPECT_EQ(passenger03->GetTotalWait(),1);
    EXPECT_EQ(passenger07->GetTotalWait(),1);
    EXPECT_EQ(passenger08->GetTotalWait(),1);
    EXPECT_EQ(passenger09->GetTotalWait(),1);
    EXPECT_EQ(passenger04->GetTotalWait(),1);
    EXPECT_EQ(passenger05->GetTotalWait(),1);
    EXPECT_EQ(passenger06->GetTotalWait(),1);
    
    bus1->Update();
    CC_EB->Update();// time 1
    CC_WB->Update();          
    EXPECT_EQ(bus1->GetNextStop(),stop_CC_EB_2);
    busData = bus1->GetBusData();
    EXPECT_EQ(busData.num_passengers,3);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),3);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
    // checking passengers update
    EXPECT_EQ(passenger01->IsOnBus(),true);
    EXPECT_EQ(passenger02->IsOnBus(),true);
    EXPECT_EQ(passenger03->IsOnBus(),true);
    EXPECT_EQ(passenger07->IsOnBus(),false);
    EXPECT_EQ(passenger08->IsOnBus(),false);
    EXPECT_EQ(passenger09->IsOnBus(),false);
    EXPECT_EQ(passenger04->IsOnBus(),false);
    EXPECT_EQ(passenger05->IsOnBus(),false);
    EXPECT_EQ(passenger06->IsOnBus(),false);
    
    EXPECT_EQ(passenger01->GetTotalWait(),2);
    EXPECT_EQ(passenger02->GetTotalWait(),2);
    EXPECT_EQ(passenger03->GetTotalWait(),2);
    EXPECT_EQ(passenger07->GetTotalWait(),2);
    EXPECT_EQ(passenger08->GetTotalWait(),2);
    EXPECT_EQ(passenger09->GetTotalWait(),2);
    EXPECT_EQ(passenger04->GetTotalWait(),2);
    EXPECT_EQ(passenger05->GetTotalWait(),2);
    EXPECT_EQ(passenger06->GetTotalWait(),2);
    
    bus1->Update();
    CC_EB->Update();// time 2, arrive at stop 1
    CC_WB->Update();
    EXPECT_EQ(bus1->GetNextStop(),stop_CC_EB_3);
    busData = bus1->GetBusData();
    EXPECT_EQ(bus1->GetNumPassengers(),5);
    EXPECT_EQ(bus1->HowManySeatsLeft(),0);
    EXPECT_EQ(bus1->NotFull(),false);
    EXPECT_EQ(busData.num_passengers,5);
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
	// checking passengers update
    EXPECT_EQ(passenger01->IsOnBus(),true);
    EXPECT_EQ(passenger02->IsOnBus(),true);
    EXPECT_EQ(passenger03->IsOnBus(),true);
    EXPECT_EQ(passenger07->IsOnBus(),true);
    EXPECT_EQ(passenger08->IsOnBus(),true);
    EXPECT_EQ(passenger09->IsOnBus(),false); // <- bus full :(
    EXPECT_EQ(passenger04->IsOnBus(),false);
    EXPECT_EQ(passenger05->IsOnBus(),false);
    EXPECT_EQ(passenger06->IsOnBus(),false);
    
    EXPECT_EQ(passenger01->GetTotalWait(),3);
    EXPECT_EQ(passenger02->GetTotalWait(),3);
    EXPECT_EQ(passenger03->GetTotalWait(),3);
    EXPECT_EQ(passenger07->GetTotalWait(),3);
    EXPECT_EQ(passenger08->GetTotalWait(),3);
    EXPECT_EQ(passenger09->GetTotalWait(),3);
    EXPECT_EQ(passenger04->GetTotalWait(),3);
    EXPECT_EQ(passenger05->GetTotalWait(),3);
    EXPECT_EQ(passenger06->GetTotalWait(),3);
	
    EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),1);
    bus1->Update();
    CC_EB->Update();// time 3, arrive at stop 2,3
    CC_WB->Update();
    EXPECT_EQ(bus1->GetNextStop(),stop_CC_WB_2);
    busData = bus1->GetBusData();
    EXPECT_EQ(bus1->GetNumPassengers(),1);
    EXPECT_EQ(bus1->HowManySeatsLeft(),4);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(busData.num_passengers,1);
    EXPECT_EQ(bus1->IsTripComplete(),false);	
    // checking passengers update
    EXPECT_EQ(passenger09->IsOnBus(),false); // <- bus full :(
    EXPECT_EQ(passenger04->IsOnBus(),true);
    EXPECT_EQ(passenger05->IsOnBus(),false);
    EXPECT_EQ(passenger06->IsOnBus(),false);
    
    EXPECT_EQ(passenger09->GetTotalWait(),4);
    EXPECT_EQ(passenger04->GetTotalWait(),4);
    EXPECT_EQ(passenger05->GetTotalWait(),4);
    EXPECT_EQ(passenger06->GetTotalWait(),4);
    
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_2->GetNumberOfPassengerAtStop(),2);
	
	
    EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
    bus1->Update();
    CC_EB->Update();// time 4, arrive at stop 4
    CC_WB->Update();
    EXPECT_EQ(bus1->GetNextStop(),stop_CC_WB_3);

    busData = bus1->GetBusData();
    EXPECT_EQ(bus1->GetNumPassengers(),2);
    EXPECT_EQ(bus1->HowManySeatsLeft(),3);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(busData.num_passengers,2);
    EXPECT_EQ(bus1->IsTripComplete(),false);
    
    // checking passengers update
    EXPECT_EQ(passenger09->IsOnBus(),false); // <- bus full :(
    EXPECT_EQ(passenger05->IsOnBus(),true);
    EXPECT_EQ(passenger06->IsOnBus(),true);
    
    EXPECT_EQ(passenger09->GetTotalWait(),5);
    EXPECT_EQ(passenger05->GetTotalWait(),5);
    EXPECT_EQ(passenger06->GetTotalWait(),5);
    
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_2->GetNumberOfPassengerAtStop(),0);
	
	
    EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
    bus1->Update();
    CC_EB->Update();// time 5
    CC_WB->Update();
    EXPECT_EQ(bus1->GetNextStop(),stop_CC_WB_3);
    busData = bus1->GetBusData();
    EXPECT_EQ(bus1->GetNumPassengers(),2);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(busData.num_passengers,2);
    EXPECT_EQ(bus1->IsTripComplete(),false);
    EXPECT_EQ(bus1->GetNextStop(),stop_CC_WB_3);
    
    // checking passengers update
    EXPECT_EQ(passenger09->IsOnBus(),false); // <- bus full :(
    EXPECT_EQ(passenger05->IsOnBus(),true);
    EXPECT_EQ(passenger06->IsOnBus(),true);
    
    EXPECT_EQ(passenger09->GetTotalWait(),6);
    EXPECT_EQ(passenger05->GetTotalWait(),6);
    EXPECT_EQ(passenger06->GetTotalWait(),6);
    
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_2->GetNumberOfPassengerAtStop(),0);
	
	
    EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
    bus1->Update();
    bus1->Update();
    CC_EB->Update();// time 6, arriving at last stop, stop 5
    CC_WB->Update();
    busData = bus1->GetBusData();
    EXPECT_EQ(bus1->GetNumPassengers(),0);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(busData.num_passengers,0);
    EXPECT_EQ(bus1->IsTripComplete(),true);

    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_2->GetNumberOfPassengerAtStop(),0);
    // 6 passengers waiting but only 5 can get on the bus. passenger 6 can't
    bus1->Update(); // this should change nothing
    busData = bus1->GetBusData();
    EXPECT_EQ(bus1->GetNumPassengers(),0);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(busData.num_passengers,0);
    EXPECT_EQ(bus1->IsTripComplete(),true);

     EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_2->GetNumberOfPassengerAtStop(),0);
    delete passenger01;
    delete passenger02;
    delete passenger03;
    delete passenger04;
    delete passenger05;
    delete passenger06;
    delete passenger07;
    delete passenger08;
    delete passenger09;
    delete stop_CC_EB_1;
    delete stop_CC_EB_2;
    delete stop_CC_EB_3;
    delete stop_CC_WB_1;
    delete stop_CC_WB_2;
    delete stop_CC_WB_3;
    delete CC_EB_generator;
    delete CC_EB;
    delete bus1;
    delete CC_EB_stops;
    delete CC_EB_distances;
}
TEST_F (BusTests, Test02) {
	/*
	 * passenger destinations (for later tests)
   * methods that got tested:
   *     
	 * bus passed this test can move, switch route when needed,
	 * dropping, picking and update passengers on bus correctly.
	 * not including skipping stop.
     * this tests that bus will stop when speed is relatively large
	 * */
	// std::cout << "begin test\n";
    CC_EB_stops = new Stop *[3];
    CC_WB_stops = new Stop *[3];
    CC_EB_distances = new double[3];
    CC_WB_distances = new double[3];
    Passenger* passenger01 =  new Passenger();
    Passenger* passenger02 =  new Passenger();
  	Passenger* passenger03 =  new Passenger();
	Passenger* passenger07 =  new Passenger();
	Passenger* passenger08 =  new Passenger();
	Passenger* passenger09 =  new Passenger();
    Stop * stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
    stop_CC_EB_1->AddPassengers(passenger01);
    stop_CC_EB_1->AddPassengers(passenger02);
    stop_CC_EB_1->AddPassengers(passenger03);

    StopData s1 = stop_CC_EB_1->GetStopData();

  	Stop * stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
    StopData s2 = stop_CC_EB_2->GetStopData();
	stop_CC_EB_2->AddPassengers(passenger07);
	stop_CC_EB_2->AddPassengers(passenger08);
	stop_CC_EB_2->AddPassengers(passenger09);

  	Stop * stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);  // last stop
    StopData s3 = stop_CC_EB_3->GetStopData();

	
	 Passenger* passenger04 =  new Passenger(4); // get off at 4
	 Passenger* passenger05 =  new Passenger();
	 Passenger* passenger06 =  new Passenger();
	 Stop * stop_CC_WB_1 = new Stop(3, 44.975392, -93.226632);
	 stop_CC_WB_1->AddPassengers(passenger04);
	 StopData s4 = stop_CC_WB_1->GetStopData();
	 
	 Stop * stop_CC_WB_2 = new Stop(4, 44.984482, -93.181657);
	 stop_CC_WB_2->AddPassengers(passenger05);
	 stop_CC_WB_2->AddPassengers(passenger06);
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
    Bus * bus1 = new Bus ("1001", CC_EB,CC_WB, 5, 999);
    EXPECT_EQ(bus1->GetBusPreviousStop()->GetId(),0);
    //EXPECT_EQ(busData.num_passengers,0);
    
    bus1->Update(); 
    CC_EB->Update();// time 0, created at stop 0
    CC_WB->Update();
    EXPECT_EQ(bus1->GetNumPassengers(),3);
    BusData busData = bus1->GetBusData();
    EXPECT_EQ(busData.num_passengers,3);
    EXPECT_EQ(bus1->HowManySeatsLeft(),2);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
    // checking passengers update
    EXPECT_EQ(passenger01->IsOnBus(),true);
    EXPECT_EQ(passenger02->IsOnBus(),true);
    EXPECT_EQ(passenger03->IsOnBus(),true);
    EXPECT_EQ(passenger07->IsOnBus(),false);
    EXPECT_EQ(passenger08->IsOnBus(),false);
    EXPECT_EQ(passenger09->IsOnBus(),false);
    EXPECT_EQ(passenger04->IsOnBus(),false);
    EXPECT_EQ(passenger05->IsOnBus(),false);
    EXPECT_EQ(passenger06->IsOnBus(),false);
    
    EXPECT_EQ(passenger01->GetTotalWait(),1);
    EXPECT_EQ(passenger02->GetTotalWait(),1);
    EXPECT_EQ(passenger03->GetTotalWait(),1);
    EXPECT_EQ(passenger07->GetTotalWait(),1);
    EXPECT_EQ(passenger08->GetTotalWait(),1);
    EXPECT_EQ(passenger09->GetTotalWait(),1);
    EXPECT_EQ(passenger04->GetTotalWait(),1);
    EXPECT_EQ(passenger05->GetTotalWait(),1);
    EXPECT_EQ(passenger06->GetTotalWait(),1);
    
    bus1->Update(); 
    CC_EB->Update();// time 1, arriving at stop 1
    CC_WB->Update();
    busData = bus1->GetBusData();
    EXPECT_EQ(busData.num_passengers,5);
    EXPECT_EQ(bus1->NotFull(),false);
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
    // checking passengers update
    EXPECT_EQ(passenger01->IsOnBus(),true);
    EXPECT_EQ(passenger02->IsOnBus(),true);
    EXPECT_EQ(passenger03->IsOnBus(),true);
    EXPECT_EQ(passenger07->IsOnBus(),true);
    EXPECT_EQ(passenger08->IsOnBus(),true);
    EXPECT_EQ(passenger09->IsOnBus(),false);
    EXPECT_EQ(passenger04->IsOnBus(),false);
    EXPECT_EQ(passenger05->IsOnBus(),false);
    EXPECT_EQ(passenger06->IsOnBus(),false);
    
    EXPECT_EQ(passenger01->GetTotalWait(),2);
    EXPECT_EQ(passenger02->GetTotalWait(),2);
    EXPECT_EQ(passenger03->GetTotalWait(),2);
    EXPECT_EQ(passenger07->GetTotalWait(),2);
    EXPECT_EQ(passenger08->GetTotalWait(),2);
    EXPECT_EQ(passenger09->GetTotalWait(),2);
    EXPECT_EQ(passenger04->GetTotalWait(),2);
    EXPECT_EQ(passenger05->GetTotalWait(),2);
    EXPECT_EQ(passenger06->GetTotalWait(),2);
    
    bus1->Update();
    CC_EB->Update();// time 2, arrive at stop 2,3
    CC_WB->Update();
    busData = bus1->GetBusData();
    EXPECT_EQ(bus1->GetNumPassengers(),1);
    EXPECT_EQ(bus1->HowManySeatsLeft(),4);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(busData.num_passengers,1);
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
	// checking passengers update
    EXPECT_EQ(passenger09->IsOnBus(),false); // <- bus full :(
    EXPECT_EQ(passenger04->IsOnBus(),true);
    EXPECT_EQ(passenger05->IsOnBus(),false);
    EXPECT_EQ(passenger06->IsOnBus(),false);

    EXPECT_EQ(passenger09->GetTotalWait(),3);
    EXPECT_EQ(passenger04->GetTotalWait(),3);
    EXPECT_EQ(passenger05->GetTotalWait(),3);
    EXPECT_EQ(passenger06->GetTotalWait(),3);
	
    EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
    bus1->Update();
    CC_EB->Update();// time 3, arrive at stop 4
    CC_WB->Update();
    busData = bus1->GetBusData();
    EXPECT_EQ(bus1->GetNumPassengers(),2);
    EXPECT_EQ(bus1->HowManySeatsLeft(),3);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(busData.num_passengers,2);
    EXPECT_EQ(bus1->IsTripComplete(),false);	
    // checking passengers update
    EXPECT_EQ(passenger09->IsOnBus(),false); // <- bus full :(
    EXPECT_EQ(passenger04->IsOnBus(),true);
    EXPECT_EQ(passenger05->IsOnBus(),true);
    EXPECT_EQ(passenger06->IsOnBus(),true);
    
    EXPECT_EQ(passenger09->GetTotalWait(),4);
    EXPECT_EQ(passenger04->GetTotalWait(),4);
    EXPECT_EQ(passenger05->GetTotalWait(),4);
    EXPECT_EQ(passenger06->GetTotalWait(),4);
    
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_2->GetNumberOfPassengerAtStop(),0);
	
	
    EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
    bus1->Update();
    bus1->Update();
    CC_EB->Update();// time 4, arrive at stop 5, last stop
    CC_WB->Update();
    busData = bus1->GetBusData();
    EXPECT_EQ(bus1->GetNumPassengers(),0);
    EXPECT_EQ(bus1->HowManySeatsLeft(),5);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(busData.num_passengers,0);
    EXPECT_EQ(bus1->IsTripComplete(),true);
    
    // checking passengers update
    
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_WB_2->GetNumberOfPassengerAtStop(),0);
	
    delete passenger01;
    delete passenger02;
    delete passenger03;
    delete passenger04;
    delete passenger05;
    delete passenger06;
    delete passenger07;
    delete passenger08;
    delete passenger09;
    delete stop_CC_EB_1;
    delete stop_CC_EB_2;
    delete stop_CC_EB_3;
    delete stop_CC_WB_1;
    delete stop_CC_WB_2;
    delete stop_CC_WB_3;
    delete CC_EB_generator;
    delete CC_EB;
    delete bus1;
    delete CC_EB_stops;
    delete CC_EB_distances;
}
TEST_F(BusTests,MoveAndLoadPassengersTest) {
  /**
  * methods tested: Move, LoadPassenger
  **/
  CC_EB_stops = new Stop *[3];
    CC_WB_stops = new Stop *[3];
    CC_EB_distances = new double[3];
    CC_WB_distances = new double[3];
    Passenger* passenger01 =  new Passenger();
    Passenger* passenger02 =  new Passenger();
  	Passenger* passenger03 =  new Passenger();
	Passenger* passenger07 =  new Passenger();
	Passenger* passenger08 =  new Passenger();
	Passenger* passenger09 =  new Passenger();
    Stop * stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
    stop_CC_EB_1->AddPassengers(passenger01);
    stop_CC_EB_1->AddPassengers(passenger02);
    stop_CC_EB_1->AddPassengers(passenger03);

    StopData s1 = stop_CC_EB_1->GetStopData();

  	Stop * stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
    StopData s2 = stop_CC_EB_2->GetStopData();
	stop_CC_EB_2->AddPassengers(passenger07);
	stop_CC_EB_2->AddPassengers(passenger08);
	stop_CC_EB_2->AddPassengers(passenger09);

  	Stop * stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);  // last stop
    StopData s3 = stop_CC_EB_3->GetStopData();

	
	 Passenger* passenger04 =  new Passenger(4); // get off at 4
	 Passenger* passenger05 =  new Passenger();
	 Passenger* passenger06 =  new Passenger();
	 Stop * stop_CC_WB_1 = new Stop(3, 44.975392, -93.226632);
	 stop_CC_WB_1->AddPassengers(passenger04);
	 StopData s4 = stop_CC_WB_1->GetStopData();
	 
	 Stop * stop_CC_WB_2 = new Stop(4, 44.984482, -93.181657);
	 stop_CC_WB_2->AddPassengers(passenger05);
	 stop_CC_WB_2->AddPassengers(passenger06);
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
  // time 0
    Bus * bus1 = new Bus ("1000", CC_EB,CC_WB, 5, 1);

	  Passenger* passenger10 =  new Passenger();
    Bus * bus2 = new Bus ("1001", CC_EB,CC_WB, 5, 1);
    EXPECT_EQ(bus2->GetHowManyPassengerOnBus(),0);
    bus2->LoadPassenger(passenger10);
    EXPECT_EQ(bus2->GetHowManyPassengerOnBus(),1);

    EXPECT_EQ(bus1->GetCapacity(),5);
    EXPECT_EQ(bus1->GetNextStop(),stop_CC_EB_2);
    EXPECT_EQ(bus1->GetBusPreviousStop()->GetId(),0);
    //EXPECT_EQ(busData.num_passengers,0);
    
    bool temp = bus1->Move();
    CC_EB->Update();// time 1
    CC_WB->Update();
    EXPECT_EQ (temp,true);
    EXPECT_EQ(bus1->GetNumPassengers(),3);
    EXPECT_EQ(bus1->GetHowManyPassengerOnBus(),3);
    BusData busData = bus1->GetBusData();
    EXPECT_EQ(busData.num_passengers,3);
    EXPECT_EQ(bus1->HowManySeatsLeft(),2);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
    // checking passengers update
    EXPECT_EQ(passenger01->IsOnBus(),true);
    EXPECT_EQ(passenger02->IsOnBus(),true);
    EXPECT_EQ(passenger03->IsOnBus(),true);
    EXPECT_EQ(passenger07->IsOnBus(),false);
    EXPECT_EQ(passenger08->IsOnBus(),false);
    EXPECT_EQ(passenger09->IsOnBus(),false);
    EXPECT_EQ(passenger04->IsOnBus(),false);
    EXPECT_EQ(passenger05->IsOnBus(),false);
    EXPECT_EQ(passenger06->IsOnBus(),false);
    
    temp = bus1->Move(); 
    CC_EB->Update();// time 2, arrive at stop 1
    CC_WB->Update();
    EXPECT_EQ (temp,true);
    EXPECT_EQ(bus1->GetNextStop(),stop_CC_EB_3);
    busData = bus1->GetBusData();
    EXPECT_EQ(busData.num_passengers,5);
    EXPECT_EQ(bus1->NotFull(),false);
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
    // checking passengers update
    EXPECT_EQ(passenger01->IsOnBus(),true);
    EXPECT_EQ(passenger02->IsOnBus(),true);
    EXPECT_EQ(passenger03->IsOnBus(),true);
    EXPECT_EQ(passenger07->IsOnBus(),true);
    EXPECT_EQ(passenger08->IsOnBus(),true);
    EXPECT_EQ(passenger09->IsOnBus(),false);// <- bus full :(
    EXPECT_EQ(passenger04->IsOnBus(),false);
    EXPECT_EQ(passenger05->IsOnBus(),false);
    EXPECT_EQ(passenger06->IsOnBus(),false);

    
    temp = bus1->Move();
    CC_EB->Update();// time 3, arrive at stop 2,3 last stop, switch route
    CC_WB->Update();
    EXPECT_EQ(temp,true);
    EXPECT_EQ(bus1->GetNextStop(),stop_CC_WB_2);
    busData = bus1->GetBusData();
    EXPECT_EQ(bus1->GetNumPassengers(),1);
    EXPECT_EQ(bus1->HowManySeatsLeft(),4);
    EXPECT_EQ(bus1->NotFull(),true);
    EXPECT_EQ(busData.num_passengers,1);
    EXPECT_EQ(stop_CC_WB_1->GetNumberOfPassengerAtStop(),0);
	EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
	EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);
	// checking passengers update
    EXPECT_EQ(passenger01->IsOnBus(),true);
    EXPECT_EQ(passenger02->IsOnBus(),true);
    EXPECT_EQ(passenger03->IsOnBus(),true);
    EXPECT_EQ(passenger07->IsOnBus(),true);
    EXPECT_EQ(passenger08->IsOnBus(),true);
    EXPECT_EQ(passenger09->IsOnBus(),false); // <- bus full :(
    EXPECT_EQ(passenger04->IsOnBus(),true);
    EXPECT_EQ(passenger05->IsOnBus(),false);
    EXPECT_EQ(passenger06->IsOnBus(),false);
    
    delete passenger01;
    delete passenger02;
    delete passenger03;
    delete passenger04;
    delete passenger05;
    delete passenger06;
    delete passenger07;
    delete passenger08;
    delete passenger09;
    delete stop_CC_EB_1;
    delete stop_CC_EB_2;
    delete stop_CC_EB_3;
    delete stop_CC_WB_1;
    delete stop_CC_WB_2;
    delete stop_CC_WB_3;
    delete CC_EB_generator;
    delete CC_EB;
    delete bus1;
    delete bus2;
    delete CC_EB_stops;
    delete CC_EB_distances;
}
