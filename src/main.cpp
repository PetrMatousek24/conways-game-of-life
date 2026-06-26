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

#define cellSize    25


//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int SCREEN_HEIGHT = 900;
static const int SCREEN_WIDTH = 900;
static const int TARGETFPS = 12;

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


//------------------------------------------------------------------------------------
// Functions declarations
//------------------------------------------------------------------------------------
static void InitGame();
static void UpdateGame();
static void RenderGame();
static void UnloadGame();

static int CountLiveNeighbors(int row, int col);


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
    
    std::cout << CountLiveNeighbors(2, 5) << std::endl;
    std::cout << CountLiveNeighbors(3, 4) << std::endl;
}


// Core game logic in the game loop
void UpdateGame() {
    
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
        int rowOffset = row + cellOffset.x;
        int colOffset = col + cellOffset.y;

        if (grid.GetValue(rowOffset, colOffset) == 1) liveNeighbors++;
    }

    return liveNeighbors;
}