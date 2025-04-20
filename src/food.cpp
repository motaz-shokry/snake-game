#include "food.h"
#include "utils.h"  // For elementInDeque
#include <iostream> // For error reporting
#include <raylib.h> // For Raylib functions

// Pass snakeBody by const reference
Food::Food(const std::deque<Vector2> &snakeBody) {
    Image image = LoadImage("assets/food.png");
    // Basic error checking for image loading
    if (image.data == nullptr) {
        std::cerr << "ERROR: Failed to load image 'assets/food.png'\n";
        // Consider setting a default texture or position, or exiting
        texture = {0}; // Assign a default invalid texture
    } else {
        texture = LoadTextureFromImage(image);
        UnloadImage(image); // Unload image CPU data once texture is on GPU
    }
    position = GenerateRandomPos(snakeBody);
}

Food::~Food() {
    // Check if texture is valid before unloading
    if (texture.id > 0) {
        UnloadTexture(texture);
    }
}

void Food::Draw() {
    // Check if texture is valid before drawing
    if (texture.id > 0) {
        DrawTexture(texture, offset + position.x * cellSize,
                    offset + position.y * cellSize, WHITE);
    } else {
        // Optionally draw a placeholder if texture failed to load
        DrawRectangle(offset + position.x * cellSize,
                      offset + position.y * cellSize, cellSize, cellSize, RED);
    }
}

Vector2 Food::GenerateRandomCell() {
    // GetRandomValue typically takes integers for min/max
    float x =
        static_cast<float>(GetRandomValue(0, static_cast<int>(cellCount) - 1));
    float y =
        static_cast<float>(GetRandomValue(0, static_cast<int>(cellCount) - 1));
    return {x, y};
}

// Pass snakeBody by const reference
Vector2 Food::GenerateRandomPos(const std::deque<Vector2> &snakeBody) {
    Vector2
        new_pos; // Use a different name to avoid shadowing member 'position'
    // Use do-while to guarantee at least one generation attempt
    do {
        new_pos = GenerateRandomCell();
    } while (elementInDeque(
        new_pos,
        snakeBody)); // Keep trying until position is not in the snake body
    return new_pos;
}
