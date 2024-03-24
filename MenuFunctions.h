#ifndef MENU_FUNCTIONS_H
#define MENU_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <limits>

// Function to get user input for chosen difficulty
void handleDifficultyChoice(int difficultyChoice, const std::string& name, int& bombsRemaining, std::vector<std::tuple<std::string, int, std::string>>& scoreboard);

// Function to get user input for the menu choice
int getMenuChoice();

// Function to get user input for difficulty level
int getDifficultyLevel();

#endif // MENU_FUNCTIONS_H
