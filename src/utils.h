#ifndef UTILS_HPP
#define UTILS_HPP

#include <deque>
#include <raylib.h>  // For Vector2
#include <raymath.h> // For Vector2Equals

// Function declarations
bool eventTriggered(float interval);
bool elementInDeque(
    Vector2 element,
    const std::deque<Vector2> &deque); // Pass deque by const reference

#endif // UTILS_HPP
