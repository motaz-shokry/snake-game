#include "game.h"    // For Game class
#include "globals.h" // For constants
#include "utils.h"   // For eventTriggered
#include <raylib.h>
#include <string> // For std::to_string

int main(void) {
    // Calculate window dimensions using constants
    const int screenWidth = static_cast<int>(2 * offset + cellSize * cellCount);
    const int screenHeight =
        static_cast<int>(2 * offset + cellSize * cellCount);
    const char *title = "Snake Game - Structured";

    SetConfigFlags(FLAG_VSYNC_HINT); // Optional: Improve rendering smoothness
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60); // Target FPS

    Game game; // Create the game instance (initializes audio, loads assets)

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // --- Update ---
        game.HandleInput(); // Process player input

        // Update game state at a fixed interval
        if (eventTriggered(0.2f)) { // Use 0.2f for float literal
            game.Update(); // Update game logic (snake movement, collisions) if
                           // running
        }

        // --- Draw ---
        BeginDrawing();
        ClearBackground(green); // Use background color from globals

        // Draw game borders/UI
        DrawRectangleLinesEx({offset - 5, offset - 5, cellSize * cellCount + 10,
                              cellSize * cellCount + 10},
                             5, // Thickness
                             darkGreen);

        // Draw Title centered
        int titleFontSize = 30;
        int titleWidth = MeasureText("Retro Snake Game", titleFontSize);
        DrawText("Retro Snake Game", screenWidth / 2 - titleWidth / 2, 15,
                 titleFontSize, darkGreen);

        // Draw Score
        std::string scoreText = "Score: " + std::to_string(game.score);
        DrawText(scoreText.c_str(), offset - 5,
                 offset + cellSize * cellCount + 10, 40, darkGreen);

        // Draw game elements (snake, food) inside the Game class
        game.Draw();

        // Draw FPS (optional debugging)
        // DrawFPS(10, 10);

        EndDrawing();
    }

    // De-Initialization
    // Game destructor (~Game) handles unloading sounds and closing audio.
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
