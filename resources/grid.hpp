#pragma once
#include <raylib.h>
#include <vector>


class Grid { 
// Private members
private:
    int cellSize, rotationState;

    // Private functions


// Public members
public:
    int id;
    int rowOffset, colOffset;
    std::vector<int> grid;

    // Constructor
    Grid();

    // Public functions
    void Draw(int offsetOfX = 0, int offsetOfY = 0);
    void Move(int rows, int columns);
    void Rotate();
    void UndoRotation();
    std::vector<Vector2> GetCellPositions();
};


//------------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// Private members
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Public interface
//------------------------------------------------------------------------------------