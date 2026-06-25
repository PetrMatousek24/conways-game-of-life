#pragma once
#include <raylib.h>
#include <vector>


class Grid { 
// Private members
private:
    int rows, cols;
    int cellSize;
    // Private functions


// Public members
public:
    std::vector<std::vector<int>> cells;

    // Constructor
    Grid(int width, int height, int cellSize):
        rows(width/cellSize), cols(height/cellSize), cellSize(cellSize), cells(rows, std::vector<int>(cols, 0))
    {}

    // Public functions
    void Draw();
};


//------------------------------------------------------------------------------------
// Private members
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Public interface
//------------------------------------------------------------------------------------
void Grid::Draw() {
    for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
        DrawRectangle(col*cellSize, row*cellSize, cellSize-1, cellSize-1, cells[row][col] ? WHITE : BLACK);
    }
    }
}