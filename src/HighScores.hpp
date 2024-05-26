#ifndef HIGHSCORES_HPP
#define HIGHSCORES_HPP

#include <vector>
#include <string>

class HighScores {
public:
    HighScores();
    void update(int newScore);
    std::vector<int> getHighScores() const;
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

private:
    std::vector<int> scores;
    static const int MAX_SCORES = 5;
};

#endif // HIGHSCORES_HPP
