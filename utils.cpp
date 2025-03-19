#include "utils.h"
#include <iostream>
#include <fstream>

const std::string HIGH_SCORE_FILE = "highscore.txt";

int loadHighScore() {
    std::ifstream file(HIGH_SCORE_FILE);
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
