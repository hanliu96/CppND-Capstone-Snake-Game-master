#include "gameMenu.h"

void GameMenu::DisplayPlayerNamePrompt() {

  std::string playerName;

  std::cout << "Please enter your name: ";
  std::cin >> playerName;

  if (std::cin.fail()) {
    playerName = "<UNKNOWN>";
    std::cerr << "Wrong Input" << std::endl;
  }

  _playerName = std::move(playerName);
};

void GameMenu::DisplayPlayerScore(std::string name, int score, int size) {
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Player Name: " << name << "\n";
  std::cout << "Score: " << score << "\n";
  std::cout << "Size: " << size << "\n";
};

std::string GameMenu::GetPlayerName() {
  return _playerName;
}