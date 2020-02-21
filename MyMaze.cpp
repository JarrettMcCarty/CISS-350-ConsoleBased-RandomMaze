// File   : MyMaze.cpp
// Author : Jarrett McCarty

#include "MyMaze.h"
#include "Stack.h" 
#include <algorithm>
#include <random>
#include <iostream>
#include <set>
#include <string>
#include <vector>


/* Constructor */
Maze::Maze(int rows, int cols, int sr, int sc)
    : rows_(rows), cols_(cols)
{
    if (rows_ <= 0 || cols_ <= 0)
    {
        throw InvalidMaze();
    }
    if (sr >= rows_ || sc >= cols_)
    {
        throw InvalidRC();
    }

    /* Set RANDPATH with the random value*/
    RANDPATH = std::default_random_engine(seed);
    
    /* Allocate enough memory for all cells */
    Cell * cells = new Cell[rows * cols];

    /* Init the grid */
    grid_ = new Cell * [rows];
    for (int i = 0; i < rows; ++i)
    {
        grid_[i] = &cells[i * cols];
    }
    
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            grid_[i][j].row = i;
            grid_[i][j].col = j;
        }
    }
    
    /* Set starting position */
    grid_[sr][sc].FLAG |= SCELL;
    build_maze();
}

/* Deconstructor */
Maze::~Maze()
{
    delete [] grid_[0]; /* deallocate block of Cells */
    delete [] grid_;    /* deallocate array of pointers */
}

/* Punched walls function -- determines walls that need to be "punched" */
int Maze::punched_wall(Cell * c0, Cell * c1)
{
    if (c0 == c1)
    {
        return -1; 
    }
    
    if (c0->row == c1->row - 1 && c0->col == c1->col)
    {
        /*  c1 is north of c0, "punch" c1 south wall */
        c1->FLAG &= ~SWALL;
        
    }
    else if (c0->row == c1->row && c0->col == c1->col - 1)
    {
        /* c1 is east of c0, "punch" c0  east wall */
        c0->FLAG &= ~EWALL;
        
    }
    else if (c0->row == c1->row + 1 && c0->col == c1->col)
    {
        /* c1 is south of c0, "punch" c0 south wall */
        c0->FLAG &= ~SWALL;
        
    }
    else if (c0->row == c1->row && c0->col == c1->col + 1)
    {
        /* c1 is west of c0, "punch" c1 east wall */
        c1->FLAG &= ~EWALL;
        
    }
    else
    {
        /* No nearby cells */
        return -1; 
    }
    
    return 0;
}

/* Determines if cells are nearby and checks their validity */
std::vector<Maze::Cell*> Maze::cells_nearby(int row, int col) const
{
    Cell * NORTH = (in_bounds(row + 1, col) ? &grid_[row + 1][col] : NULL);
    Cell * EAST = (in_bounds(row, col + 1) ? &grid_[row][col + 1] : NULL);
    Cell * SOUTH = (in_bounds(row - 1, col) ? &grid_[row - 1][col] : NULL);
    Cell * WEST = (in_bounds(row, col - 1) ? &grid_[row][col - 1] : NULL);
    
    return
    {{NORTH, EAST, SOUTH, WEST}};
}

/* Checks the boundry of the Cells rows and cols*/
bool Maze::in_bounds(int row, int col) const
{
    if (row < 0 || row >= rows_)
    {
        return false;
    }
    
    if (col < 0 || col >= cols_)
    {
        return false;
    }
    
    return true;
}

/* Maze Generator Function */
void Maze::build_maze()
{
    Stack<Cell*> stack; /* Init stack for cells */
    stack.push(&grid_[0][0]);
    
    while (stack.size() > 0)
    {
        Cell * current = stack.top(); 
        stack.pop();
        
        std::vector<Cell*> cells_to_punch =
            cells_nearby(current->row, current->col);
        std::shuffle(cells_to_punch.begin(), cells_to_punch.end(), RANDPATH);   
        for (Cell * cells_to_punch : cells_to_punch)
        {
            if (cells_to_punch && visited.find(cells_to_punch) == visited.end())
            {
                punched_wall(current, cells_to_punch);
                visited.insert(cells_to_punch);
                stack.push(cells_to_punch);
            }
        }
    }
}

/* Main output operator, uses strings to store the ASCII characters */
std::ostream & Maze::print_maze(std::ostream & cout, int row) const
{
    /* North */ 
    if (row + 1 == rows_) {
        for (int col = 0; col < cols_; ++col)
        {
            cout << "+-";
        }
        
        cout << "+\n";
    }
    
    /* West */ 
    cout << "|";
    
    for (int col = 0; col < cols_; ++col)
    {
        const Cell * cell = &grid_[row][col];
        
        cout << " ";
        
        /* East */
        std::string wall = (cell->FLAG & EWALL ? "|" : " ");
        cout << wall;
    }
    
    cout << "\n";
    cout << "+";
    
    /* South */
    for (int col = 0; col < cols_; ++col)
    {
        std::string wall = (grid_[row][col].FLAG & SWALL ? "-+" : " +");
        cout << wall;
    }
    
    cout << "\n";
    
    return cout;
}


/* Output operator */
std::ostream & operator<<(std::ostream & cout, const Maze & maze)
{
    for (int row = maze.rows_ - 1; row >= 0; --row)
    {
        maze.print_maze(cout, row);
    }
    
    return cout;
}
