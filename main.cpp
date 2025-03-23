#include "libra.h"


int main(int argc, char * argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
    TTF_Font* font = nullptr;

    if (!init(window, renderer, font)) return -1;
    texture = LoadTexture("Paint/backGround.png", renderer);

    srand(time(0));
    bool running = true;
    SDL_Event event;
    bool useMouseControl = false;

    Snake snake(SCREEN_WIDTH, SCREEN_HEIGHT); //Snake class object instantiation
    Food food(SCREEN_WIDTH, SCREEN_HEIGHT);   //Food class object instantiation
    AIsnake aiSnake(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, rand() % 4);

    double velX = 4, velY = 0;

    bool gameOver = false;
    bool paused = false;
    int highScore = loadHighScore();
    int highLevel = loadLevel();

        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                } else if (event.type == SDL_KEYDOWN && !gameOver) {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:    velX = 0; velY = -4 ; useMouseControl = false; break;
                        case SDLK_DOWN:  velX = 0; velY = 4; useMouseControl = false; break;
                        case SDLK_LEFT:  velX = -4; velY = 0; useMouseControl = false; break;
                        case SDLK_RIGHT: velX = 4; velY = 0; useMouseControl = false; break;
                        case SDLK_SPACE:
                            paused = true; break;
                        case SDLK_r:
                            gameOver = false;
                            score = 0;
                            count_score = 0;
                            level = 0;
                            count_level = 0;
                            snake = Snake(SCREEN_WIDTH, SCREEN_HEIGHT);
                            food.randomizePosition(SCREEN_WIDTH, SCREEN_HEIGHT);
                            velX = 4;
                            velY = 0;
                            useMouseControl = false;
                            aiSnake = AIsnake(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, rand() % 4);
                            paused = false;
                            break;
                    }
                } else if (event.type == SDL_MOUSEMOTION && !gameOver && !paused) {
                    useMouseControl = true;
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                    SnakeSegment head = snake.getHead();
                    double diffX = mouseX - head.x;
                    double diffY = mouseY - head.y;
                    double length = sqrt(diffX * diffX + diffY * diffY);
                    if (length > 0) {
                        velX = (diffX / length) * 4;
                        velY = (diffY / length) * 4;
                    }
                }
            }

            if (!gameOver && !paused ) {

                snake.update(velX, velY);
                aiSnake.update(snake.getHead().x, snake.getHead().y);

                //if (snake.checkSelfCollision()) gameOver = true;

                if (snake.checkCollision(food.getX(), food.getY(), 8)) {
                    snake.grow();
                    food.randomizePosition(SCREEN_WIDTH, SCREEN_HEIGHT);
                    score++;
                    count_score++;
                    if (count_score >= 10) {
                        count_score -= 10;
                    }
                }

                if(snake.checkCollisions(aiSnake.getSegments()))
                {
                    gameOver = true;
                }
            }

            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer, texture, NULL, NULL);

            snake.draw(renderer);
            aiSnake.draw(renderer);
            food.draw(renderer);

            renderText(renderer, font, "Score: " + std::to_string(score), 20, 20);
            renderText(renderer, font, "High Score: " + std::to_string(highScore), 20, 50);
            renderText(renderer, font, "Level: " + to_string(level), 20, 80);
            renderText(renderer, font, "High Level:" + to_string(highLevel), 20, 110);


             if (paused) {
                renderText(renderer, font, "Paused", SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2);
                SDL_RenderPresent(renderer);

                /*while(SDL_PollEvent(&event)){
                    if(event.type == SDL_QUIT){
                        running = false;
                    }
                    //else
                        if (event.type == SDL_KEYDOWN){
                        switch (event.key.keysym.sym){
                            case SDLK_SPACE:
                            paused = false;
                            break;
                        }
                    }
                }*/
                while(1)
                {
                    if(SDL_PollEvent(&event)){
                    if(event.type == SDL_QUIT){
                        running = false;
                    }
                    //else
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE){

                            paused = false;
                            break;
                        }
                    }
                }
            }

            if (gameOver) {
                if(increase_level(score) == true){
                    print_level_up(renderer, font);
                    score = 20 + (level-1) * 10;
                }
                else if(increase_level(score) == false){
                    print_lose(renderer, font);
                    if(SDL_PollEvent(&event)){
                        if(event.type == SDL_QUIT){
                            running = false;
                        }
                        else if (event.type == SDL_KEYDOWN){
                            switch (event.key.keysym.sym){
                            case SDLK_y:
                                if(gameOver){
                                    gameOver = false;
                                    score = 0;
                                    count_score = 0;
                                    level = 0;
                                    count_level = 0;
                                    snake = Snake(SCREEN_WIDTH, SCREEN_HEIGHT); // Tạo snake mới
                                    food.randomizePosition(SCREEN_WIDTH, SCREEN_HEIGHT); // Tạo thức ăn mới
                                    velX = 4;
                                    velY = 0;
                                    useMouseControl = false;
                                    aiSnake = AIsnake(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, rand() % 4);
                                    paused = false;
                                    cout << "game restart" << endl;
                                }
                                else cout << "error game restart" << endl;
                                break;
                                case SDLK_n:
                                    running = false;
                                break;
                            }
                        }
                    }
                }
            }

            SDL_RenderPresent(renderer);
            SDL_Delay(8);
        }
    close(window, renderer, font, texture);
    return 0;
}
