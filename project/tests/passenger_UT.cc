/* STUDENTS: YOU MUST ADD YOUR PASSENGER UNIT TESTS TO THIS FILE. FORMAT YOUR
 * TESTS TO FIT THE SPECIFICATIONS GIVEN BY THE TESTS PROVIDED IN THIS FILE.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/route.h"
#include "../src/passenger_generator.h"


/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class PassengerTests : public ::testing::Test {

	protected:
  	
  	Passenger* passenger;
  	
	virtual void SetUp() {
    	passenger = new Passenger();
  	}

  	virtual void TearDown() {
    	delete passenger;
  	}

};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PassengerTests,Constructor) {
  	EXPECT_EQ(passenger->IsOnBus(), false);
  	passenger->GetOnBus();
  	EXPECT_EQ(passenger->IsOnBus(), true);
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(PassengerTests, more_Constructor) {
  	Passenger *passenger1 = new Passenger (5,"Michael");
  	EXPECT_EQ(passenger1->GetDestination(),5);
};
TEST_F(PassengerTests, GetOnBus) {
  	Passenger *passenger1 = new Passenger (2,"Michael");
  	// testing::internal::CaptureStdout()
  	
  	passenger1->Update();
  	EXPECT_EQ(passenger1->GetTotalWait(),1);  	
  	passenger1->GetOnBus();
  	passenger1->Update();
  	
  	// passenger1->Report()
  	
  	// std::string output1 = testing::internal::GetCaptureStdout()
  	EXPECT_EQ(passenger1->IsOnBus(),true);
  	EXPECT_EQ(passenger1->GetTotalWait(),3);
  	delete passenger1;
};

TEST_F(PassengerTests, GetTotalWait) {
	Passenger*passenger2 = new Passenger (10,"Sam");
	passenger2->Update(); // at stop 2, bus start at stop 1
	
  	passenger2->GetOnBus(); // bus at stop 2
  	passenger2->Update(); // bus at stop 3
  	
  	passenger2->Update(); // bus at stop 4
  	passenger2->Update(); // bus at stop 5
  	// passenger get off bus
  	// EXPECT_EQ(passenger2->IsOnBus(),true);
  	EXPECT_EQ(passenger2->GetTotalWait(),5);
  	delete passenger2; // passenger off the bus
};
