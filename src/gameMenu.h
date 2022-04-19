#ifndef GMENU_H
#define GMENU_H

#include <iomanip>
#include <iostream>
#include <string>

class GameMenu {
  public:
    GameMenu(){};
    ~GameMenu(){};
    void DisplayPlayerNamePrompt();
    void DisplayPlayerScore(std::string name, int score, int size);
    std::string GetPlayerName();
  private:
    std::string _playerName;
};

#endif