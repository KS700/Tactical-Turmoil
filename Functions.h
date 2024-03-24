#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>

// Function to handle user input
void userInput(int& action, int& x, int& y);

// Function to update the scoreboard
void updateScoreboard(std::vector<std::tuple<std::string, int, std::string>>& scoreboard, const std::string& name, int score, const std::string& difficulty);

// Function to display the scoreboard
void displayScoreboard(const std::vector<std::tuple<std::string, int, std::string>>& scoreboard);

// Function to run the game
void game(int rows, int cols, int numBombs, int& bombsRemaining, std::vector<std::tuple<std::string, int, std::string>>& scoreboard, const std::string& name, const std::string& difficulty);

#endif // FUNCTIONS_H
