/**
 * @file local_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_CAPTURE_LOCAL_SIMULATOR_H_
#define SRC_CAPTURE_LOCAL_SIMULATOR_H_

#include <vector>

#include "src/captureSimulator.h"
/**
* @brief run simulation
**/
class captureLocalSimulator : public captureSimulator {
 public:
/**
* @brief create stop, route and random passenger objects
* params [in] None
* @return bool
**/
  bool Start() override;
/**
* @brief update time, bus and route
* @param [in] None
* @return bool
**/
  bool Update(std::ostream &) override;
 private:
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
};

#endif  // SRC_CAPTURE_LOCAL_SIMULATOR_H_
