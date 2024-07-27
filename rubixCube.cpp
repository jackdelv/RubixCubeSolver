#include "rubixCube.hpp"
#include <iostream>
#include <cstdlib>

// #######################
// Face Class
// #######################

#define _DEBUG 1

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
        this->rotateCW(static_cast<RubixFace>(rand() % 6));
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

void RubixCube::print(int spacing = 0)
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
            std::cout << colorToChar(up.sticker(2,0)) <<  sp6 << colorToChar(up.sticker(1,1)) << sp6 << colorToChar(up.sticker(0,2)) << sp7 << sp3 << colorToChar(left.sticker(0,2)) << sp5 << colorToChar(left.sticker(1,0)) << " " << colorToChar(back.sticker(1,2)) << sp5 << colorToChar(back.sticker(0,0)) << std::endl;
            std::cout << colorToChar(front.sticker(0,0)) << sp3 << colorToChar(up.sticker(2,1)) << sp5 << colorToChar(up.sticker(1,2)) << sp3 << colorToChar(right.sticker(0,2)) << sp7 << sp3 << sp3 << colorToChar(left.sticker(1,1)) << sp7 << colorToChar(back.sticker(1,1)) << sp3 << std::endl;
            std::cout << sp3 << colorToChar(front.sticker(0,1)) << sp3 << colorToChar(up.sticker(2,2)) << sp3 << colorToChar(right.sticker(0,1)) << sp3 << sp7 << sp3 << colorToChar(left.sticker(1,2)) << sp5 << colorToChar(left.sticker(2,0)) << " " << colorToChar(back.sticker(2,2)) << sp5 << colorToChar(back.sticker(1,0)) << std::endl;
            std::cout << colorToChar(front.sticker(1,0)) << sp5 << colorToChar(front.sticker(0,2)) << " " << colorToChar(right.sticker(0,0)) << sp5 << colorToChar(right.sticker(1,2)) << sp7 << sp3 << sp3 << colorToChar(left.sticker(2,1)) << sp3 << colorToChar(down.sticker(2,0)) << sp3 << colorToChar(back.sticker(2,1)) << sp3 << std::endl;
            std::cout << sp3 << colorToChar(front.sticker(1,1)) << sp7 << colorToChar(right.sticker(1,1)) << sp3 << sp7 << sp3 << colorToChar(left.sticker(2,2)) << sp3 << colorToChar(down.sticker(1,0)) << sp5 << colorToChar(down.sticker(2,1)) << sp3 << colorToChar(back.sticker(0,0)) << std::endl;
            std::cout << colorToChar(front.sticker(2,0)) << sp5 << colorToChar(front.sticker(1,2)) << " " << colorToChar(right.sticker(1,0)) << sp5 << colorToChar(right.sticker(2,2)) << sp7 << sp3 << colorToChar(down.sticker(0,0)) <<  sp6 << colorToChar(down.sticker(1,1)) << sp6 << colorToChar(down.sticker(2,2)) << std::endl;
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

RubixCube & RubixCube::rotateCW(RubixFace face)
{
    std::vector<RubixColor> tempRow;
    switch(face)
    {
        case UP:
            up.rotateCW();
            std::swap(left.stickers[0],front.stickers[0]);
            std::swap(right.stickers[0],front.stickers[0]);
            std::swap(right.stickers[0],back.stickers[0]); 
            break; 
        case DOWN:
            down.rotateCW();
            std::swap(right.stickers[2],front.stickers[2]);
            std::swap(left.stickers[2],front.stickers[2]);
            std::swap(left.stickers[2],back.stickers[2]);
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
            right.stickers[2][2] = down.sticker(2,2);
            right.stickers[1][2] = down.sticker(2,1);
            right.stickers[0][2] = down.sticker(2,0);
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
            std::swap(right.stickers[0],front.stickers[0]);
            std::swap(left.stickers[0],front.stickers[0]);
            std::swap(left.stickers[0],back.stickers[0]); 
            break; 
        case DOWN:
            down.rotateCCW();
            std::swap(left.stickers[2],front.stickers[2]);
            std::swap(right.stickers[2],front.stickers[2]);
            std::swap(right.stickers[2],back.stickers[2]);
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
            left.stickers[0][0] = down.sticker(0,2);
            left.stickers[1][0] = down.sticker(0,1);
            left.stickers[2][0] = down.sticker(0,0);
            down.stickers[0][2] = right.sticker(0,2);
            down.stickers[0][1] = right.sticker(1,2);
            down.stickers[0][0] = right.sticker(2,2);
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
            down.stickers[0][0] = back.sticker(0,2);
            down.stickers[1][0] = back.sticker(1,2);
            down.stickers[2][0] = back.sticker(2,2);
            back.stickers[0][2] = tempRow[2];
            back.stickers[1][2] = tempRow[1];
            back.stickers[2][2] = tempRow[0];
            break;
        case RIGHT:
            right.rotateCCW();
            tempRow = {up.sticker(2,2), up.sticker(1,2), up.sticker(0,2)};
            up.stickers[0][2] = back.sticker(0,0);
            up.stickers[1][2] = back.sticker(1,0);
            up.stickers[2][2] = back.sticker(2,0);
            back.stickers[0][0] = down.sticker(0,2);
            back.stickers[1][0] = down.sticker(1,2);
            back.stickers[2][0] = down.sticker(2,2);
            down.stickers[0][2] = front.sticker(2,2);
            down.stickers[1][2] = front.sticker(1,2);
            down.stickers[2][2] = front.sticker(0,2);
            front.stickers[0][2] = tempRow[2];
            front.stickers[1][2] = tempRow[1];
            front.stickers[2][2] = tempRow[0];
            break;
    }

    return *this;
}

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
        randomCube.rotateCW(static_cast<RubixFace>(rand() % 6));
        i++;
#if _DEBUG
        if (i % 30000000 == 0)
            randomCube.print();
#endif
    }

    int elapsedTime = time(0) - startTime;
    std::cout << "Solved cube with monkey and a typewriter: " << i << " moves in ";
    std::cout << (int)(elapsedTime / 60) << " minutes " << elapsedTime % 60 << " seconds." << std::endl;
}

int main()
{

    srand(time(0));
    testRotations();

    RubixCube cube;
    cube.rotateCW(RIGHT).rotateCW(RIGHT).rotateCCW(LEFT).rotateCCW(LEFT);
    cube.rotateCW(FRONT).rotateCW(FRONT).rotateCCW(BACK).rotateCCW(BACK);
    cube.rotateCW(UP).rotateCW(UP).rotateCCW(DOWN).rotateCCW(DOWN);
    cube.print();

    RubixCube cube2(25000);
    cube2.print();
    
    dummySolver();
}
