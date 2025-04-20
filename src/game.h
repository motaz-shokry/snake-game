#ifndef GAME_HPP
#define GAME_HPP

#include "food.h"   // Game uses Food
#include "snake.h"  // Game uses Snake
#include <raylib.h> // For Sound type

class Game {
  public:
    Snake snake;
    Food food; // Initialized in constructor
    bool running;
    short score; // Consider using int or unsigned int for score
    Sound eatSound;
    Sound wallSound;

    Game();  // Constructor
    ~Game(); // Destructor

    void Update();
    void Draw();
    void HandleInput();     // Separate input handling logic
    void CheckCollisions(); // Separate collision logic

  private:
    // Keep collision check details private
    void CheckCollisionWithFood();
    void CheckCollisionWithEdges();
    void CheckCollisionWithSelf(); // Renamed for clarity
    void GameOver();
};

#endif // GAME_HPP
