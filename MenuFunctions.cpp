#include <thread>
#include "GameBoard.h"
#include "Functions.h"
#include "MenuFunctions.h"

int getMenuChoice() {
    int choice;
    while (true) {
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("cls");
            std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
        } else {
            break;
        }
    }
    return choice;
}

int getDifficultyLevel() {
    int level;
    while (true) {
        std::cout << "1. Easy\n2. Hard\n3. Good Luck\n";
        std::cin >> level;
        if (std::cin.fail() || level < 1 || level > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("cls");
            std::cout << "Invalid input. Please enter a number between 1 and 3." << std::endl;
        } else {
            break;
        }
    }
    return level;
}

void handleDifficultyChoice(int difficultyChoice, const std::string& name, int& bombsRemaining, std::vector<std::tuple<std::string, int, std::string>>& scoreboard) {
    std::string difficulty;
    int rows, cols, numBombs;
    switch (difficultyChoice) {
        case 1: {
            difficulty = "E";
            rows = 10;
            cols = 10;
            numBombs = 10;
            std::thread gameThread(game, rows, cols, numBombs, std::ref(bombsRemaining), std::ref(scoreboard), name, difficulty);
            gameThread.join();
            break;
        }
        case 2: {
            difficulty = "H";
            rows = 16;
            cols = 16;
            numBombs = 40;
            std::thread gameThread2(game, rows, cols, numBombs, std::ref(bombsRemaining), std::ref(scoreboard), name, difficulty);
            gameThread2.join();
            break;
        }
        case 3: {
            difficulty = "GL";
            rows = 30;
            cols = 30;
            numBombs = 180;
            std::thread gameThread3(game, rows, cols, numBombs, std::ref(bombsRemaining), std::ref(scoreboard), name, difficulty);
            gameThread3.join();
            break;
        }
    }
}