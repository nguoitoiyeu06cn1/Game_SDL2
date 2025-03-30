#include "food.h"
#include <cstdlib> //
#include "graphics.h"

Food::Food(int screenWidth, int screenHeight) {
    randomizePosition(screenWidth, screenHeight);
}

void Food::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // xet mau cho thuc an: mau do
    drawCircle(renderer, x, y, FOOD_RADIUS); //
}
void Food::randomizePosition(int screenWidth, int screenHeight) {
    int maxAttempts = 1000; // giới hạn số lần thử
    for (int attempt = 0; attempt < maxAttempts; ++attempt) {
        x = rand() % (screenWidth - 2 * FOOD_RADIUS) + FOOD_RADIUS;
        y = rand() % (screenHeight - 2 * FOOD_RADIUS) + FOOD_RADIUS;
        if (x > 200 && y > 120) {
            return; // Vị trí hợp lệ, thoát khỏi hàm
        }
    }
    // Nếu không tìm thấy vị trí hợp lệ sau nhiều lần thử,
    // hãy đặt một vị trí mặc định nào đó (hoặc xử lý lỗi)
    x = screenWidth / 2;
    y = screenHeight / 2;
   // std::cout << "Không tìm thấy vị trí hợp lệ cho thức ăn sau " << maxAttempts << " lần thử." << std::endl;
}

int Food::getX() const {
    return x;
}

int Food::getY() const {
    return y;
}
