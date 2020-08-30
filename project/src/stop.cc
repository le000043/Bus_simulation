/**
 * @file stop.h
 *
 * @copyright 2019 3081 Staff and Dat Le, All rights reserved.
 */

#include <iostream>
#include <vector>
#include <string>
#include "src/stop.h"
#include "src/data_structs.h"

Stop::Stop(int id, double longitude, double latitude) :
  id_(id), longitude_(longitude), latitude_(latitude) {
  // Defaults to Westbound Coffman Union stop
  // no initialization of list of passengers necessary
  id_ = id;
  longitude_ = longitude;
  latitude_ = latitude;
  stopData.id = id_;
  stopData.position.x = longitude_;
  stopData.position.y = latitude_;
  stopData.num_people = GetNumberOfPassengerAtStop();
}

int Stop::GetNumberOfPassengerAtStop() {
int count = 0;
if (!passengers_.empty()) {
  for ( std::list<Passenger *>::iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    count+=1;
  }
}
return count;
}
double Stop::GetLongitude() {
  return longitude_;
}
double Stop::GetLatitude() {
  return latitude_;
}
StopData Stop::GetStopData() {
// get the most current data which includes
// constant id, position and varying number of passenger
// std::string s = std::to_string(id_);
stopData.id = std::to_string(id_);
stopData.position.x = longitude_;
stopData.position.y = latitude_;
stopData.num_people = GetNumberOfPassengerAtStop();
return stopData;
}

int Stop::AddPassengers(Passenger * pass) {
// push new passenger to passengers_ list
  passengers_.push_back(pass);
  return 1;
}

int Stop::LoadPassengers(Bus * bus) {
  // loading some passengers onto a bus.
  int count = 0;
// int count is a boundary to pop passenger off the stop
// for loop goes thru passengers_ list and
// let passengers get on bus iff passengers_ list not empty
// and bus is not full
// increment count
  for ( std::list<Passenger *>::iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
  if (!passengers_.empty() && bus->NotFull()) {
  (*it)->GetOnBus();
  bus->LoadPassenger(*it);
  count+=1;
  }
}
  int x = 0;
// while loop below pops passengers off the list based on count
  while (!passengers_.empty()&& x < count) {
    passengers_.pop_front();
    x+=1;
  }
  return 1;
}
void Stop::Update() {
// call update on its passengers
  for (std::list<Passenger *>::iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
  (*it)->Update();
  }
}

int Stop::GetId() const {
  return id_;
}

void Stop::Report(std::ostream &  out) const {
  out << "ID: " << id_ << std::endl;
  out << "Passengers waiting: " << passengers_.size() << std::endl;
  for (std::list<Passenger *>::const_iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}
