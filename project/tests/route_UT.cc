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
// TODO: havent test route report
class RouteTests :public ::testing::Test {
	protected:
    std::list<double> CC_EB_probs;


  	Stop ** CC_EB_stops;
  	std::list<Stop *> CC_EB_stops_list;
  	double * CC_EB_distances;
	
    Route * CC_EB;
};
TEST_F (RouteTests,constructor) {
    CC_EB_stops = new Stop *[3];
    CC_EB_distances = new double[3];
 	Stop * stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
  	Stop * stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
  	Stop * stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);
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
 	CC_EB_distances[1] = 4;
  	CC_EB_distances[2] = 2;
	RandomPassengerGenerator* CC_EB_generator = new RandomPassengerGenerator(CC_EB_probs, CC_EB_stops_list);;
    CC_EB = new Route("Campus Connector - Eastbound", CC_EB_stops,CC_EB_distances, 3, CC_EB_generator);

    EXPECT_EQ(CC_EB->GetName(),"Campus Connector - Eastbound");
    std::list<Stop*>::iterator it = CC_EB->GetStops().begin();
    EXPECT_EQ((*it),stop_CC_EB_1);
    it++;
    EXPECT_EQ((*it),stop_CC_EB_2);
    it++;
    EXPECT_EQ((*it),stop_CC_EB_3);
    EXPECT_EQ(CC_EB->GetStops().size(),3);
    EXPECT_EQ(CC_EB->GetLastStop(),stop_CC_EB_3);
    EXPECT_EQ(CC_EB->GetNumberOfStop(),3);
    delete stop_CC_EB_1;
    delete stop_CC_EB_2;
    delete stop_CC_EB_3;
    delete CC_EB_generator;
    delete CC_EB;
    delete CC_EB_stops;
    delete CC_EB_distances;

}
TEST_F (RouteTests, nextStopAndIsAtEnd) {
    CC_EB_stops = new Stop *[3];
    CC_EB_distances = new double[3];
    Stop * stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
  	Stop * stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
  	Stop * stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);
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
    EXPECT_EQ (CC_EB->IsAtEnd(),false);
    EXPECT_EQ(CC_EB->GetNextStopDistance(),4);
    EXPECT_EQ(CC_EB->GetDestinationStop(),stop_CC_EB_1);
    CC_EB->NextStop();
    EXPECT_EQ (CC_EB->IsAtEnd(),false);
    EXPECT_EQ(CC_EB->GetNextStopDistance(),2);
    EXPECT_EQ(CC_EB->GetDestinationStop(),stop_CC_EB_2);
    CC_EB->NextStop();
    EXPECT_EQ(CC_EB->GetDestinationStop(),stop_CC_EB_3);
    EXPECT_EQ(CC_EB->IsLastStop(stop_CC_EB_3),true);
    EXPECT_EQ(CC_EB->IsLastStop(stop_CC_EB_1),false);
    EXPECT_EQ (CC_EB->IsAtEnd(),true);

    delete stop_CC_EB_1;
    delete stop_CC_EB_2;
    delete stop_CC_EB_3;
    delete CC_EB_generator;
    delete CC_EB;
    delete CC_EB_stops;
    delete CC_EB_distances;
}
TEST_F (RouteTests, Clone) {
    CC_EB_stops = new Stop *[3];
    CC_EB_distances = new double[3];
    Stop * stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
  	Stop * stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
  	Stop * stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);
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
    Route * temp;
    temp = CC_EB->Clone();
    EXPECT_EQ(temp->GetNextStopDistance(),4);
    EXPECT_EQ(temp->GetDestinationStop(),stop_CC_EB_1);
    temp->NextStop();
    EXPECT_EQ(temp->GetNextStopDistance(),2);
    EXPECT_EQ(temp->GetDestinationStop(),stop_CC_EB_2);
    temp->NextStop();
    EXPECT_EQ(temp->GetDestinationStop(),stop_CC_EB_3);
    EXPECT_EQ(temp->IsLastStop(stop_CC_EB_3),true);
    EXPECT_NE(temp->IsLastStop(stop_CC_EB_1),true);
    EXPECT_NE(temp->IsLastStop(stop_CC_EB_2),true);
    temp->NextStop(); // this should do nothing, route code protects bus
    EXPECT_EQ(temp->GetNextStopDistance(),0);
    EXPECT_EQ(temp->GetDestinationStop(),stop_CC_EB_3);
    temp->NextStop();
    EXPECT_EQ(temp->GetNextStopDistance(),0);
    EXPECT_EQ(temp->GetDestinationStop(),stop_CC_EB_3);



    delete stop_CC_EB_1;
    delete stop_CC_EB_2;
    delete stop_CC_EB_3;
    delete CC_EB_generator;
    delete CC_EB;
    delete CC_EB_stops;
    delete CC_EB_distances;
}
TEST_F (RouteTests, GetRouteDataAndUpdate) {
    CC_EB_stops = new Stop *[3];
    CC_EB_distances = new double[3];
    Passenger* passenger01 =  new Passenger();
    Passenger* passenger02 =  new Passenger();
  	Passenger* passenger03 =  new Passenger();

    Stop * stop_CC_EB_1 = new Stop(0, 44.972392, -93.243774);
    stop_CC_EB_1->AddPassengers(passenger01);
    StopData s1 = stop_CC_EB_1->GetStopData();

  	Stop * stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
    stop_CC_EB_2->AddPassengers(passenger02);
    stop_CC_EB_2->AddPassengers(passenger03);
    StopData s2 = stop_CC_EB_2->GetStopData();


  	Stop * stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);
    StopData s3 = stop_CC_EB_3->GetStopData();

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
    RouteData data = CC_EB->GetRouteData();
    EXPECT_EQ(data.id,"Campus Connector - Eastbound");
    std::vector<StopData>::iterator it;
    it = data.stops.begin();
    EXPECT_EQ((*it).id,s1.id);
    EXPECT_EQ((*it).position.x,s1.position.x);
    EXPECT_EQ((*it).position.y,s1.position.y);
    EXPECT_EQ((*it).num_people,s1.num_people);

    it++;
    EXPECT_EQ((*it).id,s2.id);
    EXPECT_EQ((*it).position.x,s2.position.x);
    EXPECT_EQ((*it).position.y,s2.position.y);
    EXPECT_EQ((*it).num_people,s2.num_people);
    it++;
    EXPECT_EQ((*it).id,s3.id);
    EXPECT_EQ((*it).position.x,s3.position.x);
    EXPECT_EQ((*it).position.y,s3.position.y);
    EXPECT_EQ((*it).num_people,s3.num_people);
	CC_EB->Update();
	EXPECT_EQ(passenger01->GetTotalWait(),1);
	EXPECT_EQ(passenger02->GetTotalWait(),1);
	EXPECT_EQ(passenger03->GetTotalWait(),1);
	CC_EB->Update();
	EXPECT_EQ(passenger01->GetTotalWait(),2);
	EXPECT_EQ(passenger02->GetTotalWait(),2);
	EXPECT_EQ(passenger03->GetTotalWait(),2);
    delete passenger01;
    delete passenger02;
    delete passenger03;
    delete stop_CC_EB_1;
    delete stop_CC_EB_2;
    delete stop_CC_EB_3;
    delete CC_EB_generator;
    delete CC_EB;
    delete CC_EB_stops;
    delete CC_EB_distances;
}
TEST_F (RouteTests, UpdateRouteData) {
    CC_EB_stops = new Stop *[3];
    CC_EB_distances = new double[3];
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

  	Stop * stop_CC_EB_2 = new Stop(1, 44.973580, -93.235071);
    StopData s2 = stop_CC_EB_2->GetStopData();


  	Stop * stop_CC_EB_3 = new Stop(2, 44.975392, -93.226632);
    StopData s3 = stop_CC_EB_3->GetStopData();

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

    RouteData data1 = CC_EB->GetRouteData(); // UpdateRouteData is called in GetRouteData
    EXPECT_EQ(data1.id,"Campus Connector - Eastbound");
    std::vector<StopData>::iterator it1;
    it1 = data1.stops.begin();
    EXPECT_EQ((*it1).num_people,3);


    Bus * bus1 = new Bus ("1000", CC_EB,CC_EB, 10, 1);
    stop_CC_EB_1->LoadPassengers(bus1);
    s1 = stop_CC_EB_1->GetStopData();  // passenger at first stop gone

    RouteData data = CC_EB->GetRouteData(); // UpdateRouteData is called in GetRouteData
    EXPECT_EQ(data.id,"Campus Connector - Eastbound");
    std::vector<StopData>::iterator it;
    it = data.stops.begin();

    EXPECT_EQ((*it).id,s1.id);
    EXPECT_EQ((*it).position.x,s1.position.x);
    EXPECT_EQ((*it).position.y,s1.position.y);
    EXPECT_EQ((*it).num_people,0);  // passenger at first stop gone by buse
    it++;
    EXPECT_EQ((*it).id,s2.id);
    EXPECT_EQ((*it).position.x,s2.position.x);
    EXPECT_EQ((*it).position.y,s2.position.y);
    EXPECT_EQ((*it).num_people,s2.num_people);
    it++;
    EXPECT_EQ((*it).id,s3.id);
    EXPECT_EQ((*it).position.x,s3.position.x);
    EXPECT_EQ((*it).position.y,s3.position.y);
    EXPECT_EQ((*it).num_people,s3.num_people);
// next time
    CC_EB->Update();
    stop_CC_EB_1->AddPassengers(passenger01);

    s1 = stop_CC_EB_1->GetStopData();
    data = CC_EB->GetRouteData();
    it = data.stops.begin();

    EXPECT_EQ((*it).id,s1.id);
    EXPECT_EQ((*it).position.x,s1.position.x);
    EXPECT_EQ((*it).position.y,s1.position.y);
    EXPECT_EQ((*it).num_people,s1.num_people);
    it++;
    EXPECT_EQ((*it).id,s2.id);
    EXPECT_EQ((*it).position.x,s2.position.x);
    EXPECT_EQ((*it).position.y,s2.position.y);
    EXPECT_EQ((*it).num_people,s2.num_people);
    it++;
    EXPECT_EQ((*it).id,s3.id);
    EXPECT_EQ((*it).position.x,s3.position.x);
    EXPECT_EQ((*it).position.y,s3.position.y);
    EXPECT_EQ((*it).num_people,s3.num_people);
  // next time
    stop_CC_EB_2->LoadPassengers(bus1);
    CC_EB->Update();
    s1 = stop_CC_EB_1->GetStopData();
    s2 = stop_CC_EB_2->GetStopData();
    data = CC_EB->GetRouteData();
    it = data.stops.begin();

    EXPECT_EQ((*it).id,s1.id);
    EXPECT_EQ((*it).position.x,s1.position.x);
    EXPECT_EQ((*it).position.y,s1.position.y);
    EXPECT_EQ((*it).num_people,s1.num_people);
    it++;
    EXPECT_EQ((*it).id,s2.id);
    EXPECT_EQ((*it).position.x,s2.position.x);
    EXPECT_EQ((*it).position.y,s2.position.y);
    EXPECT_EQ((*it).num_people,s2.num_people);
    it++;
    EXPECT_EQ((*it).id,s3.id);
    EXPECT_EQ((*it).position.x,s3.position.x);
    EXPECT_EQ((*it).position.y,s3.position.y);
    EXPECT_EQ((*it).num_people,s3.num_people);

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
    delete CC_EB_stops;
    delete CC_EB_distances;
}
