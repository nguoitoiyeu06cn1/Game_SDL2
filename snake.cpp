#include "snake.h"
#include "graphics.h"
#include <vector>

#include <cmath> //

Snake::Snake(int startX, int startY) : speedMultiplier(1.0) {
    segments = {
    {startX / 2, startY / 2},
    {startX / 2 - 20, startY / 2},
    {startX / 2 - 40, startY / 2}
};

}

void Snake::update(double velX, double velY) {
    SnakeSegment newHead = {segments[0].x + (int)velX, segments[0].y + (int)velY};

    // Di chuyen cua ran het man hinh se di nguoc lai
    if (newHead.y < 0) newHead.y = SCREEN_HEIGHT;
    if (newHead.y > SCREEN_HEIGHT) newHead.y = 0;
    if (newHead.x < 0) newHead.x = SCREEN_WIDTH;
    if (newHead.x > SCREEN_WIDTH) newHead.x = 0;

    segments.insert(segments.begin(), newHead);
    segments.pop_back();
}


void Snake::draw(SDL_Renderer* renderer) {
    int i = 0;
    for (const auto& segment : segments) {
        if(i == 0){
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // xet mau cho dau ran, mau nau
            drawCircle(renderer, segment.x, segment.y, CIRCLE_RADIUS + 3);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // xet mau cho  ran, mau nau
            drawCircle(renderer, segment.x, segment.y, CIRCLE_RADIUS);
        }
         i ++;
    }
}

void Snake::grow() {
    segments.push_back(segments.back());
    speedMultiplier *= 1.2;  // Dieu chinh toc do neu can
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
        {startX / 2 - 20, startY / 2},
        {startX / 2 - 40, startY / 2}
    };
    speedMultiplier = 1.0;
}


SnakeSegment Snake::getHead() const {
  return segments[0];
}

std::vector<SnakeSegment> Snake::getSegments() const {
  return segments;
}
