#include <thread>
#include "GameBoard.h"
#include "Functions.h"
#include "MenuFunctions.h"

// Function to prompt the user for menu choice
int getMenuChoice() {
    signed int choice;
    
    // Loop until a valid choice is entered
    while (true) {
        // Display the menu options
        std::cout << "1. Start Game" << std::endl << "2. Instructions" << std::endl << "3. Scoreboard" << std::endl << "4. Quit Game" << std::endl;
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        // Validate the input
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

// Function to prompt the user for the game difficulty level
int getDifficultyLevel() {
    int level;
    // Loop until a valid level is entered
    while (true) {
        // Display the difficulty options
        std::cout << "1. Easy\n2. Hard\n3. Good Luck\n";
        std::cin >> level;
        
        // Validate the input
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

// Function to handle the user's choice of game difficulty
void handleDifficultyChoice(int difficultyChoice, const std::string& name, int& bombsRemaining, std::vector<std::tuple<std::string, int, std::string>>& scoreboard) {
    std::string difficulty;
    int rows, cols, numBombs;

    // Determine the game parameters based on the selected difficulty level
    switch (difficultyChoice) {
        case 1: {
            difficulty = "E";
            rows = 10;
            cols = 10;
            numBombs = 10;
            // Create a thread to start the game with the chosen parameters
            std::thread gameThread(game, rows, cols, numBombs, std::ref(bombsRemaining), std::ref(scoreboard), name, difficulty);
            gameThread.join();  // Wait for the game thread to finish execution
            break;
        }
        case 2: {
            difficulty = "H";
            rows = 16;
            cols = 16;
            numBombs = 40;
            // Create a thread to start the game with the chosen parameters
            std::thread gameThread2(game, rows, cols, numBombs, std::ref(bombsRemaining), std::ref(scoreboard), name, difficulty);
            gameThread2.join(); // Wait for the game thread to finish execution
            break;
        }
        case 3: {
            difficulty = "GL";
            rows = 30;
            cols = 30;
            numBombs = 180;
            // Create a thread to start the game with the chosen parameters
            std::thread gameThread3(game, rows, cols, numBombs, std::ref(bombsRemaining), std::ref(scoreboard), name, difficulty);
            gameThread3.join(); // Wait for the game thread to finish execution
            break;
        }
    }
}