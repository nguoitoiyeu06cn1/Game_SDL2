#include "level.h"
#include <iostream>
using namespace std;


int count_score = 0;
int score = 0;
int level = 0;
int count_level = 0;
bool increase_level(int score){
    int condition = 20 + level * 10;
    if(score >= condition)
    {
        level += 1;
        return true;
    }
    else return false;
}
