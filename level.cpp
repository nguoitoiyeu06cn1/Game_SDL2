#include "level.h"
#include "menu.h"
#include <SDL.h>
#include <iostream>
using namespace std;

vector <AIsnake> aiSnakes;
int count_score = 0;
int score;
int level;
int count_level = 0;
bool hasLeveledUp = false;
bool increase_level(int score, int level_){
    int condition = 10 + level_ * 10;// cu 10 diem se co the tang level, tang muc do kho cho game
     cout << "condition: " << condition << " score: " << score << endl;
    // cout << score - condition << endl;
    if((score - condition) >= 0)
    {
       // level += 1;
        count_level = level_ + 1;
        hasLeveledUp = true;
        //cout << 1 << endl;
        return true;
    }
    else return false;
}
void createAIsnakes(int numAIsnake, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    for(int i = 0; i < numAIsnake; i++){
        int startX = rand() % SCREEN_WIDTH;
        int startY = rand() % SCREEN_HEIGHT;
        int initialDirection = rand() % 4;

        AIsnake newAisnake(startX, startY, initialDirection);

        aiSnakes.push_back(newAisnake);
    }
}
