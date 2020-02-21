// File   : MyMaze.h
// Author : Jarrett McCarty

#ifndef MYMAZE_H
#define MYMAZE_H

/* Includes */
#include <iostream>
#include <random>
#include <set>
#include <chrono>
#include "Stack.h"

class InvalidMaze
{
public:
    const char * what () const throw ()
    {
        return "Caught InvalidInputError--Value must be greater than zero\n";
    }
};

class InvalidRC
{
public:
    const char * what () const throw ()
    {
        return "Caught InvalidRow/ColError--Value(s) must be less than the Maze dimensions\n";
        
    }
};


/* Maze class */
class Maze
{
public:
    /* Constructor */
    Maze(int rows, int cols, int r, int c);
    
    /* Used to output the maze */
    friend std::ostream & operator<<(std::ostream & cout, const Maze & maze);

/* Destructor */
    ~Maze();    
private:
    /* Cell struct instead of a class for convience */
    struct Cell
    {
        /* Cell constructor -- Sets flags for East and west walls */
    Cell()
    : FLAG(EWALL|SWALL)
        {}
        int row; /* Row variable */
        int col;   /* Col variable */
        int FLAG; /* Flag variable */
    };
    
    /* Main Maze Generator function */
    void build_maze();
    
    /* Punched wall function -- sets walls to be "Punched Down" */
    int punched_wall(Cell * c0, Cell * c1);
    
    /* Near by cells are managed here */
    std::vector<Cell*> cells_nearby(int row, int col) const;
    
    /* Manages Boundaries */
    bool in_bounds(int row, int col) const;
    
    /* Variables for row and col for the mazeGen */
    int rows_;
    int cols_;
    
    /* 2D-Array for keeping track of cells */
    Cell **grid_;

    /* Keeps track of visited cells */
    std::set<Cell*> visited; 
    
    /* Random number generator -- Found better system than rand */
    std::default_random_engine RANDPATH;
    unsigned seed =
        std::chrono::system_clock::now().time_since_epoch().count();

    /* Attempting to use Enums */
    /* East and South status flags are set for the walls  */
    /* The status of North and west is determind by East and south */
    /* Enum declaration */
    enum Directions : int
    {
        EWALL = 0x1,
            SWALL = 0x2,
            SCELL = 0x4
            };
    
    /* Output operator */
    std::ostream & print_maze(std::ostream & cout, int row) const;
};

#endif
