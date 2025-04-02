#include "AIsnake.h"
#include <cstdlib> // Need rand()
#include <cmath> // Need some functions

AIsnake :: AIsnake(int startX, int startY, int initialDirection) : currentDirection(initialDirection)
{
    segments = {{startX - 300, startY - 300},
                {startX - 320, startY - 320},
                {startX - 340, startY - 340}
    };
    switch (initialDirection)
    {
        case 0: velX = 0; velY = -4; break; //up
        case 1: velX = 0; velY = 4; break; //down
        case 2: velX = -4; velY = 0; break; //left
        case 3: velX = 4; velY = 0; break; //right

    }
}
void AIsnake::update(int playerSnakeX, int playerSnakeY)
{
    // random direction change
    if(rand() % 100 < 5) // 5% chance to change direction
    // co the cai tien sao cho ran ai duoi theo chu the cu the la dau ran chu the bang viec kiem tra khoang cach dau ran ai va dau ran chu the sau do se cho random tiep
    {
        currentDirection = rand() % 4; // choose a new random direction
        switch (currentDirection)
        {
            case 0: velX = 0; velY = -4; break; //up
            case 1: velX = 0; velY = 4; break; //down
            case 2: velX = -4; velY = 0; break; //left
            case 3: velX = 4; velY = 0; break; //right
        }
    }

    SnakeSegment newHead = {segments[0].x + (int)velX, segments[0].y + (int)velY};

    // wrap around logic
     if (newHead.y < 0) newHead.y = SCREEN_HEIGHT; // Sử dụng SCREEN_HEIGHT
    if (newHead.y > SCREEN_HEIGHT) newHead.y = 0;
    if (newHead.x < 0) newHead.x = SCREEN_WIDTH; // Sử dụng SCREEN_WIDTH
    if (newHead.x > SCREEN_WIDTH) newHead.x = 0;

    segments.insert(segments.begin(), newHead);
    segments.pop_back();

}
void AIsnake::draw(SDL_Renderer * renderer)
{
    int i = 0;
    for(const auto& segment: segments)
    {
        if(i == 0) {  // Phần đầu rắn
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Đặt màu đỏ cho đầu rắn
            drawCircle(renderer, segment.x, segment.y, 11);  // Vẽ đầu rắn với kích thước lớn hơn
        }
        else {  // Các phần thân rắn
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // Màu vàng cho thân rắn
            drawCircle(renderer, segment.x, segment.y, 10);  // Vẽ thân rắn
        }
        i++;  // Tăng biến đếm
    }
}


bool AIsnake::checkCollision(const Snake& playerSnake)
{
    SnakeSegment aiHead = segments[0];
    vector <SnakeSegment> playerSegments = playerSnake.getSegments();
    for(const auto& playerSegment : playerSegments)
    {
        double distance = hypot(aiHead.x - playerSegment.x, aiHead.y - playerSegment.y);
        if(distance < 20) return true; // collision happened
    }
    return false;
}

//bool AIsnake::checkSelfCollision()
//{
//    SnakeSegment head = segments[0];
//    for(size_t i = 1; i < segments.size(); ++i)
//    {
//        if(head.x == segments[i].x && head.y == segments[i].y)
//        {
//            return true;
//        }
//    }
//    return false;
//}

const vector <SnakeSegment>& AIsnake::getSegments() const
{
    return segments;
}
