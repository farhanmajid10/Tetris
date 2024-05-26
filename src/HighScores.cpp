#include "HighScores.hpp"
#include <algorithm>
#include <fstream>
#include <iterator>

HighScores::HighScores() {}

void HighScores::update(int newScore) {
    scores.push_back(newScore);
    std::sort(scores.begin(), scores.end(), std::greater<int>());
    if (scores.size() > MAX_SCORES) {
        scores.resize(MAX_SCORES);
    }
}

std::vector<int> HighScores::getHighScores() const {
    return scores;
}

void HighScores::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        int score;
        scores.clear();
        while (file >> score) {
            scores.push_back(score);
        }
        std::sort(scores.begin(), scores.end(), std::greater<int>());
        if (scores.size() > MAX_SCORES) {
            scores.resize(MAX_SCORES);
        }
        file.close();
    }
}

void HighScores::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int score : scores) {
            file << score << std::endl;
        }
        file.close();
    }
}
