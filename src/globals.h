#ifndef GLOBALS_H
#define GLOBALS_H

#include <raylib.h>

// Using const directly in the header is often fine for simple types
const Color green = {152, 151, 26, 255};
const Color darkGreen = {43, 51, 24, 255};

const float cellSize = 30.0f; // Use 'f' suffix for float literals
const float cellCount = 25.0f;
const float offset = 55.0f;

// Note: lastUpdateTime is specific to eventTriggered, so it will be kept static
// in utils.cpp

#endif // GLOBALS_HPP
