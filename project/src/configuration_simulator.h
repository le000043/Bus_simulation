/**
 * @file configuration_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_CONFIGURATION_SIMULATOR_H_
#define SRC_CONFIGURATION_SIMULATOR_H_

#include <vector>
#include <list>

// #include "web_interface.h"
#include "src/config_manager.h"

class Route;
class Bus;
class Stop;
/**
* @brief simulator for configuration_sim driver
**/
class configuration_simulator{
 public:
        /**
        * @brief destructor
        * @param [in] ConfigManager*
        **/
        explicit configuration_simulator(ConfigManager*);
        ~configuration_simulator();
        /**
        * @brief create stop, route and random passenger objects
        * @params [in] std::vector<int>&
        * @params [in] const int&
        **/
        void Start(const std::vector<int>&, const int&);
        /**
        * @brief update time, bus and route
        * @param [in] None
        * @return bool
        **/
        void Update();

 private:
        ConfigManager* configManager_;
        std::vector<int> busStartTimings_;
        std::vector<int> timeSinceLastBus_;
        int numTimeSteps_;
        int simulationTimeElapsed_;

        std::vector<Route *> prototypeRoutes_;
        std::vector<Bus *> busses_;

        int busId = 1000;
};

#endif  // SRC_CONFIGURATION_SIMULATOR_H_
