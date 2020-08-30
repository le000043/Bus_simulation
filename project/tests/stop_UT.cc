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
// TODO: need to test Stop's Report
class StopTests :public ::testing::Test {
	protected:
    std::list<double> CC_EB_probs;


  	Stop ** CC_EB_stops = new Stop *[3];
  	std::list<Stop *> CC_EB_stops_list;
  	double * CC_EB_distances = new double[7];
	
    Route * CC_EB;

	Stop* stop;
	virtual void SetUp() {
    	stop = new Stop(0);
  	}

  	virtual void TearDown() {
        delete CC_EB_stops;
        delete CC_EB_distances;
    	delete stop;
  	}
};
TEST_F(StopTests,ConstructorAndSetters) {
  	EXPECT_EQ(stop->GetLongitude(), 44.973723);
  	EXPECT_EQ(stop->GetLatitude(), -93.235365);
  	EXPECT_EQ(stop->GetId(), 0);
};

TEST_F(StopTests,AddPassengerANDGetNumberOfPassengerAtStop) {
  	Passenger* passenger01 =  new Passenger();
  	Passenger* passenger02 =  new Passenger();
  	Passenger* passenger03 =  new Passenger();

  	EXPECT_EQ(stop->GetNumberOfPassengerAtStop(),0);
	stop->AddPassengers(passenger01);
  	EXPECT_EQ(stop->GetNumberOfPassengerAtStop(),1);
	stop->AddPassengers(passenger02);
	stop->AddPassengers(passenger03);
  	EXPECT_EQ(stop->GetNumberOfPassengerAtStop(),3);
};
TEST_F (StopTests,Update) {
  	Passenger* passenger01 =  new Passenger();
  	Passenger* passenger02 =  new Passenger();
	stop->AddPassengers(passenger01);
	stop->AddPassengers(passenger02);
	stop->Update();
  	EXPECT_EQ(passenger01->GetTotalWait(),1);  	
  	EXPECT_EQ(passenger02->GetTotalWait(),1);
	EXPECT_EQ(passenger01->IsOnBus(),false);
  	EXPECT_EQ(passenger02->IsOnBus(),false);
	stop->Update();
  	EXPECT_EQ(passenger01->GetTotalWait(),2);  	
  	EXPECT_EQ(passenger02->GetTotalWait(),2);
	EXPECT_EQ(passenger01->IsOnBus(),false);  	
  	EXPECT_EQ(passenger02->IsOnBus(),false);
}
TEST_F (StopTests,LoadPassengerAndStopData) {
     Passenger* passenger01 =  new Passenger();
    Passenger* passenger02 =  new Passenger();
  	Passenger* passenger03 =  new Passenger();
  	Passenger* passenger04 =  new Passenger();
  	Passenger* passenger05 =  new Passenger();


    Stop * stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
    stop_CC_EB_1->AddPassengers(passenger01);
    stop_CC_EB_1->AddPassengers(passenger02);
    stop_CC_EB_1->AddPassengers(passenger03);
    StopData s1 = stop_CC_EB_1->GetStopData();
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),3);
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),s1.num_people);

  	Stop * stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
    stop_CC_EB_2->AddPassengers(passenger04);
    StopData s2 = stop_CC_EB_2->GetStopData();
    EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
    EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),s2.num_people);


  	Stop * stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);
    stop_CC_EB_3->AddPassengers(passenger05);
    EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),1);
    StopData s3 = stop_CC_EB_3->GetStopData();
    EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),s3.num_people);


    CC_EB_probs.push_back(0);   // WB
    CC_EB_probs.push_back(0);    // CMU
    CC_EB_probs.push_back(0);  // O&W
    CC_EB_stops_list.push_back(stop_CC_EB_1);
  	CC_EB_stops[0] = stop_CC_EB_1;
    CC_EB_stops_list.push_back(stop_CC_EB_2);
  	CC_EB_stops[1] = stop_CC_EB_2;
    CC_EB_stops_list.push_back(stop_CC_EB_3);
  	CC_EB_stops[2] = stop_CC_EB_3;
    CC_EB_distances[0] = 4;
 	CC_EB_distances[1] = 2;
	RandomPassengerGenerator* CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);;
    CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops,CC_EB_distances, 3, CC_EB_generator);
    Bus * bus1 = new Bus ("1000", CC_EB,CC_EB, 10, 1);
    stop_CC_EB_1->LoadPassengers(bus1);
    s1 = stop_CC_EB_1->GetStopData();
    EXPECT_EQ(0,s1.num_people);
    EXPECT_EQ(1,s2.num_people);
    EXPECT_EQ(1,s3.num_people);

    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
    EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),1);
    EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),1);

    stop_CC_EB_2->LoadPassengers(bus1);
    s2 = stop_CC_EB_2->GetStopData();
    EXPECT_EQ(0,s1.num_people);
    EXPECT_EQ(0,s2.num_people);
    EXPECT_EQ(1,s3.num_people);
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
    EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),0);
    EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),1);
    
    stop_CC_EB_3->LoadPassengers(bus1);
    s3 = stop_CC_EB_3->GetStopData();
    EXPECT_EQ(0,s1.num_people);
    EXPECT_EQ(0,s2.num_people);
    EXPECT_EQ(0,s3.num_people);
    EXPECT_EQ(stop_CC_EB_1->GetNumberOfPassengerAtStop(),0);
    EXPECT_EQ(stop_CC_EB_2->GetNumberOfPassengerAtStop(),0);
    EXPECT_EQ(stop_CC_EB_3->GetNumberOfPassengerAtStop(),0);



    delete passenger01;
    delete passenger02;
    delete passenger03;
    delete passenger04;
    delete passenger05;
    delete stop_CC_EB_1;
    delete stop_CC_EB_2;
    delete stop_CC_EB_3;
    delete CC_EB_generator;
    delete CC_EB;
    delete bus1;
}
