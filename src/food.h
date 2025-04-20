#ifndef FOOD_H
#define FOOD_H

#include "globals.h" // Include for constants
#include <deque>
#include <raylib.h>

class Food {
  public:
    Vector2 position;
    Texture2D texture;

    // Constructor needs the initial snake body to avoid spawning inside it
    Food(const std::deque<Vector2> &snakeBody); // Pass by const reference
    ~Food();                                    // Destructor to unload texture

    void Draw();
    // Make GenerateRandomPos public so Game can reposition it easily
    Vector2 GenerateRandomPos(
        const std::deque<Vector2> &snakeBody); // Pass by const reference

  private:
    Vector2 GenerateRandomCell(); // Keep this helper private
};

#endif // FOOD_HPP
