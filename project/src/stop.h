/**
 * @file stop.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_STOP_H_
#define SRC_STOP_H_

#include <list>
#include <iostream>

#include "src/bus.h"
#include "src/passenger.h"
#include "src/data_structs.h"

class Bus;
/**
* @brief stop has a list of passenger and load passenger to buses
**/
class Stop {
 public:
  /**
   * @brief initialize stop id, longitude and latitude
   * @brief default value of longitude and latitde are 44.973723 and -93.235365 respectively
   * @param[in] int holding stop id
   * @param[in] double holding longitude
   * @param[in] double holding latitude
   * */
  explicit Stop(int, double = 44.973723, double = -93.235365);
  // Adding passengers to the stop (from the generator)
  /**
   * @brief get the stop id
   * @return int
   * */
  int GetId() const;
  /**
   * @brief add passenger to passenger_ which is a list of pointer type Passenger
   * @params a pointer type Passenger
   * @return 1
   * */
  int AddPassengers(Passenger *);
  /**
   * @brief remove the passenger from the front of the linked list passenger_
   * @params a pointer type Bus 
   * @return int
   * */  
  int LoadPassengers(Bus *);
  /**
   * @brief update all passenger on the bus
   * @param [in] None
   * @return None
   * */
  void Update();
  /**
   * @brief print out stop id and number of passenger waiting,
   * @brief call report of each passenger waiting
   * @param[in] ostream&
   * @return None
   * */
  void Report(std::ostream &  out) const;
  /**
  * @brief get how many passenger waiting at stop
  * @param [in] None
  * @return integer
  **/
  int GetNumberOfPassengerAtStop();
  /**
  * @brief get stop data for vis_sim
  * @param [in] None
  * @return StopData
  **/
  StopData GetStopData();
  /**
  * @brief get stop's longitude
  * @param [in] None
  * @return double
  **/
  double GetLongitude();
  /**
  * @brief get stop's latitude
  * @param [in] None
  * @return double
  **/
  double GetLatitude();

 private:
  int id_;
  std::list<Passenger *> passengers_;  // considered array, vector, queue, list
  double longitude_;
  double latitude_;  // are we using long/lat coords?
  StopData stopData;
  // derived information - not needed depending on passengers_
  // data structure implementation?
  // int passengers_present_;
};
#endif  // SRC_STOP_H_
