/**
 * @file route.h
 *
 * @Copyright 2019 3081 Staff and Dat le, All rights reserved.
 */

#include "src/route.h"
#include <vector>

Route::Route(std::string name, Stop ** stops, double * distances, int num_stops,
PassengerGenerator * pg) {
// tested
  // std::cout<<"BEGINNING..\n";
  for (int i = 0; i < num_stops; i++) {
    stops_.push_back(stops[i]);
    last_stop_object_reference_ = stops[i];
  }
  for (int i = 0; i < num_stops - 1; i++) {
    distances_between_.push_back(distances[i]);
  }
  stop_iterator = stops_.begin();
  destination_stop_ = *stop_iterator;
  distances_between_iterator_ = (distances_between_.begin());
  name_ = name;
  num_stops_ = num_stops;
  generator_ = pg;
  routeData.id = name;
  UpdateRouteData();
}
std::string Route::GetName() {
// tested
  return name_;
}
std::list<Stop *> Route::GetStops() {
// tested
  return stops_;
}
Stop* Route::GetLastStop() {
  return last_stop_object_reference_;
}
int Route::GetNumberOfStop() {
  return num_stops_;
}
void Route::UpdateRouteData() {
  routeData.id = name_;
  std::vector<StopData> stopDataVector;
  std::list<Stop *>::iterator it1 = stops_.begin();
  // while loop below create a temporary stop and add it to stop vector
  while (it1 != stops_.end()) {
      StopData tempStopData = (*it1)->GetStopData();
      stopDataVector.push_back(tempStopData);
      it1++;
    }
    routeData.stops = stopDataVector;
}

RouteData Route::GetRouteData() {
// tested
UpdateRouteData();
  return routeData;
}
Route* Route::Clone() {
// tested
  /*
  why? if all bus share the same Route,
   -chances that stop list iterator can be misplaced
  1. create a new set of stop that reference to all the orginal stop object
  2. create a new set of distance that
    copy all the orginal distance_remaining's stop object
  3. passing thru name and num_stop to the constructor
  4. return a pointer to the new Route object
  */
  // TODO(me): delete new things to prevent mem leak
  Stop ** stop_t_ = new Stop*[stops_.size()];
  int i = 0;
  std::list<Stop *>::iterator it1 = stops_.begin();
// loop belows make deep copy of stop list
  while (it1 != stops_.end()) {
     stop_t_[i] = *it1;
     it1++;
     i+=1;
  }
  double * distances_t_ = new double[distances_between_.size()];
  int y = 0;
// loop belows make deep copy of distance_between list
  for (std::list<double >::iterator it = distances_between_.begin();
  it != distances_between_.end(); it++) {
  distances_t_[y] = *it;
  y+=1;
  }
  Route* temp = new Route (name_, stop_t_,
  distances_t_, num_stops_, generator_);
  return temp;
}
void Route::NextStop() {
// tested
// increment stop_iterator if stop_iterator not at the end of its list
  if (!IsAtEnd()) {
  stop_iterator++;
  destination_stop_ = *stop_iterator;
  if (distances_between_iterator_ != distances_between_.end()) {
// increment distances_between_iterator_ if it not at the end of its list
  distances_between_iterator_++;
  }
}
}
Stop* Route::GetDestinationStop() const {
// tested
return destination_stop_;
}
bool Route::IsLastStop(Stop* s) {
// tested
return s == last_stop_object_reference_;
}
double Route::GetNextStopDistance() const {
// tested
// return the value that distances_between_iterator_ pointing to
if (distances_between_iterator_ != distances_between_.end()) {
return *distances_between_iterator_;
} else {
  return 0;
}
}
bool Route::IsAtEnd()const {
// tested
// return if last_stop id is the same as stop_iterator stop object
return last_stop_object_reference_ == (*stop_iterator);
}

void Route::Update() {
// tested
// update all of its stops
  GenerateNewPassengers();
// this is to prevent wait stop is 0
  for (std::list<Stop *>::iterator it = stops_.begin();
  it != stops_.end(); it++) {
    (*it)->Update();
  }
  //  create new passenger then update stop will double update passenger.
  //  calling GenerateNewPassengers after update stops to avoid it
  UpdateRouteData();
}

void Route::Report(std::ostream &  out) {
  out << "Name: " << name_ << std::endl;
  out << "Num stops: " << num_stops_ << std::endl;
  int stop_counter = 0;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
  it != stops_.end(); it++) {
    (*it)->Report(out);
    stop_counter++;
  }
}
int Route::GenerateNewPassengers() {
  generator_->GeneratePassengers();
  return 1;
}
