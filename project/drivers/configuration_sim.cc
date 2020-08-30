/**
 * @file configuration_sim.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <iostream>
#include <fstream>
#include <string>
#include "src/config_manager.h"
#include "src/configuration_simulator.h"
// std::string Printing(std::string message) {
//   return message;
// }
// DONE refactoring 2: Extract Method
void RunningDefault(int length_of_simulation_, ConfigManager * configManager,
std::vector<int> busStartTimings);

void RunningDefault(int length_of_simulation_, ConfigManager * configManager,
std::vector<int> busStartTimings) {
      configuration_simulator *configSimulator =
      new configuration_simulator (configManager);
      configSimulator->Start(busStartTimings, length_of_simulation_);
      for (int i = 0; i < length_of_simulation_; i++) {
      configSimulator->Update();
      }
}
int main(int argc, char**argv) {
  /*
    if input is ./build/bin/configuration_sim,
        then config_sim will run with config.txt as default
    if input is ./build/bin/configuration_sim 123.txt which not exists,
        then program will print warning and stops
    if input is ./build/bin/configuration_sim config.txt,
        then program will run with file config.txt with
        length of simulation is 25
    if input file is empty, then it run defaults
  */
  std::cout << "Usage: ./build/bin/configuration_sim <config_filename>";
  std::cout << " <length of simulation> ";
  std::cout << " <time between busses for first route> ";
  std::cout << "<time between for second route>\n";
  /*
  config_filename = argv[1]
  length of simulation = argv[2]
  time between busses for first route = argv[3]
  time between for second route = argv[4]
  etc depends on how many routes we receving from configManager.GetRoutes().size()
  */
int length_of_simulation_ = 25;
std::vector<int> busStartTimings;
// std::string file_name_;
std::ifstream ifile;
std::cout << argc <<" this many arguments\n";
if (argc >= 2) {
  std::string file_name_ = argv[1];
  std::cout << argv[1] << std::endl;
  ifile.open("config/" + (file_name_));
}
  if (argc >= 2 && ifile) {
    // file exists, carry on
    ConfigManager * configManager = new ConfigManager ();
    configManager-> ReadConfig(argv[1]);
    int number_of_Routes_ = configManager->GetRoutes().size();
    std::cout << "Number of routes found: " << number_of_Routes_ << std::endl;
    int number_of_General_Routes_ = number_of_Routes_ / 2;
    if (argc > (3 + number_of_General_Routes_)) {
      std::cout << "Too many arguments\n";
      std::cout << "Please re-run the program with proper arguments\n";
      return 0;
    } else {
      if (argc == (3+number_of_General_Routes_)) {
        if (atoi(argv[2]) > 0) {
          length_of_simulation_ = atoi(argv[2]);
        } else {
          std::cout << "length_of_simulation_ is negative !\n";
          return 0;  // length_of_simulation_ is negative !
        }
        for (int i = 0; i < number_of_General_Routes_; i++) {
        if (std::atoi(argv[3+i]) < 0) {
          std::cout << "one of inputs is negative\n";
          return 0;  // one of inputs is negative
        }
        busStartTimings.push_back(std::atoi(argv[3+i]));
        }
      } else {
        if (number_of_Routes_ == 0) {
          std::cout << "Missing routes\n";
          std::cout << "please re run with correct amount of routes\n";
          return 0;
        }
        std::cout << "MISSING ARGUMENTS ";
        std::cout << "Running default config ";
        std::cout << "length of simulation is 25\n";
        std::cout << "Expect number of arguments: ";
        std::cout << (3+number_of_General_Routes_) << std::endl;
        std::cout << "Received: " << argc << std::endl;
        length_of_simulation_ = 25;
        for (int i = 0; i < number_of_General_Routes_; i++) {
        busStartTimings.push_back(5);
        }
      }
      // running default
     RunningDefault(length_of_simulation_, configManager, busStartTimings);
      // configuration_simulator *configSimulator =
      // new configuration_simulator (configManager);
      // configSimulator->Start(busStartTimings, length_of_simulation_);
      // for (int i = 0; i < length_of_simulation_; i++) {
      // configSimulator->Update();
      // }
     }
// close
     ifile.close();
    } else {
if (argc ==1) {
// file_name_ = "config.txt";
std::ifstream new_ifile_;
new_ifile_.open("config/config.txt");
if (new_ifile_) {
    std::cout << "RUNNING DEFAULT FILE AS NO FILE NAME PROVIDED\n";
    ConfigManager * configManager = new ConfigManager ();
    configManager-> ReadConfig("config.txt");
    int number_of_Routes_ = configManager->GetRoutes().size();
    int number_of_General_Routes_ = number_of_Routes_ / 2;
    if (number_of_Routes_ == 0) {
      std::cout << "Missing routes\n";
      std::cout << "please re run with correct amount of routes\n";
      return 0;
    }
    length_of_simulation_ = 25;
    for (int i = 0; i < number_of_General_Routes_; i++) {
        busStartTimings.push_back(5);
    }
      // running default
    RunningDefault(length_of_simulation_, configManager, busStartTimings);
// configuration_simulator *configSimulator =
// new configuration_simulator (configManager);
// configSimulator->Start(busStartTimings, length_of_simulation_);
// for (int i = 0; i < length_of_simulation_; i++) {
// configSimulator->Update();
// }
} else {
std::cout << "Default file config.txt not exists\n";
return 0;
}
new_ifile_.close();
} else {
std::cout << "FILE NOT FOUND \n";
std::cout << "PLease re-run the program with correct file name\n";
return 0;
}
  }
  // Check command line params for config file name

  // if filename arg present
  //   Create ConfigManager
  //   Call ReadConfig
  //   Create configSimulator
  //   Call Start on configSimulator
  //   Start for loop, length of simulation (where from?terminal argv)
  //     Call Update on configSimulator
  // else
  //   echo info to the user about needing a config file name
  return 0;
}
