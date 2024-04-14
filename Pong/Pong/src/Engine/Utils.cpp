#include "Utils.h"

#include <iostream>

bool Utils::CheckCollisionAABB(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    return (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
}

bool Utils::CheckCollisionAABB(bool center_aligned, glm::vec2 p1, int w1, int h1, glm::vec2 p2, int w2, int h2)
{
    if (center_aligned == false) {
        return CheckCollisionAABB(p1.x, p1.y, w1, h1, p1.x, p2.y, w2, h2);
    }
    
    return CheckCollisionAABB(p1.x - w1 / 2, p1.y - h1 / 2, w1, h1, p2.x - w2 / 2, p2.y - h2 / 2, w2, h2);
}

bool Utils::CheckCollisionAABB(bool center_aligned, glm::vec2 p1, glm::vec2 s1, glm::vec2 p2, glm::vec2 s2)
{
    if (center_aligned == false) {
        return CheckCollisionAABB(p1.x, p1.y, s1.x, s1.y, p2.x, p2.y, s2.x, s2.y);
    }
    
    return CheckCollisionAABB(p1.x - s1.x / 2, p1.y - s1.y / 2, s1.x, s1.y, p2.x - s2.x / 2, p2.y - s2.y / 2, s2.x, s2.y);
}

// Unit tests for Method 1
void Utils::TestMethod1() {
    // Non-overlapping rectangles
    assert(!CheckCollisionAABB(0, 0, 2, 2, 4, 4, 2, 2));
    // Overlapping rectangles
    assert(CheckCollisionAABB(0, 0, 2, 2, 1, 1, 2, 2));
    // Touching rectangles
    assert(!CheckCollisionAABB(0, 0, 2, 2, 2, 2, 2, 2));
}

// Unit tests for Method 2
void Utils::TestMethod2() {
    // Non-overlapping rectangles
    assert(!CheckCollisionAABB(false, glm::vec2(0, 0), 2, 2, glm::vec2(4, 4), 2, 2));
    // Overlapping rectangles
    assert(CheckCollisionAABB(false, glm::vec2(0, 0), 2, 2, glm::vec2(1, 1), 2, 2));
    // Touching rectangles
    assert(!CheckCollisionAABB(false, glm::vec2(0, 0), 2, 2, glm::vec2(2, 2), 2, 2));
}

// Unit tests for Method 3
void Utils::TestMethod3() {
    // Non-overlapping rectangles
    assert(!CheckCollisionAABB(false, glm::vec2(0, 0), glm::vec2(2, 2), glm::vec2(4, 4), glm::vec2(2, 2)));
    // Overlapping rectangles
    assert(CheckCollisionAABB(false, glm::vec2(0, 0), glm::vec2(2, 2), glm::vec2(1, 1), glm::vec2(2, 2)));
    // Touching rectangles
    assert(!CheckCollisionAABB(false, glm::vec2(0, 0), glm::vec2(2, 2), glm::vec2(2, 2), glm::vec2(2, 2)));
}