#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cassert>
#include <cstring>

#include "rubixCube.hpp"

// #######################
// Utility functions
// #######################

void testRotations()
{
    RubixCube cubeControl;
    RubixCube cubeTest;
    std::cout << "*************************************************" << std::endl;
    std::cout << "Testing RubixCube Class" << std::endl;
    std::cout << "*************************************************" << std::endl;
    cubeTest.rotateCW(UP).rotateCW(UP).rotateCW(UP).rotateCW(UP);
    assert(cubeControl.equivalent(cubeTest));
    cubeTest.rotateCW(DOWN).rotateCW(DOWN).rotateCW(DOWN).rotateCW(DOWN);
    assert(cubeControl.equivalent(cubeTest));
    cubeTest.rotateCW(FRONT).rotateCW(FRONT).rotateCW(FRONT).rotateCW(FRONT);
    assert(cubeControl.equivalent(cubeTest));
    cubeTest.rotateCW(BACK).rotateCW(BACK).rotateCW(BACK).rotateCW(BACK);
    assert(cubeControl.equivalent(cubeTest));
    cubeTest.rotateCW(LEFT).rotateCW(LEFT).rotateCW(LEFT).rotateCW(LEFT);
    assert(cubeControl.equivalent(cubeTest));
    cubeTest.rotateCW(RIGHT).rotateCW(RIGHT).rotateCW(RIGHT).rotateCW(RIGHT);
    assert(cubeControl.equivalent(cubeTest));
    std::cout << "Testing clockwise rotation successful" << std::endl;
    std::cout << "*************************************************" << std::endl;

    cubeTest.rotateCCW(UP).rotateCCW(UP).rotateCCW(UP).rotateCCW(UP);
    assert(cubeControl.equivalent(cubeTest));
    cubeTest.rotateCCW(DOWN).rotateCCW(DOWN).rotateCCW(DOWN).rotateCCW(DOWN);
    assert(cubeControl.equivalent(cubeTest));
    cubeTest.rotateCCW(FRONT).rotateCCW(FRONT).rotateCCW(FRONT).rotateCCW(FRONT);
    assert(cubeControl.equivalent(cubeTest));
    cubeTest.rotateCCW(BACK).rotateCCW(BACK).rotateCCW(BACK).rotateCCW(BACK);
    assert(cubeControl.equivalent(cubeTest));
    cubeTest.rotateCCW(LEFT).rotateCCW(LEFT).rotateCCW(LEFT).rotateCCW(LEFT);
    assert(cubeControl.equivalent(cubeTest));
    cubeTest.rotateCCW(RIGHT).rotateCCW(RIGHT).rotateCCW(RIGHT).rotateCCW(RIGHT);
    assert(cubeControl.equivalent(cubeTest));
    std::cout << "Testing counter-clockwise rotation successful" << std::endl;
    std::cout << "*************************************************" << std::endl;

    RubixCube cubeCW;
    RubixCube cubeCCW;
    assert(!cubeCW.rotateCW(UP).equivalent(cubeCCW.rotateCCW(UP)));
    assert(!cubeCW.reset().rotateCW(DOWN).equivalent(cubeCCW.reset().rotateCCW(DOWN)));
    assert(!cubeCW.reset().rotateCW(FRONT).equivalent(cubeCCW.reset().rotateCCW(FRONT)));
    assert(!cubeCW.reset().rotateCW(BACK).equivalent(cubeCCW.reset().rotateCCW(BACK)));
    assert(!cubeCW.reset().rotateCW(LEFT).equivalent(cubeCCW.reset().rotateCCW(LEFT)));
    assert(!cubeCW.reset().rotateCW(RIGHT).equivalent(cubeCCW.reset().rotateCCW(RIGHT)));
    std::cout << "Testing CW and CCW are unique is successful" << std::endl;
    std::cout << "*************************************************" << std::endl;
}

void gatherStats(int moves = 100000, bool showCubes=false)
{
    // Solved 1000000 Random Rubix Cubes with a min move set size of 62 and Max move set of 292
    // The average Move set size was 177 moves.
    // Finished in 24 minutes 3 seconds.

    RubixCube randomCube;
    int32_t minMoves = 256;
    int32_t maxMoves = 0;
    int64_t totalMoves = 0;
    MoveSet minMoveSet;
    MoveSet maxMoveSet;
    RubixCube minCube;
    RubixCube maxCube;
    std::time_t startTime = time(0);
    uint64_t i = 0;

    while (i < moves)
    {
        randomCube = RubixCube(50);
        RubixCubeSolver solver;
        if (showCubes)
            randomCube.print();
        MoveSet moveSet = solver.solveCube(randomCube);
        if (showCubes)
        {
            /**
             * solveCube does not return a solved cube. It asserts that the moves it recorded
             * produced a solved cube from the one that was passed in.
             * To show the results we need to either create a new cube or solve the randomCube
             * using the output moveSet. Feels clunky but too much of a hassle to fix ATM.
             */

            RubixCube solvedCube;
            solvedCube.print();
        }

        if (moveSet.size() < minMoves)
        {
            minMoves = moveSet.size();
            minMoveSet = moveSet;
        }

        if (moveSet.size() > maxMoves)
        {
            maxMoves = moveSet.size();
            maxMoveSet = moveSet;
        }

        totalMoves += moveSet.size();
        i++;
    }

    int elapsedTime = time(0) - startTime;
    std::cout << std::endl << "Solved " << i << " Random Rubix Cubes with a min move set size of " << minMoves << " and Max move set of " << maxMoves <<  std::endl;
    std::cout << "The average Move set size was " << totalMoves / i << " moves with an average time of " << (double) elapsedTime / (double) moves << " seconds." << std::endl;
    std::cout << "Finished in " << (int)(elapsedTime / 60) << " minutes " << elapsedTime % 60 << " seconds." << std::endl;
}

int parseCommandLineArguments(int argc, char*argv[])
{
	if (argc==1)
    {
        std::cout << std::endl;
        std::cout << "==========================================================================================" << std::endl;
		std::cout << "Rubix Cube Solver. Can generate a random rubix cube, print one out, and solve them." << std::endl;
		std::cout << "The following arguments can be passed to use this utility:" << std::endl << std::endl;
        std::cout << "test                   | Test the RubixCube class" << std::endl;
		std::cout << "print(int n=0)         | Print Rubix Cube. n is the number of randoms moves to make before printing." << std::endl;
		std::cout << "solve(int n=1, bool s) | Solve Rubix Cubes. n is the number of cubes to solve. Pass in s to show the before/after for each cube. (e.g. solve n 1000 s)" << std::endl;
        std::cout << "showMoves(int n=0)     | Solve a Rubix cube, but show each individual move. n is the number of moves to show from the end i.e. n=10 will show the last 10 moves. No argument shows all moves." << std::endl;
        std::cout << std::endl;
        return 0;
    }

    if (argc > 5)
    {
        std::cout << "Error: Too many arguments" << std::endl;
        return -1;
    }

    if (strcmp(argv[1], "print")==0)
    {
        unsigned i = 0;
        if (argc > 2)
            i = std::stoi(argv[2]);
        RubixCube cube(i);
        cube.print();
    }
    else if (strcmp(argv[1], "solve")==0)
    {
        unsigned numCubes = 1;
        bool showCubes = false;
        if (argc > 2)
        {
            int i = 2;
            while (true)
            {
                if (i >= argc)
                    break;

                const char *option = argv[i++];
                switch (option[0])
                {
                    case 'n':
                    {
                        if (i >= argc)
                        {
                            std::cout << "Missing argument for number of cubes to solve" << std::endl;
                            return -4;
                        }

                        numCubes = std::stoi(argv[i++]);
                        break;
                    }
                    case 's':
                    {
                        showCubes = true;
                        break;
                    }
                    default:
                    {
                        std::cout << "Unknown solve options: " << option << std::endl;
                        return -5;
                    }
                }
            }
        }
        gatherStats(numCubes, showCubes);
    }
    else if (strcmp(argv[1], "showMoves")==0)
    {
        RubixCube cube(100);
        RubixCubeSolver solver;
        MoveSet moves = solver.solveCube(cube);
        unsigned numMoves = moves.size();
        int i = 0;
        int offset = 0;

        if (argc > 2)
        {
            offset = numMoves - std::stoi(argv[2]);
            assert(offset>=0);
        }

        std::cout << "== Starting Cube ==" << std::endl;
        cube.print();
        for (; i < numMoves; i++)
        {
            const char * direction = std::get<2>(moves[i]);

            if (strcmp(direction, "CW") == 0)
                cube.rotateCW(std::get<0>(moves[i]));
            else if (strcmp(direction, "CCW") == 0)
                cube.rotateCCW(std::get<0>(moves[i]));
            else
            {
                std::cout << "Error: unknown direction from solved move set ( " << direction << " )" << std::endl;
                return -3;
            }

            if (i >= offset)
            {
                std::cout << "== Rotating " << colorToChar(static_cast<RubixColor>(std::get<0>(moves[i]))) << " "<< direction << " ==" << std::endl << std::endl;
                cube.print();
            }
        }
    }
    else if (strcmp(argv[1], "test")==0)
    {
        testRotations();
    }
    else
    {
        std::cout << "Error: Unrecognized command " << argv[1] << std::endl;
        return -2;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // This project uses rand to create psuedo random moves for generating valid cubes
    srand(time(0));
    return parseCommandLineArguments(argc, argv);

    int mode = 0;
    if (argc > 1)
        mode = std::stoi(argv[1]);

    switch (mode)
    {
        case 1:
        {
            RubixCube cube2(250);
            RubixCubeSolver solver;
            solver.solveCube(cube2);
            break;
        }
        case 2:
        {
            if (argc == 3)
                gatherStats(std::stoi(argv[2]));
            else
                gatherStats();
            break;
        }
        case 3:
        {
            testRotations();
            break;
        }
        case 4:
        {

            break;
        }
        default:
            std::cout << "1: RubixCubeSolver, 2: Dummy Solver (Try unfinished RubixCubeSolver repeatedly), 3: Test rotations" << std::endl;
    }

    return 0;
}
