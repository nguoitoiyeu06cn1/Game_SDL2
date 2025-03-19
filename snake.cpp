#include "snake.h"
#include "graphics.h"
#include <vector>

#include <cmath> // For sqrt (if using mouse control within the Snake class)

Snake::Snake(int startX, int startY) : speedMultiplier(1.0) {
    segments = {
        {startX / 2, startY / 2},
        {startX / 2 - 15, startY / 2},
        {startX / 2 - 30, startY / 2}
    };
}

void Snake::update(double velX, double velY) {
    SnakeSegment newHead = {segments[0].x + (int)velX, segments[0].y + (int)velY};

    // Wrap around logic (consider moving SCREEN_WIDTH/HEIGHT to a global config file/header)
    if (newHead.y < 0) newHead.y = 600;
    if (newHead.y > 600) newHead.y = 0;
    if (newHead.x < 0) newHead.x = 800;
    if (newHead.x > 800) newHead.x = 0;

    segments.insert(segments.begin(), newHead);
    segments.pop_back();
}


void Snake::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Snake color
    for (const auto& segment : segments) {
        drawCircle(renderer, segment.x, segment.y, CIRCLE_RADIUS); // Use the drawCircle function from graphics.cpp
    }
}

void Snake::grow() {
    segments.push_back(segments.back());
    speedMultiplier *= 1.1;  // Adjust speed increase as needed.  Consider making this configurable.
}

/*bool Snake::checkCollisions( vector <SnakeSegment>& otherSnakeSegments)
{
    SnakeSegment head = segments[0];
    for (const auto& segment : otherSnakeSegments) {
        double distance = hypot(head.x - segment.x, head.y - segment.y);
        if (distance < 20) { // Điều chỉnh khoảng cách va chạm nếu cần
            return true;
        }
    }
    return false;
}*/

bool Snake::checkCollision(int foodX, int foodY, int foodRadius) {
    SnakeSegment head = segments[0];
    return (abs(head.x - foodX) < foodRadius * 2 && abs(head.y - foodY) < foodRadius * 2);
}

bool Snake::checkSelfCollision() {
    SnakeSegment head = segments[0];
    for (size_t i = 1; i < segments.size(); ++i) {
        if (head.x == segments[i].x && head.y == segments[i].y) {
            return true;
        }
    }
    return false;
}

void Snake::reset(int startX, int startY) {
    segments.clear();
    segments = {
        {startX / 2, startY / 2},
        {startX / 2 - 15, startY / 2},
        {startX / 2 - 30, startY / 2}
    };
    speedMultiplier = 1.0;
}

SnakeSegment Snake::getHead() const {
  return segments[0];
}

std::vector<SnakeSegment> Snake::getSegments() const {
  return segments;
}
