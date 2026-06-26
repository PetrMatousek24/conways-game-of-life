#pragma once
#include <raylib.h>
#include <vector>


class Grid { 
// Private members
private:
    int rows, cols;
    int cellSize;
    std::vector<std::vector<int>> cells;

    // Private functions
    bool IsWithinBounds(int row, int col);


// Public members
public:
    // Constructor
    Grid(int width, int height, int cellSize):
        rows(width/cellSize), cols(height/cellSize), cellSize(cellSize), cells(rows, std::vector<int>(cols, 0))
    {}

    // Public functions
    void Draw();
    void SetValue(int row, int col, int value);
    int GetValue(int row, int col);
};


//------------------------------------------------------------------------------------
// Private members
//------------------------------------------------------------------------------------
bool Grid::IsWithinBounds(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) return false;
    return true;
}


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


void Grid::SetValue(int row, int col, int value) {
    if (IsWithinBounds(row, col) == false) return;

    cells[row][col] = value;
}

int Grid::GetValue(int row, int col) {
    if (IsWithinBounds(row, col) == false) return 0;

    return cells[row][col];
}