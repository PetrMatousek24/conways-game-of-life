#include <raylib.h>
#include <vector>
#include <iostream>

#include "resources/grid.hpp"


// defines --> constatns --> classes --> global variables --> functions declarations -->
// program --> game modules definitions --> helper modules definitions


//------------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------------
#define gray        (Color){32, 32, 32, 255}

#define cellSize    25 // pixels


//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int SCREEN_HEIGHT = 900;
static const int SCREEN_WIDTH = 900;
static const int TARGETFPS = 60;
static int gameSpeed = 0.2; // a simulation per x seconds

static bool running = false;

static Grid grid = Grid(SCREEN_WIDTH, SCREEN_HEIGHT, cellSize);
static std::vector<Vector2> cellOffsets = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1},
};

double lastUpdateTime = 0;


//------------------------------------------------------------------------------------
// Functions declarations
//------------------------------------------------------------------------------------
static void InitGame();
static void UpdateGame();
static void RenderGame();
static void UnloadGame();

static int CountLiveNeighbors(int row, int col);
static void RunSimulation();

static bool HasIntervalPassed(double interval);


//------------------------------------------------------------------------------------
// Program
//------------------------------------------------------------------------------------
int main() 
{
    // Initalize window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World");
    SetWindowPosition(GetMonitorWidth(0) / 2 - GetScreenWidth() / 2, GetMonitorHeight(0) / 2 - GetScreenHeight() / 2);

    InitGame();

    SetTargetFPS(TARGETFPS);


    // Game loop
    while(WindowShouldClose() == false) 
    {
        // Core game logic
        UpdateGame();

        // Render all objects
        RenderGame();
    }


    // End game
    UnloadGame();
    CloseWindow();
    return 0;
}


//------------------------------------------------------------------------------------
// Game modules definitions
//------------------------------------------------------------------------------------
// Initialize values before the game starts
void InitGame() {
    grid.SetValue(3, 3, 1);
    grid.SetValue(4, 4, 1);
    grid.SetValue(4, 5, 1);
    grid.SetValue(3, 5, 1);
    grid.SetValue(2, 5, 1);
}


// Core game logic in the game loop
void UpdateGame() {
    if (HasIntervalPassed(gameSpeed)) {
        RunSimulation();
    }
}


// Draw the game
void RenderGame() {
    BeginDrawing();
        ClearBackground(gray);

        grid.Draw();

        DrawFPS(10, 10);
    EndDrawing();
}


// Unload game assets at the end of the game
void UnloadGame() {

}


//------------------------------------------------------------------------------------
// Helper modules definitions
//------------------------------------------------------------------------------------
int CountLiveNeighbors(int row, int col) {
    int liveNeighbors = 0;

    for (Vector2 cellOffset : cellOffsets) {
        int rowOffset = (row + (int)cellOffset.x + grid.GetTotalRows()) % grid.GetTotalRows();
        int colOffset = (col + (int)cellOffset.y + grid.GetTotalCols()) % grid.GetTotalCols();

        if (grid.GetValue(rowOffset, colOffset) == 1) liveNeighbors++;
    }

    return liveNeighbors;
}


void RunSimulation() {
    for (int row = 0; row < grid.GetTotalRows(); row++) {
    for (int col = 0; col < grid.GetTotalCols(); col++) {

        int cell = grid.GetValue(row, col);
        int liveNeighbors = CountLiveNeighbors(row, col);

        if (cell == 1) { // alive
            if (liveNeighbors < 2 || liveNeighbors > 3) {
                grid.SetSimulationValue(row, col, 0); // dies
            } else {
                grid.SetSimulationValue(row, col, 1); // lives
            }
        } else if (cell == 0) { // dead
            if (liveNeighbors == 3) {
                grid.SetSimulationValue(row, col, 1); // resurects
            } else {
                grid.SetSimulationValue(row, col, 0); // stays dead
            }
        }

    }
    }

    grid.UpdateSimulation();
}

bool HasIntervalPassed(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}