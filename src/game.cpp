#include "game.h"
#include "globals.h" // For cellCount
#include "utils.h"   // For elementInDeque
#include <iostream>  // For error reporting
#include <raymath.h> // For Vector2Equals

// Initialize members using an initializer list
// Crucially, initialize 'food' *after* 'snake' so snake.body exists
Game::Game()
    : snake(),          // Calls Snake's default constructor
      food(snake.body), // Pass the initial snake body to Food's constructor
      running(false), score(0) {
    // Init audio device here, once for the game
    // Check if it's already initialized if this constructor could be called
    // multiple times (unlikely here)
    if (!IsAudioDeviceReady()) {
        InitAudioDevice();
    }

    // Load sounds with basic error checking
    eatSound = LoadSound("assets/eat.mp3");
    if (!IsSoundReady(eatSound)) {
        std::cerr << "ERROR: Failed to load sound 'assets/eat.mp3'\n";
    }
    wallSound = LoadSound("assets/wall.mp3");
    if (!IsSoundReady(wallSound)) {
        std::cerr << "ERROR: Failed to load sound 'assets/wall.mp3'\n";
    }
}

Game::~Game() {
    // Unload sounds
    if (IsSoundReady(eatSound))
        UnloadSound(eatSound);
    if (IsSoundReady(wallSound))
        UnloadSound(wallSound);

    // Close audio device only if it was initialized
    if (IsAudioDeviceReady()) {
        CloseAudioDevice();
    }
}

void Game::Update() {
    if (running) {
        snake.Update();
        CheckCollisions(); // Check all collisions after updating snake position
    }
}

void Game::Draw() {
    // Order matters if you want food potentially drawn over snake or vice versa
    food.Draw();
    snake.Draw();
}

void Game::HandleInput() {
    // Only change direction if the new direction is not directly opposite
    if (IsKeyPressed(KEY_UP) && snake.direction.y != 1) {
        snake.direction = {0, -1};
        running = true; // Start game on first key press
    } else if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1) {
        snake.direction = {0, 1};
        running = true;
    } else if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1) {
        snake.direction = {-1, 0};
        running = true;
    } else if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1) {
        snake.direction = {1, 0};
        running = true;
    }
}

void Game::CheckCollisions() {
    CheckCollisionWithFood();
    CheckCollisionWithEdges();
    CheckCollisionWithSelf();
}

void Game::CheckCollisionWithFood() {
    if (Vector2Equals(snake.body.front(), food.position)) {
        // Use the food's public method to get a new position
        food.position = food.GenerateRandomPos(snake.body);
        snake.addSegment = true; // Use correct member name
        score++;
        if (IsSoundReady(eatSound))
            PlaySound(eatSound);
    }
}

void Game::CheckCollisionWithEdges() {
    // Check boundaries using < 0 for left/top and >= cellCount for right/bottom
    if (snake.body.front().x < 0 || snake.body.front().x >= cellCount) {
        GameOver();
    }
    if (snake.body.front().y < 0 || snake.body.front().y >= cellCount) {
        GameOver();
    }
}

void Game::CheckCollisionWithSelf() {
    // Create a temporary copy of the body *excluding* the head
    std::deque<Vector2> headlessBody = snake.body;
    if (!headlessBody.empty()) { // Ensure body is not empty before popping
        headlessBody.pop_front();
    }

    // Check if the head position exists in the rest of the body
    if (!headlessBody.empty() &&
        elementInDeque(snake.body.front(), headlessBody)) {
        GameOver();
    }
}

void Game::GameOver() {
    if (IsSoundReady(wallSound))
        PlaySound(wallSound);
    snake.Reset();
    // Generate food position based on the *reset* snake body
    food.position = food.GenerateRandomPos(snake.body);
    running = false;
    score = 0;
    // No need to reset direction here, Reset() handles it.
}
