/**
 * @file route.h
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_

#include <list>
#include <iostream>
#include <string>

#include "./passenger_generator.h"
#include "./stop.h"
#include "src/data_structs.h"

class PassengerGenerator;
class Stop;
/**
*@brief 
* collection of stops and generate passengers
**/
class Route {
 public:
  /**
   * @brief create stop and distance between stops
   * 
   * @param[in] string name of route
   * @param[in] Stop* to an array of Stop pointer 
   * @param[in] double* pointer with name distances
   * @param[in] int of number of stops
   * @param[in] PassengerGenerator* to random passenger generator. object
   * */
  Route(std::string name, Stop ** stops, double * distances, int num_stops,
        PassengerGenerator *);
  /**
  * @brief make a non-prototype route that shares
  * @brief stop and distance list
  * @param[in] None
  * @return pointer to non-prototype Route
  * */
  Route * Clone();
  /**
   * @brief update method will call all stop's update method
   * @param[in] None.
   * */
  void Update();
  /**
   * @brief print out name, number stops and report all stops
   * @param[in] pointer address of ostream object
   * @return None
   * */
  void Report(std::ostream&);
  /**
  * @brief checking if stop_iterator pointing to the last stop
  * @param[in] None
  * @return true if stop_iterator pointing stop that is the last top
  * */
  bool IsAtEnd() const;
  /**
  * @brief increment stop_iterator and distances_between_iterator_
  * @param[in] None
  * */
  void NextStop();  // Change destination_stop_ to next stop
  /**
  * @brief checking if given stop is the last stop of route
  * @param[in] Stop*
  * @return bool
  * */
  bool IsLastStop(Stop*);
  /**
  * @brief get the next stop
  * @param[in] None
  * @return Stop*
  * */
  Stop * GetDestinationStop() const;
  /**
  * @brief get the distance stop
  * @param[in] None
  * @return double
  * */
  double GetNextStopDistance() const;
  // void GetAllStopData();
  /**
  * @brief get name of the route
  * @param [in] None
  * @return std::string
  **/
  std::string GetName();
  /**
  * @brief return the reference to stop list
  * @param [in] None
  * @return std::list<Stop *>
  **/
  std::list<Stop *> GetStops();
  /**
  * @brief update route data that get most current stop data
  * @param [in] None
  * @return None
  **/
  void UpdateRouteData();
  /**
  * @brief get route data to vis_sim
  * @param [in] None
  * @return RouteData
  **/
  RouteData GetRouteData();
  /**
  * @brief get last stop pointer
  * @param [in] None
  * @return Stop*
  **/
  Stop * GetLastStop();
  /**
  * @brief get number of stops
  * @param [in] None
  * @return integer
  **/
  int GetNumberOfStop();

 private:
  /*
  * @return call GenerateNewPassengers from RandomGenerator object
  * */
  int GenerateNewPassengers();       // generates passengers on its route
  PassengerGenerator * generator_;
  std::list<Stop*> stops_;
  std::list<double> distances_between_;  // length = num_stops_ - 1
  std::string name_;
  int num_stops_;
  Stop* last_stop_object_reference_;              // this is last stop object

  // int destination_stop_index_;  // always starts at zero, no init needed
  std::list<Stop*>::iterator stop_iterator;
  std::list<double>::iterator distances_between_iterator_;
  Stop * destination_stop_;
  RouteData routeData;
  // double trip_time_; // derived data - total distance travelled on route
};
#endif  // SRC_ROUTE_H_

