#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <functional>

#include "rubixCube.hpp"

size_t getDailyHash() {
    // 1. Get current system time
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // 2. Convert to local time structure
    std::tm* now_tm = std::localtime(&now_c);

    // 3. Format as "YYYY-MM-DD" into a char buffer
    char buf[11]; // "YYYY-MM-DD" + null terminator
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", now_tm);

    // 4. Hash the resulting string
    return std::hash<std::string>{}(std::string(buf));
}

int playDailyPuzzleMode()
{
    size_t hash = getDailyHash();
    std::cout << std::endl << "Today's game code is: " << hash << std::endl;
    std::cout << std::endl << "Select a difficulty level (1-5): ";
    unsigned level;
    std::cin >> level;
    if (level > 5)
        level = 5;
    else if (level == 0)
        level = 1;

    std::cout << "Generating ";
    switch (level)
    {
        case 1:
            std::cout << "beginner ";
            break;
        case 2:
            std::cout << "novice ";
            break;
        case 3:
            std::cout << "intermediate ";
            break;
        case 4:
            std::cout << "advanced ";
            break;
        case 5:
            std::cout << "pro ";
            break;
    }
    std::cout << "level cube" << std::endl;


    unsigned moves = level == 5 ? 12 : level + 1;
    RubixCube puzzle;
    unsigned hashCopy = hash;
    std::vector<char> moveSet;
    while (moves > 0)
    {
        unsigned move = hashCopy % 10;
        hashCopy /= 10;
        // std::cout << "Move: " << move << " hash: " << hash << std::endl;
        switch (move)
        {
            case 0:
                puzzle.rotateCW(UP);
                moveSet.push_back('U');
                break;
            case 1:
                puzzle.rotateCW(DOWN);
                moveSet.push_back('D');
                break;
            case 2:
                puzzle.rotateCW(LEFT);
                moveSet.push_back('L');
                break;
            case 3:
                puzzle.rotateCW(RIGHT);
                moveSet.push_back('R');
                break;
            case 4:
                puzzle.rotateCW(FRONT);
                moveSet.push_back('F');
                break;
            case 5:
                puzzle.rotateCW(BACK);
                moveSet.push_back('B');
                break;
            case 6:
                puzzle.rotateCW(UP);
                moveSet.push_back('U');
                break;
            case 7:
                puzzle.rotateCW(FRONT);
                moveSet.push_back('F');
                break;
            case 8:
                puzzle.rotateCW(LEFT);
                moveSet.push_back('L');
                break;
            case 9:
                puzzle.rotateCW(DOWN);
                moveSet.push_back('D');
                break;
        }
        moves--;
    }

    // std::cout << std::endl << "Cube has been rotated " << moveSet.size() << " times." << std::endl;

    puzzle.print();

    unsigned lives = 3;
    int index = moveSet.size()-1;
    while (lives > 0)
    {
        // std::cout << "lives: " << lives << " index: " << index << std::endl;
        if (index < 0)
        {
            std::cout << "Congratulations! You have solved today's cuble with " << lives << (lives > 1 ? " lives" : " life") << " left!" << std::endl;
            return 0;
        }

        std::cout << "Move: ";
        char input;
        std::cin >> input;

        if (std::tolower(input, std::locale()) != std::tolower(moveSet[index], std::locale()))
        {
            std::cout << std::endl << "OUCH! Try Again." << std::endl;
            // std::cout << input << " != " << moveSet[index] << std::endl;
            lives--;
        }
        else
        {
            switch (input)
            {
                case 't':
                case 'T':
                case 'u':
                case 'U':
                    puzzle.rotateCCW(UP);
                    break;
                case 'd':
                case 'D':
                    puzzle.rotateCCW(DOWN);
                    break;
                case 'f':
                case 'F':
                    puzzle.rotateCCW(FRONT);
                    break;
                case 'b':
                case 'B':
                    puzzle.rotateCCW(BACK);
                    break;
                case 'l':
                case 'L':
                    puzzle.rotateCCW(LEFT);
                    break;
                case 'r':
                case 'R':
                    puzzle.rotateCCW(RIGHT);
                    break;
                default:
                    std::cout << "Error: Invalid input" << std::endl;
            }
            index--;
            std::cout << std::endl << "Correct!" << std::endl << std::endl;
            puzzle.print();
        }
    }

    std::cout << std::endl << "\tYOU DIED" << std::endl;

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