/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/bus.h"
Bus::Bus(std::string name, Route * out,
Route * in, int capacity, double speed) {
  name_ = name;
  number_route_complete_ = 0;
  pick_up_at_first_stop_ = 1;
  outgoing_route_ = out->Clone();
  incoming_route_ = in->Clone();
  current_route_ = outgoing_route_;
  // default route is outbound
  passenger_max_capacity_ = capacity;
  speed_ = speed;
  current_stop_ = current_route_->GetDestinationStop();
  previous_stop_ = current_stop_;
  current_stop_->LoadPassengers(this);  // pick up at first stop
  distance_remaining_ = current_route_->GetNextStopDistance();
  // get the distance that needs to travel at the beginning
  UpdateBusData();
  current_route_->NextStop();
  next_stop_ = current_route_->GetDestinationStop();
  current_stop_ = next_stop_;
  // get the next stop that bus wants to be at the beginning
}
int Bus::GetCapacity() {
// tested
return passenger_max_capacity_;
}
std::string Bus::GetName() {
// tested
return name_;
}
Stop* Bus::GetNextStop() {
// tested
return next_stop_;
}
void Bus::UpdateBusData() {
// tested
// either bus at stop or in the middle of 2 stops.
  bus_data_.id = name_;
  bus_data_.num_passengers = GetNumPassengers();
  float previous_stop_x_ = previous_stop_->GetLongitude();
  float new_longitude_ = (current_stop_->GetLongitude()) + previous_stop_x_;
  new_longitude_ = new_longitude_ / 2;
  float previous_stop_y_ = (previous_stop_->GetLatitude());
  float new_latitude_ = (current_stop_->GetLatitude()) + previous_stop_y_;
  new_latitude_ = new_latitude_ / 2;
  bus_data_.position.x = new_longitude_;
  bus_data_.position.y = new_latitude_;
  bus_data_.capacity = passenger_max_capacity_;
}
BusData Bus::GetBusData() {
// tested
// get bus most recent data
  return bus_data_;
}
size_t Bus::GetNumPassengers() {
// tested
  int num = GetHowManyPassengerOnBus();
  size_t passengerSize = (size_t)num;
  return passengerSize;
}
Stop* Bus::GetBusPreviousStop() {
// tested
  return previous_stop_;
}
bool Bus::LoadPassenger(Passenger * new_passenger) {
// tested
  int number_of_passengers_on_bus = GetHowManyPassengerOnBus();
  if (number_of_passengers_on_bus < passenger_max_capacity_) {
// add passenger iff there exist 1 slot left
    passengers_.push_back(new_passenger);
    return true;
  } else {
    return false;
  }
}
int Bus::HowManySeatsLeft() {
// tested
// get how many seat left
int number_of_passengers_on_bus = GetHowManyPassengerOnBus();
return passenger_max_capacity_ - number_of_passengers_on_bus;
}
bool Bus::NotFull() {
// tested
int number_of_passengers_on_bus = GetHowManyPassengerOnBus();
if (number_of_passengers_on_bus < passenger_max_capacity_) {
return true;
}
return false;
}
int Bus::GetHowManyPassengerOnBus() {
// tested
  int count = 0;
  if (passengers_.empty()) {
    return 0;
  }
  for ( std::list<Passenger *>::iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
// increment iff there exist 1 passenger on bus
  count+=1;
  }
  return count;
}
void Bus::UnloadPassengers() {
// loop below unloads passengers before load passengers
  for (std::list<Passenger* >::iterator it = passengers_.begin();
it != passengers_.end(); it++) {
int here_ = current_stop_->GetId();
// checking if each passenger want to get off at current stop
if (here_ == (*it)->GetDestination()) {
passengers_.remove(*it);
it--;
}
}
}

bool Bus::Move() {
// tested
if (speed_ >= distance_remaining_) {
// here at a stop. Load passengers
previous_stop_ = current_stop_;

distance_remaining_ = current_route_->GetNextStopDistance();

// unloads passengers before load passengers
UnloadPassengers();

UpdateBusData();
if (current_route_->IsLastStop(current_stop_)) {
// bus sitting at last stop, better switch route
number_route_complete_ += 1;
switchRoute();
}

// finish unloading, now load passengers
if (!IsTripComplete()) {
// this is to prevent picking up after complete trip
current_stop_->LoadPassengers(this);
UpdateBusData();
}
current_route_->NextStop();  // stop needs to be at
next_stop_ = current_route_ -> GetDestinationStop();
current_stop_ = next_stop_;
return true;
} else {  // not there yet, if (speed_ < distance_remaining_)
  distance_remaining_ -= speed_;
UpdateBusData();

  return true;
}
}
void Bus::switchRoute() {
// loop emptying passenger list at LAST stop
while (!passengers_.empty()) {
passengers_.pop_front();
}
////  switching route
if (current_route_ == outgoing_route_) {
current_route_ = incoming_route_;
current_stop_ = current_route_ -> GetDestinationStop();
distance_remaining_ = current_route_ -> GetNextStopDistance();
//  reset distance_reminaing
} else {
current_route_ = outgoing_route_;
current_stop_ = current_route_ -> GetDestinationStop();
distance_remaining_ = current_route_ -> GetNextStopDistance();
////  done switching route
}
}

// bool Refuel() {
//  //This may become more complex in the future
//  fuel_ = max_fuel_;
//}

void Bus::Update() {  //  using common Update format
// Update all passenger on bus before Move()
if (!IsTripComplete()) {
if (pick_up_at_first_stop_ != 1) {
  // or is it true that pick_up_at_first_stop_ is zero
// this design is to prevent double update at the first stop
// pick_up_at_first_stop_ is 0 to prevent double update at first stop
// pick_up_at_first_stop_ is 1 if already pick up at first stop
// then do not update passengers on bus
for (std::list<Passenger *>::iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    (*it)->Update();
}
Move();
}
pick_up_at_first_stop_ = 0;
} else {
UpdateBusData();
}
//  this is to avoid double update the passenger just get on the bus
//  no need to update route or whatsoever
}
bool Bus::IsTripComplete() {
return number_route_complete_ == 2;
}
void Bus::Report(std::ostream &  out) {
  out << "Name: " << name_ << std::endl;
  out << "Speed: " << speed_ << std::endl;
  out << "Distance to next stop: " << distance_remaining_ << std::endl;
  out << "\tPassengers (" << passengers_.size() << "): " << std::endl;
  for (std::list<Passenger *>::iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}
