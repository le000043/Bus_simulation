<!-- **NOTE**: Please make sure that **all Tests** pass before pushing any changes.  -->
**Purpose**: The purpose of this program is to let users simulate a bus simulation.
**Description**In the simulation, passengers will appear at stops based on a determined probability. Each bus has two routes which are outgoing and incoming. Each stop will consist of a list of stops. Each bus will pick up and drop off passengers at each stop. The user will later be guided how to customize routes, stops, probability of generating passengers at each stop, the length of simulation, and the time between busses in each route. The user is expected to use CSE Linux lab machine to run the simulation. There are two ways to visualize a simulation. They are running a simulation with a visualizer(vis_sim) and running a simulation without a visualizer(config_sim). Vis_sim is for those who want to visualize the simulation. Config_sim is for those who wish to control their simulation via terminal and/or run the simulation on a non-default configuration file. The sequence of steps below will guide users on three options: running a simulation, customizing default configuration file, or creating and then running simulation on a new configuration file.
<!-- ### Run Tests:

- cd `tests`
- `make`
- `../build/bin/unittest` -->

<!-- ### Style Check:

- `[path_to_cpplint]/cpplint/cpplint-cse.sh --root=[path_target_dir] [file_name]` -->
### Setting up:
1. First, we need to clone the program.
2. Open users favorite browser, Google Chrome is the preferable choice here.
3. Before moving forward, users need to set up a github.umn.edu account. On users browser, create a new tab and type https://github.umn.edu/ . Hit Enter.
4. For this link to generate public SSH keygen: https://help.github.com/en/github/authenticating-to-github/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
5. Copy users ssh keygen to users UMN github account. Now users are able to clone the program.
6. On users browser, create a new tab and typehttps://github.umn.edu/umn-csci-3081-f19/repo-le000043. Hit Enter.
7. Click on the green box "Clone or Download program". A link will show up. Users then copy the given link.
8. On CSE Linux lab machine, open a Terminal. If users do not know where and how to open terminal, refer to the
   following link: https://www.howtogeek.com/howto/22283/four-ways-to-get-instant-access-to-a-terminal-in-linux/
9. In terminal, type "cd". Hit Enter.
10. Then type "mkdir CSCI3081". Hit Enter.
11. Then type "cd CSCI3081". Hit Enter.
12. Then type "git clone git@github.umn.edu:umn-csci-3081-f19/repo-le000043.git". Hit Enter.
13. Users are expected to observe a download from git.
14. When the download is complete, type "cd repo-le000043".



#### Running simulation without a visualizer
 a) Overview of Configuration file
 1. Type "cd project/src". Hit Enter.
 2. Type "make". Hit Enter.
 3. Users are expected to wait a few seconds for the program to compile.
 4. When the terminal stops running, users then type this on the terminal:"cd .." to go back to the previous directories. Hit Enter.
 5. Type "cd config". Hit Enter.
 6. Type "cat config.txt". Hit Enter.
 7. Read-only content of config.txt will be shown in the terminal.
 8. If users know how to edit configuration file in terminal, ignore step 9.
 9. Refer to http://www.mactricksandtips.com/2008/02/edit-text-file-in-terminal.html if users want to edit config.txt in terminal.
 10. Each general route consists of two routes which are outgoing and incoming. The first route of each general route is always the outgoing route. Each bus will run on outgoing route first.
 11. First line of config.txt gives the token name which is ROUTE_GENERAL followed by the name of the general route which is "Campus Connector". Line 5 of config.txt consists of Route token name and route name which is "East bound".
 12. If users want to add stop to a route, they must strictly follow the configuration rule which is Stop name, then longitude of the stop, latitude of the stop,
    and probability to generate passengers.
 13. If users decide to add more routes, users must add an even number of routes. Otherwise, routes will not be registered by the program.
 14. The existing template of config.txt must be strictly followed if users add one more general route (2 normal routes).
 15. If a general route is added then the second bus, fourth bus, sixth bus, etc will have second general route.
 16. The first bus, third bus, fifth bus, etc will have first general route.
 17. The format of the command to run the simulation is: ./build/bin/configuration_sim <config_filename> <length of simulation> <time between busses for first route> <time between for second route>
 18. Every general route requires two additional inputs of time between busses for its two routes.
 19. If users wish to create a new configuration file, users must follow the provided template inside the config.txt. New configuration file must be inside config folder.

### Running simulation with configuration file
1. In project/src directory. Type "make clean". Hit Enter.
2. Type "make". Hit Enter.
3. Repeat steps 3 and 4 of "a) Overview of Configuration file".
4. Type "./build/bin/vis_sim 8081". Then hit Enter. The number 8081 is a port number. A port number has to be greater than 8000 and not multiples of 10.
5. Open favorite browser, type http://127.0.0.1:8081/web_graphics/project.html. 8081 here can be replaced by whatever port number users had pick previously.
6. Before hitting start, there are 3 slide bars that represent the length of simulation, time between busses of first route, and time between busses of second route. Adjust the bar to get desirable simulation configuration.
7. Click Start to observe the simulation.
8. To stop the simulation, go back to the terminal where users compile the program, hit Ctrl+C.
9. If users want to re-run user program, refer to steps 5-6 of "B. Running a simulation with a visualizer".
10. If users made changes in config.txt, repeat step 8 of "Running a simulation with a visualizer", type "cd src". Hit Enter. The repeat steps 3 and 4 of "B. Running a simulation with a visualizer"
**<port_number> can be anything. Try and pick numbers above 8000 and not multiples of 10.**

### TESTING
 **Regression Test**
 This program consists of two regression tests. One exists in the driver directory and one exists in tests directory.
 To run the first regression test, change directory to project/src. Users navigate to file passenger_factory.cc and then un-comment line 16.
 Then run "make my_regression_test" in directory project/src.
 Navigate to project directory, run ./build/bin/my_regression_test > output because build folder is not tracked
 Move the output file to tests directory and run "diff myrout1Expected output"
 To run the second regression test, navigate to project/tests. Then run make. After program is completely built, run ../build/bin/unittest
 run "diff Reg01_output.txt Reg01_expected.txt"

### DEVELOPER Guide:
 * **DESIGN OVERVIEW:**
 * Separated graphic from the simulator is significant. The reason is that simulation model can be made without graphics. Therefore, models can be done in case time is limited.
 * Also, implementing two separated designs is less abstract than implementing one large design. Making vis_sim target will build graphics to help user visualize the simulation.
 * Configuration sim is designed in a way that user can change simulation parameters such as length of simulation and time between busses in the terminal. For future developer, navigate to project/src directory and type "make" and Enter to
 * make all target. Both config_sim and vis_sim must be run from project directoy instead of src directory. 
 **Main Classes overview**
 * Passenger: each Passenger has a stopId of where he/she wants to be at.
 * Also, time_on_bus_ and wait_at_stop_ of each
 * passenger indicate the time passenger traveling on bus and waiting at the stop respectively.
 * Each passenger is uniquely identified by id and name.
 * Each passenger has a constructor, private variables update method, a setter of time_on_bus_,
 * a getter of stopId and a getter of total waiting time which is a sum of time traveling on bus and waiting at stop.
 * Passengers will be either on a bus or at a stop, it makes sense that either the stop or the bus that passenger at will invoke passenger Update method.
 * Additionally, each passenger has a report method to print out value of all private variables.

 * Stop: Inside the list of private variables of each stop object, each stop stores a longitude, latitude, stop ID and a list of passengers.
 * Each stop object has a constructor to initialize its stop ID, longitude and latitude. As passengers will wait at a stop then stop needs to have a list of passengers waiting at it.
 * AddPassenger method will push a given passenger to its
 * passenger list. AddPassenger is needed as otherwise there are no other ways to add passengers to stops. Each stop also has loading passenger onto the bus method,
 * this method only add passenger to bus as long as its passenger list is not empty and the bus is not full. The reason why stop has a loading passenger method is that passenger list is private
 * so loading passenger to bus within stop object makes sense.
 * Each stop has an Update method that update all of its passengers. Each stop will have a getter of its stop ID. Report method of each stop object will report its ID and
 * how many passengers waiting at the stop. Class Stop has a method that is used by Route to extract the location and number of passenger waiting at stop.

 * Route: route is a collection of stops then each route will store a list of stop with an iterator and a list of distance between stops with an iterator. Also, each route will have a pointer pointing to
 * the last stop object. By recording the last stop reference, it can be used to see if the bus is actually at the last stop in method IsLastStop. Also current stop will be recorded so it can be used
 * by bus. Therefore, bus will know what stop it needs to be at in the future after arriving at a stop. Route needs to has a clone method as other bus would not use the same stop lists otherwise,one's stop iterator
 * can be misued by others. Inside the route constructor, stop and distance remaining pointers will be initialized to the first stop and first distance remaining. A getter of next stop and next distance remaining is needed
 * for bus to quickly use. When bus arrive at stop, bus will call NextStop () on current route to update its stop pointer and distance between pointer.
 * Inside the route Update, generate passengers before Update as to prevent passenger wait_at_stop_ be zero. Route Update should not call update on bus as inside local simulator, bus update will get called twice.
 * Class Route has a method to update and extract the location of stops and the number of passenger waiting at stops to the visualizer.
 
 * Bus: bus carries passengers and travels across stops. Bus needs to have a reference to route as it needs to get the next stop from route whenever bus arrives at a stop. Also, as each bus has two routes;therefore, it is another main reason bus needs to know route.
 * Bus needs to know if it needs to switch route and what route to switch to, which is another reason bus needs to know its route. Bus have reference to stop as it needs to know if the stops it arrives at is the last stop to switch route.
 * bus also needs to handle passenger unloading/loading. Passengers on the bus cannot remove its self from the list;therefore, bus needs to remove certain passengers off the list when it arrive at stops. Bus also needs to takes care of the loading passenger as
 * stop cannot publicly accessed bus private list of passengers. Move() should takes care the task of loading and unloading passengers whenever it arrives at stop. Last but not least, if bus finishes 2 routes, it should be allowed to move or update. Bus update only updates
 * its passenger on the bus. No other classes except local sim should call bus update to prevent double update passenger and moving twice in one time step. PassenegerManager class is not needed as loading and unloading passengers can be handled in methods. Bus class have methods to update and extract
 * bus location, and number of passengers on the bus to the visualizer.

**Use `vis_sim` in place of the `<sim target>` and `<sim executable>` arguments above.**
