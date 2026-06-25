#include <raylib.h>

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


//------------------------------------------------------------------------------------
// Functions declarations
//------------------------------------------------------------------------------------
static void InitGame();
static void UpdateGame();
static void RenderGame();
static void UnloadGame();


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
// Functions definitions
//------------------------------------------------------------------------------------
// Initialize values before the game starts
void InitGame() {
    
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