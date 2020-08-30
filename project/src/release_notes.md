#Refactoring

Refactoring 1 and 2 are in refactor/iter3 branch.
Refactoring documents is refactor.pdf in docs directory

#Issues

Refer to my Git issues

#Assumptions

All simulation run from project directory and on CSE Linux lab machines

#Regression Testing

This program consists of two regression tests. One exists in the driver directory and one exists in tests directory.To run the first regression test, change directory to project/src. Users navigate to file passenger_factory.cc and then un-comment line 16. Then run "make my_regression_test" in directory project/src.
Navigate to project directory, run ./build/bin/my_regression_test > output because build folder is not tracked
Move the output file to tests directory and run "diff myrout1Expected output".To run the second regression test,navigate to project/tests. Then run make. After program is completely built, run ../build/bin/unittest. Lastly,run "diff Reg01_output.txt Reg01_expected.txt"

#UML
Updated UML as UML_FINAL_2.pdf