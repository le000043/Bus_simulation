
/**
 * @file passenger.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_

#include <iostream>
#include <string>
/**
* @brief
* passengers will wait at a stop waiting to be picked up by a bus
* and get off at a stop within the current route.
**/
class Passenger {  // : public Reporter {
 public:
  /**
  * @brief Constructs a passenger with a standard name and id.
  *
  *
  * @param[in] int holding an id number
  * @param[in] string holding a name of a created passenger.
  * */
  explicit Passenger(int = -1, std::string = "Nobody");
  /**
  * @brief Increment wait_at_bus_ if passenger not on the bus.
  * @param[in] None
  * */
  void Update();
  /**
  * @brief set time_on_bus_ to zero. 
  * @param[in] None.
  * */
  void GetOnBus();
  /**
  * @brief If time_on_bus is non-negative.
  * @brief Then return sum of time_on_bus_ and wait_at_stop_.
  * @brief Otherwise, return wait_at_stop_.
  * @param[in] None.
  * */
  int GetTotalWait() const;
  /**
  * @brief check if time_on_bus_ is non-negative
  * @param [in] None.
  * */
  bool IsOnBus() const;
  /**
  * @brief get stop passenger want to be at
  * @param [in] None.
  * @return stop passenger want to be at
  * */
  int GetDestination() const;
  /**
  * @brief report name, stop, waiting time
  * param  [in] None.
  * @return None.
  * */
  void Report(std::ostream &  out) const;

 private:
  std::string name_;
  int destination_stop_id_;
  int wait_at_stop_;
  int time_on_bus_;
  int id_;
  static int count_;   // global count, used to set ID for new instances
};
#endif  // SRC_PASSENGER_H_
