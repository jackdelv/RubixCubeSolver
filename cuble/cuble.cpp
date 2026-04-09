#include <iostream>

int playDailyPuzzleMode()
{
    return 0;
}

int playSurvivalMode()
{
    return 0;
}

int main(int argc, char *argv[])
{
    std::cout << "#####################################################################################################################" << std::endl;
    std::cout << "#                                                                                                                   #" << std::endl;
    std::cout << "#                                                Welcome to Cuble!                                                  #" << std::endl;
    std::cout << "#                                                                                                                   #" << std::endl;
    std::cout << "# Cuble is an interactive puzzle game based on the Rubix Cube. Choose a mode:                                       #" << std::endl;
    std::cout << "#                                                                                                                   #" << std::endl;
    std::cout << "# Mode 1: Daily Puzzle Mode                                                                                         #" << std::endl;
    std::cout << "#      Choose between Easy Medium and Hard and get a randomized cube. Solve it in the fewest moves possible to win. #" << std::endl;
    std::cout << "#                                                                                                                   #" << std::endl;
    std::cout << "# Mode 2: Survival Mode                                                                                             #" << std::endl;
    std::cout << "#      Solve harder and harder puzzles and earn points to get a high score                                          #" << std::endl;
    std::cout << "#                                                                                                                   #" << std::endl;
    std::cout << "#####################################################################################################################" << std::endl;
    std::cout << std::endl << "Select a mode: ";
    unsigned mode;
    std::cin >> mode;
    switch (mode)
    {
        case 1:
            std::cout << "Playing Daily Puzzle Mode..." << std::endl;
            return playDailyPuzzleMode();
        case 2:
            std::cout << "Playing Survival Mode..." << std::endl;
            return playSurvivalMode();
        default:
            std::cout << "Invalid input " << mode << std::endl;
            return -1;
    }

    return 0;
}