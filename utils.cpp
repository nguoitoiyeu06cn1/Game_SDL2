#include "utils.h"
#include <iostream>
#include <fstream>

using namespace std;
const string HIGH_SCORE_FILE = "text/highscore.txt";
const string HIGH_LEVEL_FILE = "text/level.txt";

int loadHighScore() {
    ifstream file(HIGH_SCORE_FILE);
    int highScore = 0;
    if (file.is_open()) {
        file >> highScore;
        file.close();
    } else {
        std::cerr << "Error opening high score file for reading." << std::endl;
    }
    return highScore;
}

void saveHighScore(int score) {
    int highScore = loadHighScore();
    if (score > highScore) {
        std::ofstream file(HIGH_SCORE_FILE);
        if (file.is_open()) {
            file << score;
            file.close();
        } else {
            std::cerr << "Error opening high score file for writing." << std::endl;
        }
    }
}
int loadLevel(){
    ifstream file(HIGH_LEVEL_FILE);
    int highLevel = 0;
    if(file.is_open()){
        file >> highLevel;
        file.close();
    } else {
        cout << "Error opening high level file for reading" << endl;
    }
    return highLevel;
}
void saveHighLevel(int level){
    int highLevel = loadLevel();
    if(level > highLevel){
        ofstream file(HIGH_LEVEL_FILE);
        if(file.is_open()){
            file << level;
            file.close();
        }
        else {
            cout << "Error opening high level file for writing" << endl;
        }
    }
}
