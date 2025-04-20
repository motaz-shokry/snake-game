#include "utils.h"
#include <raylib.h> // For GetTime()

// Keep lastUpdateTime static, local to this translation unit
static float lastUpdateTime = 0;

bool eventTriggered(float interval) {
    float currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

// Pass deque by const reference to avoid copying
bool elementInDeque(Vector2 element, const std::deque<Vector2> &deque) {
    // Use a range-based for loop for cleaner syntax
    for (const auto &item : deque) {
        if (Vector2Equals(element, item)) {
            return true;
        }
    }
    return false;
}
