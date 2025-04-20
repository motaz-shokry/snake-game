#include "snake.h"
#include <raymath.h> // For Vector2Add

// Define the constructor using an initializer list
Snake::Snake()
    : body({Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}}), direction({1, 0}),
      addSegment(false) {}

void Snake::Draw() {
    // Use range-based for loop
    for (const auto &segmentPos : body) {
        Rectangle segment = {offset + segmentPos.x * cellSize,
                             offset + segmentPos.y * cellSize, cellSize,
                             cellSize};
        // Use 0.5f for float literal
        DrawRectangleRounded(segment, 0.5f, 6, darkGreen);
    }
}

void Snake::Update() {
    body.push_front(Vector2Add(body.front(), direction));

    if (addSegment) {
        addSegment = false; // Consume the flag
    } else {
        body.pop_back();
    }
}

void Snake::Reset() {
    body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    direction = {1, 0};
    addSegment = false; // Also reset the addSegment flag
}
