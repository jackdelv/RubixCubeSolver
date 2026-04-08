# To build this project from external build directory

mdkir build
cd build
cmake -S ../RubixCubeSolver -B .
cmake --build .

Generates an executable for the Rubix Cube core class and a library that is linked with the cuble game