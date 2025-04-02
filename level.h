#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <iostream>
#include "utils.h"
#include "AIsnake.h"
#include "menu.h"
#include "graphics.h"

extern vector <AIsnake> aiSnakes;
extern int count_score;
extern int score;
extern int level;
extern bool hasLeveledUp;// kiem tra len cap dung voi cap do
extern int count_level;
bool increase_level(int score_prerent, int level_prerent);

void createAIsnakes(int numAIsnake, int SCREEN_WIDTH, int SCREEN_HEIGHT);




#endif // LEVEL_H_INCLUDED
