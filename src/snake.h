#ifndef SNAKE_H
#define SNAKE_H

#include "globals.h" // Include for constants
#include <deque>
#include <raylib.h>
#include <raymath.h> // Include for Vector types if not included via raylib.h

class Snake {
  public:
    std::deque<Vector2> body;
    Vector2 direction;
    bool addSegment; // Renamed for correct spelling

    Snake(); // Declare a constructor
    void Draw();
    void Update();
    void Reset();
};

#endif // SNAKE_HPP
