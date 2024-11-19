#include "rubixCube.hpp"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cassert>

// #######################
// Face Class
// #######################

#define _DEBUG 0

Face::Face(RubixColor c)
{
    stickers = std::vector<std::vector<RubixColor> >(3, std::vector<RubixColor>(3, c));  
}

RubixColor Face::sticker(int row, int column) const
{
    return stickers[row][column];
}

Face & Face::rotateCW()
{
    std::vector<RubixColor> row0 = stickers[0];
    std::vector<RubixColor> row1 = stickers[1];
    std::vector<RubixColor> row2 = stickers[2];

    // Rotate rows
    stickers[0][2] = row0[0];
    stickers[1][2] = row0[1];
    stickers[2][2] = row0[2];

    stickers[0][1] = row1[0];
    // Stays the same stickers[1][1] = row1[1];
    stickers[2][1] = row1[2];

    stickers[0][0] = row2[0];
    stickers[1][0] = row2[1];
    stickers[2][0] = row2[2];

    return *this;
}

Face & Face::rotateCCW()
{
    std::vector<RubixColor> row0 = stickers[0];
    std::vector<RubixColor> row1 = stickers[1];
    std::vector<RubixColor> row2 = stickers[2];

    // Rotate rows
    stickers[0][0] = row0[2];
    stickers[1][0] = row0[1];
    stickers[2][0] = row0[0];

    stickers[0][1] = row1[2];
    // Stays the same stickers[1][1] = row1[1];
    stickers[2][1] = row1[0];

    stickers[0][2] = row2[2];
    stickers[1][2] = row2[1];
    stickers[2][2] = row2[0];

    return *this;
}

bool Face::operator==(const Face & other)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (stickers[i][j] != other.sticker(i,j))
                return false;
        }
    }

    return true;
}

unsigned Face::equivalence(const Face & other)
{
    unsigned match = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (stickers[i][j] == other.sticker(i,j))
                match++;
        }
    }

    return match;
}

void Face::reset()
{
    RubixColor color = stickers[1][1];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            stickers[i][j] = color;
        }
    }
}

// #######################
// RubixCube Class
// #######################

RubixCube::RubixCube()
: up(WHITE), down(YELLOW), front(BLUE), back(GREEN), left(RED), right(ORANGE)
{}

RubixCube::RubixCube(int moves)
: RubixCube()
{
    for (int i = 0; i < moves; i++)
    {
        if (rand() % 2)
            rotateCW(static_cast<RubixFace>(rand() % 6));
        else
            rotateCCW(static_cast<RubixFace>(rand() % 6));
    }
}

/**
 * @brief Returns the color changed string with the corresponding letter.
 * The string returned by this function will change the color of subsequent characters
 * use "\033[0m" before any follow characters to reset the color.
 * 
 * @param c Value from RubixColor struct to convert to character
 * @return const char* 
 */
const char * colorToChar(RubixColor c)
{
    switch (c)
    {
        case WHITE:
            return "\033[37mW";
        case YELLOW:
            return "\033[93mY";
        case BLUE:
            return "\033[34mB";
        case GREEN:
            return "\033[32mG";
        case RED:
            return "\033[31mR";
        case ORANGE:
            return "\033[35mO";
        default:
            return "\033[0mX";
    }
}

void RubixCube::print(int spacing)
{
    const char *sp7 = "       ";
    const char *sp6 = "      ";
    const char *sp5 = "     ";
    const char *sp4 = "    ";
    const char *sp3 = "   ";

    switch(spacing)
    {
        case 0:
        {
            std::cout << sp7 << colorToChar(up.sticker(0,0)) << sp7 << sp7 << sp3;
            std::cout << sp6 << colorToChar(left.sticker(0,0)) << " " << colorToChar(back.sticker(0,2)) << sp6 << std::endl;
            std::cout << sp4 << colorToChar(up.sticker(1,0)) << sp5 << colorToChar(up.sticker(0,1)) << sp4 << sp7 << sp3 << sp3 << colorToChar(left.sticker(0,1)) << sp7 << colorToChar(back.sticker(0,1)) << sp3 << std::endl;
            std::cout <<  " " << colorToChar(up.sticker(2,0)) << sp5 << colorToChar(up.sticker(1,1)) << sp5 << colorToChar(up.sticker(0,2)) << " " << sp7 << sp3 << colorToChar(left.sticker(0,2)) << sp5 << colorToChar(left.sticker(1,0)) << " " << colorToChar(back.sticker(1,2)) << sp5 << colorToChar(back.sticker(0,0)) << std::endl;
            std::cout << colorToChar(front.sticker(0,0)) << sp3 << colorToChar(up.sticker(2,1)) << sp5 << colorToChar(up.sticker(1,2)) << sp3 << colorToChar(right.sticker(0,2)) << sp7 << sp3 << sp3 << colorToChar(left.sticker(1,1)) << sp7 << colorToChar(back.sticker(1,1)) << sp3 << std::endl;
            std::cout << sp3 << colorToChar(front.sticker(0,1)) << sp3 << colorToChar(up.sticker(2,2)) << sp3 << colorToChar(right.sticker(0,1)) << sp3 << sp7 << sp3 << colorToChar(left.sticker(1,2)) << sp5 << colorToChar(left.sticker(2,0)) << " " << colorToChar(back.sticker(2,2)) << sp5 << colorToChar(back.sticker(1,0)) << std::endl;
            std::cout << colorToChar(front.sticker(1,0)) << sp5 << colorToChar(front.sticker(0,2)) << " " << colorToChar(right.sticker(0,0)) << sp5 << colorToChar(right.sticker(1,2)) << sp7 << sp3 << sp3 << colorToChar(left.sticker(2,1)) << sp3 << colorToChar(down.sticker(2,0)) << sp3 << colorToChar(back.sticker(2,1)) << sp3 << std::endl;
            std::cout << sp3 << colorToChar(front.sticker(1,1)) << sp7 << colorToChar(right.sticker(1,1)) << sp3 << sp7 << sp3 << colorToChar(left.sticker(2,2)) << sp3 << colorToChar(down.sticker(1,0)) << sp5 << colorToChar(down.sticker(2,1)) << sp3 << colorToChar(back.sticker(2,0)) << std::endl;
            std::cout << colorToChar(front.sticker(2,0)) << sp5 << colorToChar(front.sticker(1,2)) << " " << colorToChar(right.sticker(1,0)) << sp5 << colorToChar(right.sticker(2,2)) << sp7 << sp3 << " " << colorToChar(down.sticker(0,0)) << sp5 << colorToChar(down.sticker(1,1)) << sp5 << colorToChar(down.sticker(2,2)) << " " << std::endl;
            std::cout << sp3 << colorToChar(front.sticker(2,1)) << sp7 << colorToChar(right.sticker(2,1)) << sp3 << sp7 << sp3 << sp4 << colorToChar(down.sticker(0,1)) << sp5 << colorToChar(down.sticker(1,2)) << sp4 << std::endl;
            std::cout << sp6 << colorToChar(front.sticker(2,2)) << " " << colorToChar(right.sticker(2,0)) << sp6 << sp7 << sp3 << sp7 << colorToChar(down.sticker(0,2)) << sp7 << std::endl;
            std::cout << "\033[0m" << std::endl;
            break;
        }
        case 1:
        {

        }
    }
}

bool RubixCube::equivalent(RubixCube &other)
{
    return this->up == other.up && this->down == other.down && this->front == other.front && this->back == other.back && this->left == other.left && this->right == other.right;
}

unsigned RubixCube::equivalence(RubixCube &other)
{
    return up.equivalence(other.up) + down.equivalence(other.down) + front.equivalence(other.front) + back.equivalence(other.back) + left.equivalence(other.left) + right.equivalence(other.right); 
}

RubixCube & RubixCube::rotateCW(RubixFace face)
{
    std::vector<RubixColor> tempRow;
    switch(face)
    {
        case UP:
            up.rotateCW();
            tempRow = left.stickers[0];
            left.stickers[0] = front.stickers[0];
            front.stickers[0] = right.stickers[0];
            right.stickers[0] = back.stickers[0];
            back.stickers[0] = tempRow; 
            break; 
        case DOWN:
            down.rotateCW();
            tempRow = left.stickers[2];
            left.stickers[2] = back.stickers[2];
            back.stickers[2] = right.stickers[2];
            right.stickers[2] = front.stickers[2];
            front.stickers[2] = tempRow; 
            break;  
        case FRONT:
            front.rotateCW();
            tempRow = {up.sticker(2,0), up.sticker(2,1), up.sticker(2,2)};
            up.stickers[2][0] = left.sticker(2,2);
            up.stickers[2][1] = left.sticker(1,2);
            up.stickers[2][2] = left.sticker(0,2);
            left.stickers[0][2] = down.sticker(0,0);
            left.stickers[1][2] = down.sticker(0,1);
            left.stickers[2][2] = down.sticker(0,2);
            down.stickers[0][0] = right.sticker(2,0);
            down.stickers[0][1] = right.sticker(1,0);
            down.stickers[0][2] = right.sticker(0,0);
            right.stickers[0][0] = tempRow[0];
            right.stickers[1][0] = tempRow[1];
            right.stickers[2][0] = tempRow[2];
            break;
        case BACK:
            back.rotateCW();
            tempRow = {up.sticker(0,2), up.sticker(0,1), up.sticker(0,0)};
            up.stickers[0][2] = right.sticker(2,2);
            up.stickers[0][1] = right.sticker(1,2);
            up.stickers[0][0] = right.sticker(0,2);
            right.stickers[2][2] = down.sticker(2,0);
            right.stickers[1][2] = down.sticker(2,1);
            right.stickers[0][2] = down.sticker(2,2);
            down.stickers[2][2] = left.sticker(2,0);
            down.stickers[2][1] = left.sticker(1,0);
            down.stickers[2][0] = left.sticker(0,0);
            left.stickers[0][0] = tempRow[0];
            left.stickers[1][0] = tempRow[1];
            left.stickers[2][0] = tempRow[2];
            break;
        case LEFT:
            left.rotateCW();            
            tempRow = {up.sticker(0,0), up.sticker(1,0), up.sticker(2,0)};
            up.stickers[0][0] = back.sticker(2,2);
            up.stickers[1][0] = back.sticker(1,2);
            up.stickers[2][0] = back.sticker(0,2);
            back.stickers[2][2] = down.sticker(0,0);
            back.stickers[1][2] = down.sticker(1,0);
            back.stickers[0][2] = down.sticker(2,0);
            down.stickers[0][0] = front.sticker(0,0);
            down.stickers[1][0] = front.sticker(1,0);
            down.stickers[2][0] = front.sticker(2,0);
            front.stickers[0][0] = tempRow[0];
            front.stickers[1][0] = tempRow[1];
            front.stickers[2][0] = tempRow[2];
            break;
        case RIGHT:
            right.rotateCW();
            tempRow = {up.sticker(2,2), up.sticker(1,2), up.sticker(0,2)};
            up.stickers[0][2] = front.sticker(0,2);
            up.stickers[1][2] = front.sticker(1,2);
            up.stickers[2][2] = front.sticker(2,2);
            front.stickers[0][2] = down.sticker(0,2);
            front.stickers[1][2] = down.sticker(1,2);
            front.stickers[2][2] = down.sticker(2,2);
            down.stickers[0][2] = back.sticker(2,0);
            down.stickers[1][2] = back.sticker(1,0);
            down.stickers[2][2] = back.sticker(0,0);
            back.stickers[0][0] = tempRow[0];
            back.stickers[1][0] = tempRow[1];
            back.stickers[2][0] = tempRow[2];
            break;
    }

    return *this;
}

RubixCube & RubixCube::rotateCCW(RubixFace face)
{
    std::vector<RubixColor> tempRow;
    switch(face)
    {
        case UP:
            up.rotateCCW();
            tempRow = right.stickers[0];
            right.stickers[0] = front.stickers[0];
            front.stickers[0] = left.stickers[0];
            left.stickers[0] = back.stickers[0]; 
            back.stickers[0] = tempRow;
            break; 
        case DOWN:
            down.rotateCCW();
            tempRow = left.stickers[2];
            left.stickers[2] = front.stickers[2];
            front.stickers[2] = right.stickers[2];
            right.stickers[2] = back.stickers[2];
            back.stickers[2] = tempRow;
            break;  
        case FRONT:
            front.rotateCCW();
            tempRow = {up.sticker(2,0), up.sticker(2,1), up.sticker(2,2)};
            up.stickers[2][0] = right.sticker(0,0);
            up.stickers[2][1] = right.sticker(1,0);
            up.stickers[2][2] = right.sticker(2,0);
            right.stickers[0][0] = down.sticker(0,2);
            right.stickers[1][0] = down.sticker(0,1);
            right.stickers[2][0] = down.sticker(0,0);
            down.stickers[0][2] = left.sticker(2,2);
            down.stickers[0][1] = left.sticker(1,2);
            down.stickers[0][0] = left.sticker(0,2);
            left.stickers[0][2] = tempRow[2];
            left.stickers[1][2] = tempRow[1];
            left.stickers[2][2] = tempRow[0];
            break;
        case BACK:
            back.rotateCCW();
            tempRow = {up.sticker(0,2), up.sticker(0,1), up.sticker(0,0)};
            up.stickers[0][2] = left.sticker(0,0);
            up.stickers[0][1] = left.sticker(1,0);
            up.stickers[0][0] = left.sticker(2,0);
            left.stickers[0][0] = down.sticker(2,0);
            left.stickers[1][0] = down.sticker(2,1);
            left.stickers[2][0] = down.sticker(2,2);
            down.stickers[2][2] = right.sticker(0,2);
            down.stickers[2][1] = right.sticker(1,2);
            down.stickers[2][0] = right.sticker(2,2);
            right.stickers[0][2] = tempRow[2];
            right.stickers[1][2] = tempRow[1];
            right.stickers[2][2] = tempRow[0];
            break;
        case LEFT:
            left.rotateCCW();            
            tempRow = {up.sticker(0,0), up.sticker(1,0), up.sticker(2,0)};
            up.stickers[0][0] = front.sticker(0,0);
            up.stickers[1][0] = front.sticker(1,0);
            up.stickers[2][0] = front.sticker(2,0);
            front.stickers[0][0] = down.sticker(0,0);
            front.stickers[1][0] = down.sticker(1,0);
            front.stickers[2][0] = down.sticker(2,0);
            down.stickers[0][0] = back.sticker(2,2);
            down.stickers[1][0] = back.sticker(1,2);
            down.stickers[2][0] = back.sticker(0,2);
            back.stickers[0][2] = tempRow[2];
            back.stickers[1][2] = tempRow[1];
            back.stickers[2][2] = tempRow[0];
            break;
        case RIGHT:
            right.rotateCCW();
            tempRow = {up.sticker(2,2), up.sticker(1,2), up.sticker(0,2)};
            up.stickers[2][2] = back.sticker(0,0);
            up.stickers[1][2] = back.sticker(1,0);
            up.stickers[0][2] = back.sticker(2,0);
            back.stickers[0][0] = down.sticker(2,2);
            back.stickers[1][0] = down.sticker(1,2);
            back.stickers[2][0] = down.sticker(0,2);
            down.stickers[0][2] = front.sticker(0,2);
            down.stickers[1][2] = front.sticker(1,2);
            down.stickers[2][2] = front.sticker(2,2);
            front.stickers[0][2] = tempRow[2];
            front.stickers[1][2] = tempRow[1];
            front.stickers[2][2] = tempRow[0];
            break;
    }

    return *this;
}

Face & RubixCube::queryFace(RubixFace face)
{
    switch (face)
    {
        case FRONT:
            return front;
            break;
        case BACK:
            return back;
            break;
        case LEFT:
            return left;
            break;
        case RIGHT:
            return right;
            break;
        case UP:
            return up;
            break;
        case DOWN:
            return down;
            break;
    }
}

// #######################
// RubixCubeSolver Class
// #######################

RubixCubeSolver::RubixCubeSolver()
: mixedCube(1000)
{}

/**
 * @brief Attempts to find a white edge piece that has not been solved.
 * It will check the Down face first and work its way up to check for 
 * incorrectly placed pieces.
 * 
 */
Edge RubixCubeSolver::findWhiteEdge()
{
    std::vector<std::pair<int, int> > edgePos = { {0,1}, {1,0}, {1,2}, {2,1} };

    // i = 1 to skip checking the up face at the beginning
    for (int i = 1; i < 6; i++)
    {
        RubixFace face = static_cast<RubixFace>(i);

        for (int i = 0; i < 4; i++)
        {
            if (mixedCube.queryFace(face).sticker(edgePos[i].first, edgePos[i].second) == WHITE)
            {
                switch (i)
                {
                    // ToDo This Face Translation should be added to functions
                    case 0: // 0,1
                        {
                            if (face == DOWN)
                                return {DOWN, FRONT};
                            else
                                return {face, UP};
                        }
                    case 1: // 1,0
                        switch (face)
                        {
                            case FRONT:
                                return {FRONT, LEFT};
                            case BACK:
                                return {BACK, RIGHT};
                            case LEFT:
                                return {LEFT, BACK};
                            case RIGHT:
                                return {RIGHT, FRONT};
                            case DOWN:
                                return {DOWN, LEFT};
                            default:
                            {
                                std::cout << "Error RubixCubeSolver::findWhiteEdge" << std::endl;
                                return {UP,UP};
                            }
                            
                            
                        }
                        break;
                    case 2: // 1,2
                        switch (face)
                        {
                            case FRONT:
                                return {FRONT, RIGHT};
                            case BACK:
                                return {BACK, LEFT};
                            case LEFT:
                                return {LEFT, FRONT};
                            case RIGHT:
                                return {RIGHT, BACK};
                            case DOWN:
                                return {DOWN, RIGHT};
                            default:
                            {
                                std::cout << "Error RubixCubeSolver::findWhiteEdge" << std::endl;
                                return {UP,UP};
                            }
                        }
                        break;
                    case 3: // 2,1
                    {
                        if (face == DOWN)
                            return {DOWN, BACK};
                        else
                            return {face, DOWN};
                    }
                }
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (mixedCube.queryFace(UP).sticker(edgePos[i].first, edgePos[i].second) == WHITE)
        {
            switch (i)
            {
                case 0: // 0,1
                {
                    if (mixedCube.queryFace(BACK).sticker(0,1) != GREEN)
                        return {UP, BACK};
                    break;
                }
                case 1: // 1,0
                {
                    if (mixedCube.queryFace(LEFT).sticker(0,1) != RED)
                        return {UP, LEFT};
                    break;
                }
                case 2: // 1,2
                {
                    if (mixedCube.queryFace(RIGHT).sticker(0,1) != ORANGE)
                        return {UP, RIGHT};
                    break;
                }
                case 3: // 2,1
                {
                    if (mixedCube.queryFace(FRONT).sticker(0,1) != BLUE)
                        return {UP, FRONT};
                    break;
                }
            }
        }
    }

    std::cout << "*Error* : location white edge pieces RubixCubeSolver::findWhiteEdge" << std::endl;
    return {UP,UP}; // Not sure what to return here since no pieces were found.
}

Edge RubixCubeSolver::findMiddleEdge()
{
    std::vector<std::pair<int, int> > edgePos = { {0,1}, {1,0}, {1,2}, {2,1} };

    // Start by looking at the bottom layer then check for
    // misplaced edge pieces
    for (int i = 0; i < 4; i++)
    {
        if (mixedCube.queryFace(DOWN).sticker(edgePos[i].first, edgePos[i].second) != YELLOW)
        {
            switch (i)
            {
                case 0: // 0,1
                {
                    if (mixedCube.queryFace(FRONT).sticker(2,1) != YELLOW)
                        return {DOWN, FRONT};
                    break;
                }
                case 1: // 1,0
                {
                    if (mixedCube.queryFace(LEFT).sticker(2,1) != YELLOW)
                        return {DOWN, LEFT};
                    break;
                }
                case 2: // 1,2
                {
                    if (mixedCube.queryFace(RIGHT).sticker(2,1) != YELLOW)
                        return {DOWN, RIGHT};
                    break;
                }
                case 3: // 2,1
                {
                    if (mixedCube.queryFace(BACK).sticker(2,1) != YELLOW)
                        return {DOWN, BACK};
                    break;
                }
            }
        }
    }

    for (int i = 2; i < 6; i++)
    {
        RubixFace face = static_cast<RubixFace>(i);
        RubixFace left; // Left of the current face
        RubixFace right; // Right of the current face

        // Refactor to use translation in other places
        switch (face)
        {
            case FRONT:
                left = LEFT;
                right = RIGHT;
                break;
            case LEFT:
                left = BACK;
                right = FRONT;
                break;
            case BACK:
                left = RIGHT;
                right = LEFT;
                break;
            case RIGHT:
                left = FRONT;
                right = BACK;
                break;
            default:
                std::cout << "\033[31m*ERROR*" << "\033[0m : face translation RubixCubeSolver::findMiddleEdge" << std::endl;
        }

        // These faces only have two faces to check
        if (mixedCube.queryFace(face).sticker(edgePos[1].first, edgePos[1].second) != YELLOW && mixedCube.queryFace(left).sticker(edgePos[2].first, edgePos[2].second) != YELLOW)
        {
            if (mixedCube.queryFace(face).sticker(edgePos[1].first, edgePos[1].second) != static_cast<RubixColor>(face) || mixedCube.queryFace(left).sticker(edgePos[2].first, edgePos[2].second) != static_cast<RubixColor>(left))
                return {face, left};
        }
        else if (mixedCube.queryFace(face).sticker(edgePos[2].first, edgePos[2].second) != YELLOW && mixedCube.queryFace(right).sticker(edgePos[1].first, edgePos[1].second) != YELLOW)
        {
            if (mixedCube.queryFace(face).sticker(edgePos[2].first, edgePos[2].second) != static_cast<RubixColor>(face) || mixedCube.queryFace(right).sticker(edgePos[1].first, edgePos[1].second) != static_cast<RubixColor>(right))
                return {face, right};
        }

    }

    std::cout << "\033[31m*ERROR*" << "\033[0m : location Edge corner pieces RubixCubeSolver::findMiddleEdge" << std::endl; 
    return {UP,UP};
}

Corner RubixCubeSolver::findWhiteCorner()
{
    std::vector<std::pair<int, int> > cornerPos = { {0,0}, {0,2}, {2,0}, {2,2} };

    // i = 1 to skip checking the up face at the beginning
    for (int i = 1; i < 6; i++)
    {
        RubixFace face = static_cast<RubixFace>(i);

        for (int i = 0; i < 4; i++)
        {
            if (mixedCube.queryFace(face).sticker(cornerPos[i].first, cornerPos[i].second) == WHITE)
            {
                switch (i)
                {
                    case 0: // 0,0
                        switch (face)
                        {
                            case FRONT:
                                return {FRONT, LEFT, UP};
                            case BACK:
                                return {BACK, RIGHT, UP};
                            case LEFT:
                                return {LEFT, BACK, UP};
                            case RIGHT:
                                return {RIGHT, FRONT, UP};
                            case DOWN:
                                return {DOWN, LEFT, FRONT};
                            default:
                                std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::findWhiteCorner Case[" << i << "]" << std::endl;
                        }
                        break;
                    case 1: // 0,2
                        switch (face)
                        {
                            case FRONT:
                                return {FRONT, RIGHT, UP};
                            case BACK:
                                return {BACK, LEFT, UP};
                            case LEFT:
                                return {LEFT, FRONT, UP};
                            case RIGHT:
                                return {RIGHT, BACK, UP};
                            case DOWN:
                                return {DOWN, RIGHT, FRONT};
                            default:
                                std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::findWhiteCorner Case[" << i << "]" << std::endl;
                        }
                        break;
                    case 2: // 2,0
                        switch (face)
                        {
                            case FRONT:
                                return {FRONT, LEFT, DOWN};
                            case BACK:
                                return {BACK, RIGHT, DOWN};
                            case LEFT:
                                return {LEFT, BACK, DOWN};
                            case RIGHT:
                                return {RIGHT, FRONT, DOWN};
                            case DOWN:
                                return {DOWN, LEFT, BACK};
                            default:
                                std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::findWhiteCorner Case[" << i << "]" << std::endl;
                        }
                        break;
                    case 3: // 2,2
                        switch (face)
                        {
                            case FRONT:
                                return {FRONT, RIGHT, DOWN};
                            case BACK:
                                return {BACK, LEFT, DOWN};
                            case LEFT:
                                return {LEFT, FRONT, DOWN};
                            case RIGHT:
                                return {RIGHT, BACK, DOWN};
                            case DOWN:
                                return {DOWN, RIGHT, BACK};
                            default:
                                std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::findWhiteCorner Case[" << i << "]" << std::endl;
                        }
                        break;
                }
            } 
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (mixedCube.queryFace(UP).sticker(cornerPos[i].first, cornerPos[i].second) == WHITE)
        {
            switch (i)
            {
                case 0: // 0,0
                {
                    if (mixedCube.queryFace(LEFT).sticker(0,0) != RED || mixedCube.queryFace(BACK).sticker(0,2) != GREEN)
                        return {UP, LEFT, BACK};
                    break;
                }
                case 1: // 0,2
                {
                    if (mixedCube.queryFace(RIGHT).sticker(0,2) != ORANGE || mixedCube.queryFace(BACK).sticker(0,0) != GREEN)
                        return {UP, RIGHT, BACK};
                    break;
                }
                case 2: // 2,0
                {
                    if (mixedCube.queryFace(LEFT).sticker(0,2) != RED || mixedCube.queryFace(FRONT).sticker(0,0) != BLUE)
                        return {UP, LEFT, FRONT};
                    break;
                }
                case 3: // 2,2
                {
                    if (mixedCube.queryFace(RIGHT).sticker(0,0) != ORANGE || mixedCube.queryFace(FRONT).sticker(0,2) != BLUE)
                        return {UP, RIGHT, FRONT};
                    break;
                }
            }
        }
    }

    std::cout << "*Error* : location white corner pieces RubixCubeSolver::findWhiteCorner" << std::endl;
    return {UP,UP,UP}; // Not sure what to return here...
}

/**
 * @brief Finds the face on which to execute the algorithm for creating the bottom cross
 * A valid found face for executing on is FRONT, BACK, LEFT, RIGHT
 * 
 * @return Face Returns FRONT if no pattern is found
 */
RubixFace RubixCubeSolver::findBottomCrossFace()
{
    if (mixedCube.queryFace(DOWN).sticker(1,0) == YELLOW)
    {
        if (mixedCube.queryFace(DOWN).sticker(0,1) == YELLOW || mixedCube.queryFace(DOWN).sticker(1,2) == YELLOW)
            return BACK;
        else if (mixedCube.queryFace(DOWN).sticker(2,1) == YELLOW)
            return RIGHT;
    }

    if (mixedCube.queryFace(DOWN).sticker(0,1) == YELLOW)
    {
        if (mixedCube.queryFace(DOWN).sticker(1,2) == YELLOW || mixedCube.queryFace(DOWN).sticker(2,1) == YELLOW)
            return LEFT;
    }

    if (mixedCube.queryFace(DOWN).sticker(1,2) == YELLOW && mixedCube.queryFace(DOWN).sticker(2,1) == YELLOW)
        return FRONT;

    // No pattern found return front face
    return FRONT;    
}

/**
 * @brief Finds the face on which to execute the bottom corners algorithm.
 * A valid found face for executing on is FRONT, BACK, LEFT, RIGHT
 * 
 * @return Face Returns UP if the face is already solved
 */
RubixFace RubixCubeSolver::findBottomCornerFace()
{
    std::vector<int8_t> cornerMatches;

    if (mixedCube.queryFace(DOWN).sticker(0,0) == YELLOW)
        cornerMatches.push_back(0);
    if (mixedCube.queryFace(DOWN).sticker(0,2) == YELLOW)
        cornerMatches.push_back(1);
    if (mixedCube.queryFace(DOWN).sticker(2,0) == YELLOW)
        cornerMatches.push_back(2);
    if (mixedCube.queryFace(DOWN).sticker(2,2) == YELLOW)
        cornerMatches.push_back(3);

    switch (cornerMatches.size())
    {
        case 0:
            return FRONT;
        case 1:
        {
            switch(cornerMatches[0])
            {
                case 0: // 0,0
                    return RIGHT;
                case 1: // 0,2
                    return BACK;
                case 2: // 2,0
                    return FRONT;
                case 3: // 2,2
                    return LEFT;
                default:
                    std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::findBottomCornerFace Case:Single Yellow corner piece" << std::endl;
                    
            }
            break;
        }
        case 2:
        {
            if (cornerMatches[0] == 0)
            {
                // 0,0 and 0,2
                if (cornerMatches[1] == 1)
                    return LEFT;
                // 0,0 and 2,2
                if (cornerMatches[1] == 3)
                    return FRONT;
                // 0,0 and 2,0
                if (cornerMatches[1] == 2)
                    return BACK;
            }
            if (cornerMatches[0] == 1)
            {
                // 0,2 and 2,2
                if (cornerMatches[1] == 3)
                    return FRONT;
                // 0,2 and 2,0
                if (cornerMatches[1] == 2)
                    return RIGHT; 
            }
            // 2,0 and 2,2
            if (cornerMatches[0] == 2 && cornerMatches[1] == 3)
                return RIGHT;
            break;
        }
        default:
            std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::findBottomCornerFace Too many edges found[" << cornerMatches.size() << "]" << std::endl;
    }

    // This should only happen in an error
    return DOWN;
}

// In the following functions pieces will either have 2 or three colors associated with it
// to denote the difference between an edge piece and a corner piece. Some functions make the
// assumption that the pieces will have a certain orientation that allow it make certain
// moves that might not move the piece to the correct lovation otherwise.

void RubixCubeSolver::solveCross()
{
    while (!isCrossSolved())
    {
        Edge whiteEdge = findWhiteEdge();

        switch (whiteEdge.first)
        {
            case DOWN:
            {
                // Match white edge with correct face
                if (mixedCube.queryFace(whiteEdge.second).sticker(2,1) == static_cast<RubixColor>(whiteEdge.second))
                    rotateCW(whiteEdge.second).rotateCW(whiteEdge.second);
                else
                {
                    switch (whiteEdge.second)
                    {
                        RubixFace matchedFace;
                        case FRONT:
                        {
                            switch (mixedCube.queryFace(whiteEdge.second).sticker(2,1))
                            {
                                case RED:
                                    rotateCCW(DOWN).rotateCW(LEFT).rotateCW(LEFT);
                                    break;
                                case GREEN:
                                    rotateCW(DOWN).rotateCW(DOWN).rotateCW(BACK).rotateCW(BACK);
                                    break;
                                case ORANGE:
                                    rotateCW(DOWN).rotateCW(RIGHT).rotateCW(RIGHT);
                                    break;
                                default:
                                    std::cout << "\033[31m*ERROR*" << "\033[0m DOWN FRONT RubixCubeSolver::solveCross" << std::endl;
                            }
                            break;
                        }
                        case BACK:
                        {
                            switch (mixedCube.queryFace(whiteEdge.second).sticker(2,1))
                            {
                                case ORANGE:
                                    rotateCCW(DOWN).rotateCW(RIGHT).rotateCW(RIGHT);
                                    break;
                                case BLUE:
                                    rotateCW(DOWN).rotateCW(DOWN).rotateCW(FRONT).rotateCW(FRONT);
                                    break;
                                case RED:
                                    rotateCW(DOWN).rotateCW(LEFT).rotateCW(LEFT);
                                    break;
                                default:
                                    std::cout << "\033[31m*ERROR*" << "\033[0m DOWN BACK RubixCubeSolver::solveCross" << std::endl;
                            }
                            break;
                        }
                        case LEFT:
                        {
                            switch (mixedCube.queryFace(whiteEdge.second).sticker(2,1))
                            {
                                case GREEN:
                                    rotateCCW(DOWN).rotateCW(BACK).rotateCW(BACK);
                                    break;
                                case ORANGE:
                                    rotateCW(DOWN).rotateCW(DOWN).rotateCW(RIGHT).rotateCW(RIGHT);
                                    break;
                                case BLUE:
                                    rotateCW(DOWN).rotateCW(FRONT).rotateCW(FRONT);
                                    break;
                                default:
                                    std::cout << "\033[31m*ERROR*" << "\033[0m DOWN LEFT RubixCubeSolver::solveCross" << std::endl;
                            }
                            break;
                        }
                        case RIGHT:
                        {
                            switch (mixedCube.queryFace(whiteEdge.second).sticker(2,1))
                            {
                                case BLUE:
                                    rotateCCW(DOWN).rotateCW(FRONT).rotateCW(FRONT);
                                    break;
                                case RED:
                                    rotateCW(DOWN).rotateCW(DOWN).rotateCW(LEFT).rotateCW(LEFT);
                                    break;
                                case GREEN:
                                    rotateCW(DOWN).rotateCW(BACK).rotateCW(BACK);
                                    break;
                                default:
                                    std::cout << "\033[31m*ERROR*" << "\033[0m DOWN RIGHT RubixCubeSolver::solveCross" << std::endl;
                            }
                            break;
                        }
                        default:
                            std::cout << "\033[31m*ERROR*" << "\033[0m DOWN case RubixCubeSolver::solveCross" << std::endl;
                    }
                }
                break;
            }
            case UP:
                rotateCW(whiteEdge.second).rotateCW(whiteEdge.second);
                break;
            case LEFT:
            {   
                switch (whiteEdge.second)
                {
                    case BACK:
                        rotateCW(BACK).rotateCW(DOWN).rotateCCW(BACK);
                        break;
                    case FRONT:
                        rotateCCW(FRONT).rotateCW(DOWN).rotateCW(FRONT);
                        break;
                    case UP:
                        rotateCW(LEFT).rotateCCW(FRONT).rotateCW(DOWN).rotateCW(FRONT).rotateCCW(LEFT);
                        break;
                    case DOWN:
                        rotateCCW(LEFT).rotateCCW(FRONT).rotateCW(DOWN).rotateCW(FRONT).rotateCW(LEFT);
                        break;
                    default:
                        std::cout << "\033[31m*ERROR*" << "\033[0m : LEFT Invalid white edge RubixCubeSolver::solveCross";
                }
                break;
            }
            case RIGHT:
            {
                switch (whiteEdge.second)
                {
                    case FRONT:
                        rotateCW(FRONT).rotateCW(DOWN).rotateCCW(FRONT);
                        break;
                    case BACK:
                        rotateCCW(BACK).rotateCW(DOWN).rotateCW(BACK);
                        break;
                    case UP:
                        rotateCW(RIGHT).rotateCCW(BACK).rotateCW(DOWN).rotateCW(BACK).rotateCCW(RIGHT);
                        break;
                    case DOWN:
                        rotateCCW(RIGHT).rotateCCW(BACK).rotateCW(DOWN).rotateCW(BACK).rotateCW(RIGHT);
                        break;
                    default:
                        std::cout << "\033[31m*ERROR*" << "\033[0m : RIGHT Invalid white edge RubixCubeSolver::solveCross";
                }
                break;
            }
            case FRONT:
            {
                switch (whiteEdge.second)
                {
                    case LEFT:
                        rotateCW(LEFT).rotateCW(DOWN).rotateCCW(LEFT);
                        break;
                    case RIGHT:
                        rotateCCW(RIGHT).rotateCW(DOWN).rotateCW(RIGHT);
                        break;
                    case UP:
                        rotateCW(FRONT).rotateCCW(RIGHT).rotateCW(DOWN).rotateCW(RIGHT).rotateCCW(FRONT);
                        break;
                    case DOWN:
                        rotateCCW(FRONT).rotateCCW(RIGHT).rotateCW(DOWN).rotateCW(RIGHT).rotateCW(FRONT);
                        break;
                    default:
                        std::cout << "\033[31m*ERROR*" << "\033[0m : FRONT Invalid white edge RubixCubeSolver::solveCross";
                }
                break;
            }
            case BACK:
            {
                switch (whiteEdge.second)
                {
                    case RIGHT:
                        rotateCW(RIGHT).rotateCW(DOWN).rotateCCW(RIGHT);
                        break;
                    case LEFT:
                        rotateCCW(LEFT).rotateCW(DOWN).rotateCW(LEFT);
                        break;
                    case UP:
                        rotateCW(BACK).rotateCCW(LEFT).rotateCW(DOWN).rotateCW(LEFT).rotateCCW(BACK);
                        break;
                    case DOWN:
                        rotateCCW(BACK).rotateCCW(LEFT).rotateCW(DOWN).rotateCW(LEFT).rotateCW(BACK);
                        break;
                    default:
                        std::cout << "\033[31m*ERROR*" << "\033[0m : BACK Invalid white edge RubixCubeSolver::solveCross";
                }
                break;
            }
        }
    }
}

/**
 * @brief Rotate a corner piece to its position on the top if the white sticker is not on yellow face (White ==  UP)
 * 
 * @param face The face where the white sticker is located.
 * @param reverse The piece can be on either side of the face. It is reversed for the right side pieces.
 */
void RubixCubeSolver::topCornerTopUp(RubixFace face, bool reverse)
{
    RubixFace movingFace; // This algorithm executes on different faces depending on where the white piece is
    switch (face)
    {
        case LEFT:
            movingFace = reverse ? FRONT : BACK;
            break;
        case BACK:
            movingFace = reverse ? LEFT : RIGHT;
            break;
        case RIGHT:
            movingFace = reverse ? BACK : FRONT;
            break;
        case FRONT:
            movingFace = reverse ? RIGHT : LEFT;
            break;
        default:
        {
            std::cout << "Invalid face for move topCornerTopUP face[" << face << "]" << " reverse[" << reverse << "]." << std::endl;
            return;
        }

    }

    if (reverse)
        rotateCCW(DOWN).rotateCCW(movingFace).rotateCW(DOWN).rotateCW(movingFace);
    else
        rotateCW(DOWN).rotateCW(movingFace).rotateCCW(DOWN).rotateCCW(movingFace);
}

/**
 * @brief This algorithm moves the white corner piece to the UP face when the white is on the DOWN face.
 * The piece should be moved so that it is between the two other sticker colors.
 * 
 * @param face The face where the white corner is on the right side and between it's two sibling colors.
 */
void RubixCubeSolver::topCornerTopDown(RubixFace face)
{
    RubixFace movingFace; // This algorithm always moves the face to the right
    switch (face)
    {
        case FRONT:
            movingFace = RIGHT;
            break;
        case RIGHT:
            movingFace = BACK;
            break;
        case BACK:
            movingFace = LEFT;
            break;
        case LEFT:
            movingFace = FRONT;
            break;
        default:
        {
            std::cout << "Invalid face for move topCornerTopUP face[" << face << "]." << std::endl;
            return;
        }
    }

    rotateCCW(movingFace).rotateCCW(DOWN).rotateCCW(DOWN).rotateCW(movingFace); // Rotate corner piece so white is not on yellow face
    rotateCW(DOWN).rotateCCW(movingFace).rotateCCW(DOWN).rotateCW(movingFace); // Basically a reverse topCornerTopUP
}

void RubixCubeSolver::solveTopCorners()
{
    while (!isTopCornersSolved())
    {
        Corner whiteCorner = findWhiteCorner();

        switch (whiteCorner[0])
        {
            case UP:
            {
                if (whiteCorner[1] == LEFT && whiteCorner[2] == BACK)
                    rotateCCW(LEFT).rotateCCW(DOWN).rotateCW(LEFT);
                else if (whiteCorner[1] == RIGHT && whiteCorner[2] == BACK)
                    rotateCW(RIGHT).rotateCW(DOWN).rotateCCW(RIGHT);
                else if (whiteCorner[1] == LEFT && whiteCorner[2] == FRONT)
                    rotateCW(LEFT).rotateCW(DOWN).rotateCCW(LEFT);
                else if (whiteCorner[1] == RIGHT && whiteCorner[2] == FRONT)
                    rotateCCW(RIGHT).rotateCCW(DOWN).rotateCW(RIGHT);
                break;
            }
            case DOWN:
            {
                bool cornerSolving = true;
                while (cornerSolving)
                {
                    switch (whiteCorner[1])
                    {
                        case LEFT:
                        {
                            switch (whiteCorner[2])
                            {
                                case BACK:
                                {
                                    if (mixedCube.queryFace(LEFT).sticker(2,0) == GREEN && mixedCube.queryFace(BACK).sticker(2,2) == RED)
                                    {
                                        topCornerTopDown(BACK);
                                        cornerSolving = false;
                                    }
                                    break;
                                }
                                case FRONT:
                                {
                                    if (mixedCube.queryFace(LEFT).sticker(2,2) == BLUE && mixedCube.queryFace(FRONT).sticker(2,0) == RED)
                                    {
                                        topCornerTopDown(LEFT);
                                        cornerSolving = false;
                                    }
                                    break;
                                }
                                default:
                                {
                                    std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::solveTopCorners Corner[" << colorToChar(static_cast<RubixColor>(whiteCorner[0])) << "\033[0m,"
                                        << colorToChar(static_cast<RubixColor>(whiteCorner[1])) << "\033[0m," << colorToChar(static_cast<RubixColor>(whiteCorner[2])) << "\033[0m]" << std::endl;
                                    break;
                                }
                            }
                            break;
                        }
                        case RIGHT:
                        {
                            switch (whiteCorner[2])
                            {
                                case BACK:
                                {
                                    if (mixedCube.queryFace(RIGHT).sticker(2,2) == GREEN && mixedCube.queryFace(BACK).sticker(2,0) == ORANGE)
                                    {
                                        topCornerTopDown(RIGHT);
                                        cornerSolving = false;
                                    }
                                    break;
                                }
                                case FRONT:
                                {
                                    if (mixedCube.queryFace(RIGHT).sticker(2,0) == BLUE && mixedCube.queryFace(FRONT).sticker(2,2) == ORANGE)
                                    {
                                        topCornerTopDown(FRONT);
                                        cornerSolving = false;
                                    }
                                    break;
                                }
                                default:
                                {
                                    std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::solveTopCorners Corner[" << colorToChar(static_cast<RubixColor>(whiteCorner[0])) << "\033[0m,"
                                        << colorToChar(static_cast<RubixColor>(whiteCorner[1])) << "\033[0m," << colorToChar(static_cast<RubixColor>(whiteCorner[2])) << "\033[0m]" << std::endl;
                                    break;
                                }
                            }
                            break;
                        }
                        case FRONT:
                        {
                            switch (whiteCorner[2])
                            {
                                case RIGHT:
                                {
                                    if (mixedCube.queryFace(RIGHT).sticker(2,0) == BLUE && mixedCube.queryFace(FRONT).sticker(2,2) == ORANGE)
                                    {
                                        topCornerTopDown(FRONT);
                                        cornerSolving = false;
                                    }
                                    break;
                                }
                                case LEFT:
                                {
                                    if (mixedCube.queryFace(LEFT).sticker(2,2) == BLUE && mixedCube.queryFace(FRONT).sticker(2,0) == RED)
                                    {
                                        topCornerTopDown(LEFT);
                                        cornerSolving = false;
                                    }
                                    break;
                                }
                                default:
                                {
                                    std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::solveTopCorners Corner[" << colorToChar(static_cast<RubixColor>(whiteCorner[0])) << "\033[0m,"
                                        << colorToChar(static_cast<RubixColor>(whiteCorner[1])) << "\033[0m," << colorToChar(static_cast<RubixColor>(whiteCorner[2])) << "\033[0m]" << std::endl;
                                    break;
                                }
                            }
                            break;
                        }
                        case BACK:
                        {
                            switch (whiteCorner[2])
                            {
                                case LEFT:
                                {
                                    if (mixedCube.queryFace(LEFT).sticker(2,0) == GREEN && mixedCube.queryFace(BACK).sticker(2,2) == RED)
                                    {
                                        topCornerTopDown(BACK);
                                        cornerSolving = false;
                                    }
                                    break;
                                }
                                case RIGHT:
                                {
                                    if (mixedCube.queryFace(RIGHT).sticker(2,2) == GREEN && mixedCube.queryFace(BACK).sticker(2,0) == ORANGE)
                                    {
                                        topCornerTopDown(RIGHT);
                                        cornerSolving = false;
                                    }
                                    break;
                                }
                                default:
                                {
                                    std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::solveTopCorners Corner[" << colorToChar(static_cast<RubixColor>(whiteCorner[0])) << "\033[0m,"
                                        << colorToChar(static_cast<RubixColor>(whiteCorner[1])) << "\033[0m," << colorToChar(static_cast<RubixColor>(whiteCorner[2])) << "\033[0m]" << std::endl;
                                    break;
                                }
                            }
                            break;
                        }
                        default:
                        {
                            std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::solveTopCorners Corner[" << colorToChar(static_cast<RubixColor>(whiteCorner[0])) << "\033[0m,"
                                << colorToChar(static_cast<RubixColor>(whiteCorner[1])) << "\033[0m," << colorToChar(static_cast<RubixColor>(whiteCorner[2])) << "\033[0m]" << std::endl;
                            break;
                        }
                    }

                    if (cornerSolving)
                        rotateWhiteCornerOnBottom(whiteCorner);
                }
                break;
            }
            case FRONT:
            {
                if (whiteCorner[1] == LEFT)
                    rotateCW(LEFT).rotateCW(DOWN).rotateCW(DOWN).rotateCCW(LEFT);
                else
                    rotateCCW(RIGHT).rotateCCW(DOWN).rotateCCW(DOWN).rotateCW(RIGHT);
                break;
            }
            case BACK:
            {
                if (whiteCorner[1] == LEFT)
                    rotateCCW(LEFT).rotateCCW(DOWN).rotateCCW(DOWN).rotateCW(LEFT);
                else
                    rotateCW(RIGHT).rotateCCW(DOWN).rotateCCW(DOWN).rotateCCW(RIGHT);
                break;
            }
            case LEFT:
            {
                if (whiteCorner[1] == BACK)
                    rotateCW(BACK).rotateCW(DOWN).rotateCW(DOWN).rotateCCW(BACK);
                else
                    rotateCCW(FRONT).rotateCCW(DOWN).rotateCCW(DOWN).rotateCW(FRONT);
                break;
            }
            case RIGHT:
            {
                if (whiteCorner[1] == FRONT)
                    rotateCW(FRONT).rotateCW(DOWN).rotateCW(DOWN).rotateCCW(FRONT);
                else
                    rotateCCW(BACK).rotateCCW(DOWN).rotateCCW(DOWN).rotateCW(BACK);
                break;
            }
        }
    }
}

void RubixCubeSolver::solveMiddleLayer()
{
    while (!isSecondLayerSolved())
    {
        Edge edge = findMiddleEdge();

        switch (edge.first)
        {
            case DOWN:
            {
                bool edgeSolving = true;
                while (edgeSolving)
                {
                    if (mixedCube.queryFace(edge.second).sticker(2,1) == static_cast<RubixColor>(edge.second))
                    {
                        switch (edge.second)
                        {
                            case LEFT:
                            {
                                if (mixedCube.queryFace(DOWN).sticker(1,0) == BLUE)
                                {
                                    middleEdge(LEFT, true); // Move to the right
                                    edgeSolving = false;
                                }
                                else
                                {
                                    middleEdge(LEFT);
                                    edgeSolving = false;
                                }
                                break;
                            }
                            case RIGHT:
                            {
                                if (mixedCube.queryFace(DOWN).sticker(1,2) == GREEN)
                                {
                                    middleEdge(RIGHT, true); // Move to the right
                                    edgeSolving = false;
                                }
                                else
                                {
                                    middleEdge(RIGHT);
                                    edgeSolving = false;
                                }
                                break;
                            }
                            case FRONT:
                            {
                                if (mixedCube.queryFace(DOWN).sticker(0,1) == ORANGE)
                                {
                                    middleEdge(FRONT, true); // Move to the right
                                    edgeSolving = false;
                                }
                                else
                                {
                                    middleEdge(FRONT);
                                    edgeSolving = false;
                                }
                                break;
                            }
                            case BACK:
                            {
                                if (mixedCube.queryFace(DOWN).sticker(2,1) == RED)
                                {
                                    middleEdge(BACK, true); // Move to the right
                                    edgeSolving = false;
                                }
                                else
                                {
                                    middleEdge(BACK);
                                    edgeSolving = false;
                                }
                                break;
                            }
                            default:
                            {
                                std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::solveMiddleEdge Edge[" << colorToChar(static_cast<RubixColor>(edge.first)) << "\033[0m,"
                                    << colorToChar(static_cast<RubixColor>(edge.second)) << "\033[0m]" << std::endl;
                                break;
                            }
                        }
                    }

                    if (edgeSolving)
                        rotateMiddleEdgeOnBottom(edge);
                }
                break;
            }
            case FRONT:
                if (edge.second == LEFT)
                    middleEdge(FRONT); // Move incorrect piece out of position
                else
                    middleEdge(FRONT, true);
                break;
            case LEFT:
                if (edge.second == BACK)
                    middleEdge(LEFT);
                else
                    middleEdge(LEFT, true);
                break;
            case RIGHT:
                if (edge.second == FRONT)
                    middleEdge(RIGHT);
                else
                    middleEdge(RIGHT, true);
                break;
            case BACK:
                if (edge.second == RIGHT)
                    middleEdge(BACK);
                else
                    middleEdge(BACK, true);
                break;
            default:
               std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::solveMiddleLayer" << std::endl; 
        }
    }
}

void RubixCubeSolver::solveBottomCross()
{
    while (!isBottomCrossSolved())
    {
        RubixFace face = findBottomCrossFace();

        bottomCross(face);
    }
}

void RubixCubeSolver::solveBottomFace()
{
    while (!isBottomSolved())
    {
        RubixFace face = findBottomCornerFace();

        bottomCorners(face);
    }
}

void RubixCubeSolver::solveThirdLayer()
{
    while (!isSolved())
    {
        bool cornersMatch = isBottomCornerMatched();
        if (cornersMatch)
        {
            int offset = checkLayerOffset();
            if (offset > 0)
            {
                while (offset)
                {
                    // NB this skips a possible shortcut when having to do three CW rotations
                    rotateCW(DOWN);
                    offset--;
                }
            }
            else
            {
                // Corners match but middle pieces are misplaced
                RubixFace face = checkPartialLayerOffset();

                switch (face)
                {
                    case FRONT:
                        bottomSideCenters(BACK);
                        break;
                    case LEFT:
                        bottomSideCenters(RIGHT);
                        break;
                    case RIGHT:
                        bottomSideCenters(LEFT);
                        break;
                    case BACK:
                        bottomSideCenters(FRONT);
                        break;
                    default:
                        std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::solveThirdLayer Corners match" << std::endl;
                }
            }
        }
        else
        {
            // Corners don't match
            RubixFace face = checkPartialLayerOffset();

            switch (face)
            {
                case FRONT:
                    bottomSideCorners(BACK);
                    break;
                case LEFT:
                    bottomSideCorners(RIGHT);
                    break;
                case RIGHT:
                    bottomSideCorners(LEFT);
                    break;
                case BACK:
                    bottomSideCorners(FRONT);
                    break;
                default:
                    std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::solveMiddleLayer Corners don't match" << std::endl;
            }
        }
    }
}

/**
 * @brief Moves the edge piece on the bottom layer to the middle layer. 
 * 
 * @param face The face where the edge piece is located
 * @param reverse By default moves the piece to the left.
 */
void RubixCubeSolver::middleEdge(RubixFace face, bool reverse)
{
    RubixFace movingFace; // This is the primary moving face. The face passed in will move as well

    switch (face)
    {
        case FRONT:
            movingFace = reverse ? RIGHT : LEFT;
            break;
        case LEFT:
            movingFace = reverse ? FRONT : BACK;
            break;
        case RIGHT:
            movingFace = reverse ? BACK : FRONT;
            break;
        case BACK:
            movingFace = reverse ? LEFT : RIGHT;
            break;
        default:
            std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::middleEdge" << std::endl;
    }

    if (reverse)
    {
        rotateCCW(DOWN).rotateCCW(movingFace).rotateCCW(DOWN).rotateCW(movingFace).rotateCW(DOWN).rotateCW(face).rotateCW(DOWN).rotateCCW(face);
    }
    else
    {
        // Default case
        rotateCW(DOWN).rotateCW(movingFace).rotateCW(DOWN).rotateCCW(movingFace).rotateCCW(DOWN).rotateCCW(face).rotateCCW(DOWN).rotateCW(face);
    }
}

void RubixCubeSolver::bottomCross(RubixFace face)
{
    // face CW, DOWN CW, right of face CW, DOWN CCW, right of face CCW, face CCW
    RubixFace rightFace; // Right of the face passed in
    switch (face)
    {
        case FRONT:
            rightFace = LEFT;
            break;
        case LEFT:
            rightFace = BACK;
            break;
        case BACK:
            rightFace = RIGHT;
            break;
        case RIGHT:
            rightFace = FRONT;
            break;
        default:
        {
            std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::bottomCross face[ " << colorToChar(static_cast<RubixColor>(face)) << "]" << std::endl;
            return;
        }
    }

    rotateCW(face).rotateCW(DOWN).rotateCW(rightFace).rotateCCW(DOWN).rotateCCW(rightFace).rotateCCW(face);
}

void RubixCubeSolver::bottomCorners(RubixFace face)
{
    RubixFace rightFace; // Right of the current face

    // NOT INTUITIVE DO NOT TOUCH
    switch (face)
    {
        case FRONT:
            rightFace = RIGHT;
            break;
        case LEFT:
            rightFace = FRONT;
            break;
        case BACK:
            rightFace = LEFT;
            break;
        case RIGHT:
            rightFace = BACK;
            break;
        default:
            std::cout << "\033[31m*ERROR*" << "\033[0m : face translation RubixCubeSolver::findMiddleEdge" << std::endl;
    }

    rotateCW(rightFace).rotateCW(DOWN).rotateCCW(rightFace).rotateCW(DOWN).rotateCW(rightFace).rotateCW(DOWN).rotateCW(DOWN).rotateCCW(rightFace);
}

void RubixCubeSolver::bottomSideCorners(RubixFace face)
{
    RubixFace rightFace;
    RubixFace backFace;

    switch (face)
    {
        case FRONT:
            rightFace = LEFT;
            backFace = BACK;
            break;
        case LEFT:
            rightFace = BACK;
            backFace = RIGHT;
            break;
        case BACK:
            rightFace = RIGHT;
            backFace = FRONT;
            break;
        case RIGHT:
            rightFace = FRONT;
            backFace = LEFT;
            break;
        default:
        {
            std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::bottomSideCorners" << std::endl;
            return;
        }
    }

    rotateCCW(rightFace).rotateCW(face).rotateCCW(rightFace).rotateCW(backFace).rotateCW(backFace);
    rotateCW(rightFace).rotateCCW(face).rotateCCW(rightFace).rotateCW(backFace).rotateCW(backFace).rotateCW(rightFace).rotateCW(rightFace);
}

void RubixCubeSolver::bottomSideCenters(RubixFace face)
{
    RubixFace rightFace;

    switch (face)
    {
        case FRONT:
            rightFace = LEFT;
            break;
        case LEFT:
            rightFace = BACK;
            break;
        case BACK:
            rightFace = RIGHT;
            break;
        case RIGHT:
            rightFace = FRONT;
            break;
        default:
        {
            std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::bottomSideCenters" << std::endl;
            return;
        }
    }

    rotateCW(rightFace).rotateCW(rightFace).rotateCW(DOWN).rotateCW(rightFace).rotateCW(DOWN);
    rotateCCW(rightFace).rotateCCW(DOWN).rotateCCW(rightFace).rotateCCW(DOWN).rotateCCW(rightFace).rotateCW(DOWN).rotateCCW(rightFace);
}

void RubixCubeSolver::rotateWhiteCornerOnBottom(Corner & corner)
{
    rotateCW(DOWN);
    // Face translation could be improved
    // Update faces
    for (int i = 1; i <=2; i++)
        switch (corner[i])
        {
            case FRONT:
                corner[i] = RIGHT;
                break;
            case RIGHT:
                corner[i] = BACK;
                break;
            case BACK:
                corner[i] = LEFT;
                break;
            case LEFT:
                corner[i] = FRONT;
                break;
            default:
                std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::rotateWhiteCornerOnBottom" << std::endl;
        }
}

void RubixCubeSolver::rotateMiddleEdgeOnBottom(Edge & edge)
{
    rotateCW(DOWN);
    // Face translation could be improved
    // Update faces
    switch (edge.second)
    {
        case FRONT:
            edge.second = RIGHT;
            break;
        case RIGHT:
            edge.second = BACK;
            break;
        case BACK:
            edge.second = LEFT;
            break;
        case LEFT:
            edge.second = FRONT;
            break;
        default:
            std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::rotateWhiteCornerOnBottom" << std::endl;
    }
}

bool RubixCubeSolver::checkLayer(int row)
{
    if (mixedCube.queryFace(FRONT).sticker(row,0) != BLUE || mixedCube.queryFace(FRONT).sticker(row,1) != BLUE || mixedCube.queryFace(FRONT).sticker(row,2) != BLUE)
        return false;
    if (mixedCube.queryFace(LEFT).sticker(row,0) != RED || mixedCube.queryFace(LEFT).sticker(row,1) != RED || mixedCube.queryFace(LEFT).sticker(row,2) != RED)
        return false;
    if (mixedCube.queryFace(BACK).sticker(row,0) != GREEN || mixedCube.queryFace(BACK).sticker(row,1) != GREEN || mixedCube.queryFace(BACK).sticker(row,2) != GREEN)
        return false;
    if (mixedCube.queryFace(RIGHT).sticker(row,0) != ORANGE || mixedCube.queryFace(RIGHT).sticker(row,1) != ORANGE || mixedCube.queryFace(RIGHT).sticker(row,2) != ORANGE)
        return false;
    return true;
}

/**
 * @brief This function checks if the bottom layer is solved but rotated
 *
 * @return int If the Layer is not solved -1 is returned else the number of CW rotations to solve each face
 */
int RubixCubeSolver::checkLayerOffset()
{
    // Check that the final layer all matches
    if (mixedCube.queryFace(FRONT).sticker(2,0) != mixedCube.queryFace(FRONT).sticker(2,1) && mixedCube.queryFace(FRONT).sticker(2,1) != mixedCube.queryFace(FRONT).sticker(2,2))
        return -1;
    if (mixedCube.queryFace(LEFT).sticker(2,0) != mixedCube.queryFace(LEFT).sticker(2,1) && mixedCube.queryFace(LEFT).sticker(2,1) != mixedCube.queryFace(LEFT).sticker(2,2))
        return -1;
    if (mixedCube.queryFace(BACK).sticker(2,0) != mixedCube.queryFace(BACK).sticker(2,1) && mixedCube.queryFace(BACK).sticker(2,1) != mixedCube.queryFace(BACK).sticker(2,2))
        return -1;
    if (mixedCube.queryFace(RIGHT).sticker(2,0) != mixedCube.queryFace(RIGHT).sticker(2,1) && mixedCube.queryFace(RIGHT).sticker(2,1) != mixedCube.queryFace(RIGHT).sticker(2,2))
        return -1;

    switch (mixedCube.queryFace(FRONT).sticker(2,0))
    {
        case ORANGE:
            return 1;
        case GREEN:
            return 2;
        case RED:
            return 3;
        default:
        {
            std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::checkLayerOffset" << std::endl;
            return -2; // Shouldn't get here... Maybe cube is solved?
        }
    }
}

/**
 * @brief Checks for a partial match where two corners on a single face match
 *
 * @return RubixFace the face where the matched corners are
 */
RubixFace RubixCubeSolver::checkPartialLayerOffset()
{
    RubixFace match = UP;

    // Search for a face with three pieces matching
    for (int i = 2; i < 6; i++)
    {
        RubixFace face =  static_cast<RubixFace>(i);
        Face currentFace = mixedCube.queryFace(face);

        if (currentFace.sticker(2,0) == currentFace.sticker(2,1) && currentFace.sticker(2,1) == currentFace.sticker(2,2))
        {
            match = face;
            break;
        }
    }

    // Search for a face with two pieces matching
    if (match == UP)
    {
        for (int i = 2; i < 6; i++)
        {
            RubixFace face =  static_cast<RubixFace>(i);
            Face currentFace = mixedCube.queryFace(face);

            if (currentFace.sticker(2,0) == currentFace.sticker(2,2))
            {
                match = face;
                break;
            }
        }
    }

    if (match == UP)
    {
        // No match found so pretend its on FRONT
        return FRONT;
    }

    // Based on the color of those pieces and the face rotate to match them
    RubixColor color = mixedCube.queryFace(match).sticker(2,0);

    switch (color)
    {
        case ORANGE:
        {
            switch (match)
            {
                case FRONT:
                    rotateCW(DOWN);
                    break;
                case LEFT:
                    rotateCW(DOWN).rotateCW(DOWN);
                    break;
                case BACK:
                    rotateCCW(DOWN);
                    break;
                case RIGHT:
                    break;
                default:
                    std::cout << "\033[31m*ERROR*" << "\033[0m rubixCubeSolver::checkPartialLayerOffset color of corner[" << colorToChar(color) << "\033[31m}" << std::endl;
            }
            break;
        }
        case GREEN:
        {
            switch (match)
            {
                case FRONT:
                    rotateCW(DOWN).rotateCW(DOWN);
                    break;
                case LEFT:
                    rotateCCW(DOWN);
                    break;
                case BACK:
                    break;
                case RIGHT:
                    rotateCW(DOWN);
                    break;
                default:
                    std::cout << "\033[31m*ERROR*" << "\033[0m rubixCubeSolver::checkPartialLayerOffset color of corner[" << colorToChar(color) << "\033[31m}" << std::endl;
            }
            break;
        }
        case RED:
        {
            switch (match)
            {
                case FRONT:
                    rotateCCW(DOWN);
                    break;
                case LEFT:
                    break;
                case BACK:
                    rotateCW(DOWN);
                    break;
                case RIGHT:
                    rotateCW(DOWN).rotateCW(DOWN);
                    break;
                default:
                    std::cout << "\033[31m*ERROR*" << "\033[0m rubixCubeSolver::checkPartialLayerOffset color of corner[" << colorToChar(color) << "\033[31m}" << std::endl;
            }
            break;
        }
        case BLUE:
        {
            switch (match)
            {
                case FRONT:
                    break;
                case LEFT:
                    rotateCW(DOWN);
                    break;
                case BACK:
                    rotateCW(DOWN).rotateCW(DOWN);
                    break;
                case RIGHT:
                    rotateCCW(DOWN);
                    break;
                default:
                    std::cout << "\033[31m*ERROR*" << "\033[0m rubixCubeSolver::checkPartialLayerOffset color of corner[" << colorToChar(color) << "\033[31m}" << std::endl;
            }
            break;
        }
        default:
        {
            std::cout << "\033[31m*ERROR*" << "\033[0m RubixCubeSolver::checkLayerOffset" << std::endl;
            return UP; // Shouldn't get here... Maybe cube is solved?
        }
    }

    return static_cast<RubixFace>(color);
}

bool RubixCubeSolver::isBottomCornerMatched()
{
    // Check that the final layer all matches
    if (mixedCube.queryFace(FRONT).sticker(2,0) != mixedCube.queryFace(FRONT).sticker(2,2))
        return false;
    if (mixedCube.queryFace(LEFT).sticker(2,0) != mixedCube.queryFace(LEFT).sticker(2,2))
        return false;
    if (mixedCube.queryFace(BACK).sticker(2,0) != mixedCube.queryFace(BACK).sticker(2,2))
        return false;
    if (mixedCube.queryFace(RIGHT).sticker(2,0) != mixedCube.queryFace(RIGHT).sticker(2,2))
        return false;

    return true;
}

bool RubixCubeSolver::isCrossSolved()
{
    if (mixedCube.queryFace(UP).sticker(0,1) != WHITE || mixedCube.queryFace(UP).sticker(1,0) != WHITE || mixedCube.queryFace(UP).sticker(1,2) != WHITE || mixedCube.queryFace(UP).sticker(2,1) != WHITE)
        return false;
    return mixedCube.queryFace(FRONT).sticker(0,1) == BLUE && mixedCube.queryFace(LEFT).sticker(0,1) == RED && mixedCube.queryFace(RIGHT).sticker(0,1) == ORANGE && mixedCube.queryFace(BACK).sticker(0,1) == GREEN;
}

bool RubixCubeSolver::isTopCornersSolved()
{
    if (!(mixedCube.queryFace(UP).sticker(0,0) == WHITE && mixedCube.queryFace(UP).sticker(0,2) == WHITE && mixedCube.queryFace(UP).sticker(2,0) == WHITE && mixedCube.queryFace(UP).sticker(2,2) == WHITE))
        return false;
    return mixedCube.queryFace(FRONT).sticker(0,0) == BLUE && mixedCube.queryFace(FRONT).sticker(0,2) == BLUE && mixedCube.queryFace(LEFT).sticker(0,0) == RED && mixedCube.queryFace(LEFT).sticker(0,2) == RED &&
        mixedCube.queryFace(RIGHT).sticker(0,0) == ORANGE && mixedCube.queryFace(RIGHT).sticker(0,2) == ORANGE && mixedCube.queryFace(BACK).sticker(0,0) == GREEN && mixedCube.queryFace(BACK).sticker(0,2) == GREEN;
}

bool RubixCubeSolver::isUpSolved()
{
    if (!isCrossSolved())
        return false;
    return isTopCornersSolved();
}

bool RubixCubeSolver::isFirstLayerSolved()
{
    return checkLayer(0);
}

bool RubixCubeSolver::isSecondLayerSolved()
{
    return checkLayer(1);
}

bool RubixCubeSolver::isBottomCrossSolved()
{
    return mixedCube.queryFace(DOWN).sticker(1,0) == YELLOW && mixedCube.queryFace(DOWN).sticker(0,1) == YELLOW && mixedCube.queryFace(DOWN).sticker(2,1) == YELLOW && mixedCube.queryFace(DOWN).sticker(1,2) == YELLOW;
}

bool RubixCubeSolver::isBottomSolved()
{
    if (!isBottomCrossSolved())
        return false;
    return mixedCube.queryFace(DOWN).sticker(0,0) == YELLOW && mixedCube.queryFace(DOWN).sticker(0,2) == YELLOW && mixedCube.queryFace(DOWN).sticker(2,0) == YELLOW && mixedCube.queryFace(DOWN).sticker(2,2) == YELLOW;
}

bool RubixCubeSolver::isthirdLayerSolved()
{
    return checkLayer(2);
}

bool RubixCubeSolver::isSolved()
{
    if (!isUpSolved())
        return false;
    if (!isFirstLayerSolved())
        return false;
    if (!isSecondLayerSolved())
        return false;
    if (!isBottomSolved())
        return false;
    if (!isthirdLayerSolved())
        return false;
    
    return true;
}

MoveSet RubixCubeSolver::solveCube(RubixCube & _mixedCube)
{
    mixedCube = _mixedCube;

    if (solvedCube.equivalent(mixedCube))
    {
        std::cout << "Challenge cube is already solved!" << std::endl;
        return moveSet;
    }

#if !_DEBUG
    mixedCube.print();
#endif

    std::time_t startTime = time(0);
    solveCross();
    solveTopCorners();
    solveMiddleLayer();
    solveBottomCross();
    solveBottomFace();
    solveThirdLayer();
    int elapsedTime = time(0) - startTime;
    mixedCube.print();
    
    std::cout << "Solved cube with " << moves << " moves in " << elapsedTime % 60 << " seconds." << std::endl << std::endl;

    return moveSet;
}

RubixCubeSolver & RubixCubeSolver::rotateCW(RubixFace face)
{
#if _DEBUG
    mixedCube.print();
    std::cout << "Rotating " << colorToChar(static_cast<RubixColor>(face)) << "\033[0m Clockwise..." << std::endl << std::endl;
#endif

    moveSet.emplace_back(face, moves, "CW");
    mixedCube.rotateCW(face);
    moves++;
    return *this;
}

RubixCubeSolver & RubixCubeSolver::rotateCCW(RubixFace face)
{   
#if _DEBUG
    mixedCube.print();
    std::cout << "Rotating " << colorToChar(static_cast<RubixColor>(face)) << "\033[0m Counter Clockwise..." << std::endl << std::endl;
#endif

    moveSet.emplace_back(face, moves, "CCW");
    mixedCube.rotateCCW(face);
    moves++;
    return *this;
}

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

void gatherStats(int moves = 100000)
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
        MoveSet moveSet = solver.solveCube(randomCube);

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
    std::cout << "The average Move set size was " << totalMoves / i << " moves." << std::endl;
    std::cout << "Finished in " << (int)(elapsedTime / 60) << " minutes " << elapsedTime % 60 << " seconds." << std::endl;
}

int main(int argc, char *argv[])
{
    // This project uses rand to create psuedo random moves for generating valid cubes
    srand(time(0));
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
