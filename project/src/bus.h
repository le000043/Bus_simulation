/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_H_
#define SRC_BUS_H_

#include <iostream>
#include <list>
#include <string>

#include "src/passenger.h"
#include "src/route.h"
#include "src/stop.h"
#include "src/data_structs.h"

// class PassengerUnloader;
// class PassengerLoader;
class Route;
class Stop;
/**
* @brief bus has a list of passengers it is carrying.
* @brief bus loading and unloading passengers at stops.
* @brief bus switch stops when needed and can only travel two routes.
**/
class Bus {
 public:
 /**
 * @brief initialize all private variables
 * @brief load passenger at the first stop
 * @brief set up stop and distance remaining pointer
 * @param[in] string name
 * @param[in] Route* out
 * @param[in] Route* in
 * @param[in] int capacity
 * @param[in] double speed
 * @return None
 * */
  Bus(std::string name, Route * out, Route * in, int capacity = 60,
                                                 double speed = 1);
/**
* @brief add passenger to passenger list
* @param[in] Passenger*
* @return bool
* */
  bool LoadPassenger(Passenger *);  // returning revenue delta
/**
* @brief reducing distance remaining
* @brief if at a stop, unload and load passenger
* @brief if at last stop of route, switch route
* @brief and update stop and distance remaining pointer
* @param [in] None
* @return bool
* */
  bool Move();
/**
* @brief calculate how many seat left
* @param[in] None
* @return bool
**/
  int HowManySeatsLeft();
/**
* @brief check if bus is full
* @param [in] None
* @return bool
**/
  bool NotFull();
/**
* @brief update passenger and call Move()
* @param[in] None
* @return None
**/
  void Update();
/**
* @brief run passenger report that on bus and report bus info
* @param[in] ostream&
* @return None
**/
  void Report(std::ostream &  out);
/**
* @brief check if bus finish both route
* @param None
* @return bool
**/
  bool IsTripComplete();
/**
* @brief get how many passengers on the bus
* @param[in] None
* @return int
**/
  int GetHowManyPassengerOnBus();
  /**
  * @brief update the bus data including positions and number of passengers
  * @param [in] None
  **/
  void UpdateBusData();
  /**
  * @brief return the bus data
  * @return BusData
  **/
  BusData GetBusData();
  /**
  * @brief return bus name
  * @param [in] None
  * @return std::string
  **/
  std::string GetName();
  /**
  * @brief get the next stop reference
  * @param [in] None
  * @return Stop*
  **/
  Stop* GetNextStop();
  /**
  * @brief get number of passengers on the bus
  * @param [in] None
  * @return size_t
  **/
  size_t GetNumPassengers();
  /**
  * @brief get the max capacity of bus
  * @param [in] None
  * @return integer
  **/
  int GetCapacity();
  /**
  * @brief get the previous stop reference
  * @param [in] None
  * @return None
  **/
  Stop* GetBusPreviousStop();
  // bool ExistsPassengersWantToGetOffAtNextStop();
  // void ArrivingAtStop();

 private:
  std::list<Passenger *> passengers_;
  int passenger_max_capacity_;
  std::string name_;
  double speed_;  //  could also be called "distance travelled in one time step"
  Route * outgoing_route_;
  Route * incoming_route_;
  Route * current_route_;
  Stop* current_stop_;
  Stop* next_stop_;
  Stop* previous_stop_;  // previous stop for visual sim
  int number_route_complete_;
  //  need a boolean variable to keep track on which route to take
  //  (this is based on the next_stop return value)
  double distance_remaining_;  //  when negative?,
  int pick_up_at_first_stop_;
  // bool already_skip_a_stop_=false;
  void switchRoute();
  void UnloadPassengers();
  BusData bus_data_;
                              //  AND next stop set
  //  double revenue_; //  revenue collected from passengers, doesn't include
                      //  passengers who pay on deboard
  //  double fuel_;   //  may not be necessary for our simulation
  //  double max_fuel_;
};
#endif  // SRC_BUS_H_
