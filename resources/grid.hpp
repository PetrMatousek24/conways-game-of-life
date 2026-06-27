#pragma once
#include <raylib.h>
#include <vector>


class Grid { 
// Private members
private:
    int rows, cols;
    int cellSize;
    int iteration;

    std::vector<std::vector<int>> cells;
    std::vector<std::vector<int>> nextSimulation;
    std::vector<std::vector<int>> originalCells;

    // Private functions
    bool IsWithinBounds(int row, int col);


// Public members
public:
    // Constructor
    Grid(int width, int height, int cellSize):
        rows(height/cellSize), 
        cols(width/cellSize), 
        cellSize(cellSize), 
        iteration(0),
        cells(rows, std::vector<int>(cols, 0)), 
        nextSimulation(rows, std::vector<int>(cols, 0)), 
        originalCells(rows, std::vector<int>(cols, 0))
    {}

    // Public functions
    void Draw();

    void SetValue(int row, int col, int value);
    int GetValue(int row, int col);
    void ClearGrid();

    void SetSimulationValue(int row, int col, int value);
    void UpdateSimulation();

    void SetGridBackToOrigin();
    void UpdateIteration(bool reset = false);

    int GetTotalRows();
    int GetTotalCols();
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

void Grid::ClearGrid() {
    for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
        cells[row][col] = 0;
    }
    }
}


void Grid::SetSimulationValue(int row, int col, int value) {
    if (IsWithinBounds(row, col) == false) return;

    nextSimulation[row][col] = value;
}

void Grid::UpdateSimulation() {
    if (iteration == 0) originalCells = cells;

    cells = nextSimulation;
    UpdateIteration();
}


void Grid::SetGridBackToOrigin() {
    cells = originalCells;
    UpdateIteration(true);
}


void Grid::UpdateIteration(bool reset) {
    if (reset == false) iteration++;
    else iteration = 0;
}


int Grid::GetTotalRows() {
    return rows;
}

int Grid::GetTotalCols() {
    return cols;
}