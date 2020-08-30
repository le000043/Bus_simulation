/**
 * @file configuration_simulator.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/configuration_simulator.h"

#include "src/bus.h"
#include "src/route.h"

configuration_simulator::configuration_simulator(ConfigManager* configM) {
    configManager_ = configM;
}

configuration_simulator::~configuration_simulator() {
}
void configuration_simulator::Start(const std::vector<int>& busStartTimings,
const int& numTimeSteps) {
    // construct 2 parallel vector, one for time between bus in first route,
    //     one for time between bus in first route
    // first bus takes the first pair of out/in bound route,
    //     second bus takes the second pair of out/in bound route if it exists
    // otherwise, take the first one
    busStartTimings_ = busStartTimings;
    numTimeSteps_ = numTimeSteps;

    timeSinceLastBus_.resize(busStartTimings_.size());
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        timeSinceLastBus_[i] = 0;
    }

    simulationTimeElapsed_ = 0;

    prototypeRoutes_ = configManager_->GetRoutes();
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Report(std::cout);
        prototypeRoutes_[i]->UpdateRouteData();
    }
}

void configuration_simulator::Update() {
    simulationTimeElapsed_++;

    std::cout << "~~~~~~~~~~ The time is now " << simulationTimeElapsed_;
    std::cout << "~~~~~~~~~~" << std::endl;

    std::cout << "~~~~~~~~~~ Generating new busses if needed ";
    std::cout << "~~~~~~~~~~" << std::endl;

    // Check if we need to generate new busses
for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
// Check if we need to make a new bus
if (0 >= timeSinceLastBus_[i]) {
Route * outBound_ = prototypeRoutes_[2 * i];
Route * inBound_ = prototypeRoutes_[2 * i + 1];
busses_.push_back(
new Bus(std::to_string(busId), outBound_->Clone() , inBound_->Clone(), 60, 1));
busId++;
std::cout << "bus creating " << busStartTimings_[i] << std::endl;
timeSinceLastBus_[i] = busStartTimings_[i];
} else {
timeSinceLastBus_[i]--;
}
}

    std::cout << "~~~~~~~~~ Updating routes ";
    std::cout << "~~~~~~~~~" << std::endl;
    // Update routes
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Update();
        prototypeRoutes_[i]->Report(std::cout);
    }
    std::cout << "~~~~~~~~~ Updating busses ";
    std::cout << "~~~~~~~~~" << std::endl;

    // Update busses
    for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
        busses_[i]->Update();

        if (busses_[i]->IsTripComplete()) {
            busses_.erase(busses_.begin() + i);
            continue;
        }
        busses_[i]->Report(std::cout);
    }
}
