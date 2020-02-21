// File   : main.cpp
// Author : Jarrett McCarty

#include <iostream>

#include "MyMaze.h"


int main()
{
    /* Variable for N x N Maze generation */
    int n;
    /* sr = Starting row, sc = Starting col -- Coords used to init start pos */
    int sr, sc;
    /* Cin the variables */
    try
    {
        std::cin >> n >> sr >> sc;
        
        /* Use variables to init the Random maze process */
        Maze maze(n, n, sr, sc);
        
        /* Cout the maze itself */
        std::cout << maze;
    }
    catch (InvalidMaze & e)
    {
        std::cout << e.what();
    }
    catch (InvalidRC & e)
    {
        std::cout << e.what();
    }

    return 0;
}
