#include "snake.h"
#include "graphics.h"
#include <vector>

#include <cmath> //

Snake::Snake(int startX, int startY) : speedMultiplier(1.0) {
    segments = {
        {startX / 2, startY / 2},
        {startX / 2 - 300, startY / 2 -300},
        {startX / 2 - 330, startY / 2 -300}
    };
}

void Snake::update(double velX, double velY) {
    SnakeSegment newHead = {segments[0].x + (int)velX, segments[0].y + (int)velY};

    // Di chuyen cua ran het man hinh se di nguoc lai
    if (newHead.y < 0) newHead.y = 600;
    if (newHead.y > 600) newHead.y = 0;
    if (newHead.x < 0) newHead.x = 800;
    if (newHead.x > 800) newHead.x = 0;

    segments.insert(segments.begin(), newHead);
    segments.pop_back();
}


void Snake::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // xet mau cho ran, mau nau
    for (const auto& segment : segments) {
        drawCircle(renderer, segment.x, segment.y, CIRCLE_RADIUS); // dung ham render tu thu graphics.cpp de ve tat ca vat the thanh hinh tron
    }
}

void Snake::grow() {
    segments.push_back(segments.back());
    speedMultiplier *= 1.1;  // Dieu chinh toc do neu can
}

bool Snake::checkCollisions(const vector <SnakeSegment>& otherSnakeSegments)
{
    SnakeSegment head = segments[0];
    for (const auto& segment : otherSnakeSegments) {
        double distance = hypot(head.x - segment.x, head.y - segment.y);
        if (distance < 20) { // Điều chỉnh khoảng cách va chạm nếu cần
            return true;
        }
    }
    return false;
}

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
        {startX / 2 - 300, startY / 2 -300},
        {startX / 2 - 330, startY / 2 -300}
    };
    speedMultiplier = 1.0;
}

SnakeSegment Snake::getHead() const {
  return segments[0];
}

std::vector<SnakeSegment> Snake::getSegments() const {
  return segments;
}
