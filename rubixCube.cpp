#include "rubixCube.hpp"
#include <iostream>
#include <cstdlib>

// #######################
// Face Class
// #######################

#define _DEBUG 2

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
    for (int n = 0; n <= moves; ++n)
    {
        if (rand() % 2)
            rotateCW(static_cast<RubixFace>(rand() % 6));
        else
            rotateCCW(static_cast<RubixFace>(rand() % 6));
    }
}

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
            return "\033[X";
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
            std::cout << sp7 << colorToChar(up.sticker(0,0)) << sp7 << sp7 << sp3 << sp6 << colorToChar(left.sticker(0,0)) << " " << colorToChar(back.sticker(0,2)) << sp6 << std::endl;
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

// #######################
// RubixCubeSolver Class
// #######################

RubixCubeSolver::RubixCubeSolver()
: mixedCube(1000)
{}

// In the following functions pieces will either have 2 or three colors associated with it
// to denote the difference between an edge piece and a corner piece. Some functions make the
// assumption that the pieces will have a certain orientation that allow it make certain
// moves that might not move the piece to the correct lovation otherwise.

/**
 * @brief Rotate a corner piece to its position on the top if the white sticker is not on yellow face (White ==  UP)
 * 
 * @param face The face where the white sticker is located.
 * @param reverse The piece can be on either side of the face. It is reversed for the right side pieces.
 */
void RubixCubeSolver::topCornerTopUp(RubixFace face, bool reverse)
{
    RubixFace movingFace; // This algorithm executes on two faces
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
        mixedCube.rotateCCW(DOWN).rotateCCW(movingFace).rotateCW(DOWN).rotateCW(movingFace);
    else
        mixedCube.rotateCW(DOWN).rotateCW(movingFace).rotateCCW(DOWN).rotateCCW(movingFace);
}

void topCornerTopDown(RubixFace face, bool reverse)
{

}

void middleEdge(RubixFace face, bool reverse)
{

}

void bottomCross(RubixFace face, bool reverse)
{

}

void bottomCorners(RubixFace face, bool reverse)
{

}

void bottomSides(RubixFace face, bool reverse)
{

}

void bottomSideCenters(RubixFace face, bool reverse)
{

}

bool RubixCubeSolver::checkLayer(int row)
{
    if (mixedCube.front.sticker(row,0) != BLUE || mixedCube.front.sticker(row,1) != BLUE || mixedCube.front.sticker(row,2) != BLUE)
        return false;
    if (mixedCube.left.sticker(row,0) != RED || mixedCube.left.sticker(row,1) != RED || mixedCube.left.sticker(row,2) != RED)
        return false;
    if (mixedCube.back.sticker(row,0) != GREEN || mixedCube.back.sticker(row,1) != GREEN || mixedCube.back.sticker(row,2) != GREEN)
        return false;
    if (mixedCube.right.sticker(row,0) != ORANGE || mixedCube.right.sticker(row,1) != ORANGE || mixedCube.right.sticker(row,2) != ORANGE)
        return false;
    return true;
}

bool RubixCubeSolver::isCrossSolved()
{
    return mixedCube.up.sticker(0,1) == WHITE && mixedCube.up.sticker(1,0) == WHITE && mixedCube.up.sticker(1,2) == WHITE && mixedCube.up.sticker(2,1) == WHITE;
}

bool RubixCubeSolver::isUpSolved()
{
    if (!isCrossSolved())
        return false;
    return mixedCube.up.sticker(0,0) == WHITE && mixedCube.up.sticker(0,2) == WHITE && mixedCube.up.sticker(2,0) == WHITE && mixedCube.up.sticker(2,2) == WHITE;
}

bool RubixCubeSolver::isFirstLayerSolved()
{
    if (!isUpSolved())
        return false;
    return checkLayer(0);
}

bool RubixCubeSolver::isSecondLayerSolved()
{
    if (!isFirstLayerSolved())
        return false;
    return checkLayer(1);
}

bool RubixCubeSolver::isBottomCrossSolved()
{
    return mixedCube.down.sticker(1,0) == YELLOW && mixedCube.down.sticker(0,1) == YELLOW && mixedCube.down.sticker(2,1) == YELLOW && mixedCube.down.sticker(1,2) == YELLOW;
}

bool RubixCubeSolver::isBottomSolved()
{
    if (!isBottomCrossSolved())
        return false;
    return mixedCube.down.sticker(0,0) == YELLOW && mixedCube.down.sticker(0,2) == YELLOW && mixedCube.down.sticker(2,0) == YELLOW && mixedCube.down.sticker(2,2) == YELLOW;
}

bool RubixCubeSolver::isthirdLayerSolved()
{
    if (!isBottomSolved())
        return false;
    return checkLayer(2);
}

void RubixCubeSolver::solveCube(RubixCube & _mixedCube)
{
    if (solvedCube.equivalent(mixedCube))
    {
        std::cout << "Challenge cube is already solved!" << std::endl;
        return;
    }

    std::time_t startTime = time(0);
    uint64_t i = 0;
    // while (!solvedCube.equivalent(mixedCube))
    {
        mixedCube.print();
        topCornerTopUp(FRONT);
        mixedCube.print();
        topCornerTopUp(BACK);
        mixedCube.print();
        topCornerTopUp(LEFT);
        mixedCube.print();
        topCornerTopUp(RIGHT);
        mixedCube.print();
        topCornerTopUp(FRONT,true);
        mixedCube.print();
        topCornerTopUp(BACK,true);
        mixedCube.print();
        topCornerTopUp(LEFT,true);
        mixedCube.print();
        topCornerTopUp(RIGHT,true);
        mixedCube.print();

#if _DEBUG
        if (solvedCube.equivalence(mixedCube) > 35)
            mixedCube.print();
        switch(_DEBUG)
        {
            case 1:
                if (isCrossSolved())
                {
                    std::cout << "The Top Cross is solved!" << std::endl;
                    mixedCube.print();
                }
            case 2:
                if (isFirstLayerSolved())
                {
                    std::cout << "The First Layer is solved!" << std::endl;
                    mixedCube.print();
                }
            case 3:
                if (isSecondLayerSolved())
                {
                    std::cout << "The Second Layer is solved!" << std::endl;
                    mixedCube.print();
                }
            case 4:
                if (isthirdLayerSolved())
                {
                    std::cout << "The Third Layer is solved!" << std::endl;
                    mixedCube.print();
                }
        }
#endif
        i++;
    }

    int elapsedTime = time(0) - startTime;
    std::cout << "Solved cube with monkey and a typewriter: " << i << " moves in ";
    std::cout << (int)(elapsedTime / 60) << " minutes " << elapsedTime % 60 << " seconds." << std::endl;
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

void dummySolver()
{
    RubixCube solvedCube;
    RubixCube randomCube(100);
    std::time_t startTime = time(0);
    uint64_t i = 0;
    while (!solvedCube.equivalent(randomCube))
    {
        if (rand() % 2)
            randomCube.rotateCW(static_cast<RubixFace>(rand() % 6));
        else
            randomCube.rotateCCW(static_cast<RubixFace>(rand() % 6));

        if (solvedCube.equivalence(randomCube) > 35)
            randomCube.print();
#if _DEBUG
        if (i % 40000000 == 0)
            randomCube.print();
#endif
        i++;
    }

    int elapsedTime = time(0) - startTime;
    std::cout << "Solved cube with monkey and a typewriter: " << i << " moves in ";
    std::cout << (int)(elapsedTime / 60) << " minutes " << elapsedTime % 60 << " seconds." << std::endl;
}

int main()
{
    // This project uses rand to create psuedo random moves for generating valid cubes
    srand(time(0));

    testRotations();

    RubixCube cube2(250);
    RubixCubeSolver solver;
    solver.solveCube(cube2);
}
