/**
 * @file passenger_generator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_GENERATOR_H_
#define SRC_PASSENGER_GENERATOR_H_

#include <list>
#include "./passenger_factory.h"
#include "./stop.h"
/**
* @brief abstract calss of random passenger generator class
**/
class Stop;  // forward declaration

class PassengerGenerator {
 public:
/**
* @brief initialize private variables
* @param [in] list of double
* @param [in] list of Stop*
**/
  PassengerGenerator(std::list<double>, std::list<Stop *>);
  // Makes the class abstract, cannot instantiate and forces subclass override
/**
* @brief virtual method
* @param [in] None
**/
  virtual int GeneratePassengers() = 0;  // pure virtual
 protected:
  std::list<double> generation_probabilities_;
  std::list<Stop *> stops_;

  // should we be using a singleton here somehow?
  // PassengerFactory * pass_factory;
};
#endif  // SRC_PASSENGER_GENERATOR_H_
