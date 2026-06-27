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
#define GAME_SPEED  0.2 // a simulation per x seconds
#define FAST_SPEED  GAME_SPEED/2 
#define SLOW_SPEED  GAME_SPEED*2


//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int SCREEN_HEIGHT = 900;
static const int SCREEN_WIDTH = 900;
static const int TARGETFPS = 60;
static float gameSpeed = GAME_SPEED; // a variable

static bool running = true;
static bool showKeybinds = true;

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

static void DrawKeybindsText();
static void HandleInput();

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
    HandleInput();

    if (HasIntervalPassed(gameSpeed) && running) {
        RunSimulation();
    }
}


// Draw the game
void RenderGame() {
    BeginDrawing();
        ClearBackground(gray);

        grid.Draw();

        DrawKeybindsText();

        DrawFPS(10, 10);
    EndDrawing();
}


// Unload game assets at the end of the game
void UnloadGame() {
}


//------------------------------------------------------------------------------------
// Helper modules definitions
//------------------------------------------------------------------------------------
void DrawKeybindsText() {
    if (showKeybinds == false) return;

    DrawText("space - pause and run", 40, 40, 30, GREEN);
    DrawText("R - reset", 40, 80, 30, GREEN);
    DrawText("Left arrow - slow down", 40, 120, 30, GREEN);
    DrawText("Right arrow - speed up", 40, 160, 30, GREEN);
    DrawText("K = show keybinds", 40, 200, 30, GREEN);
}


void HandleInput() {
    int keyPressed = GetKeyPressed();

    switch (keyPressed) {
    case KEY_SPACE:
        running ? running = false : running = true;
        break;
    case KEY_K:
        showKeybinds ? showKeybinds = false : showKeybinds = true;
        break;
    case KEY_R:
        grid.SetGridBackToOrigin();
        running = false;
        break;
    
    default:
        break;
    }


    if (IsKeyDown(KEY_RIGHT)) gameSpeed = FAST_SPEED;
    else if (IsKeyDown(KEY_LEFT)) gameSpeed = SLOW_SPEED;
    else gameSpeed = GAME_SPEED;
}


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