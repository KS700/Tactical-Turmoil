#include "Functions.h"
#include "GameBoard.h"


// Function to get user input for action and coordinates
void userInput(int& action, int& x, int& y) {
    bool validInput = false;

    // Loop until valid input is received for action
    while (!validInput) {
        std::cout << "Choose an action:\n1. Select a square\n2. Place a flag\n";
        std::cin >> action;

        // Check if input is invalid
        if (std::cin.fail() || (action != 1 && action != 2)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid action. Please enter 1 or 2." << std::endl;
        }
        else {
            validInput = true;
        }
    }

    // Loop until valid input is received for row coordinate
    validInput = false;
    while (!validInput) {
        std::cout << "Enter the coordinates of the square (row): ";
        std::cin >> x;

        // Check if input is invalid
        if (std::cin.fail() || x < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid row coordinate. Please enter a non-negative integer." << std::endl;
        }
        else {
            validInput = true;
        }
    }

    // Loop until valid input is received for column coordinate
    validInput = false;
    while (!validInput) {
        std::cout << "Enter the coordinates of the square (column): ";
        std::cin >> y;

        // Check if input is invalid
        if (std::cin.fail() || y < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid column coordinate. Please enter a non-negative integer." << std::endl;
        }
        else {
            validInput = true;
        }
    }
}

// Function to update the scoreboard with the player's name, score, and difficulty level
void updateScoreboard(std::vector<std::tuple<std::string, int, std::string>>& scoreboard, const std::string& name, int score, const std::string& difficulty) {
    scoreboard.push_back(std::make_tuple(name, score, difficulty));                         // Add player's information to the scoreboard
    std::sort(scoreboard.begin(), scoreboard.end(), [](const auto& a, const auto& b) {      // Sort the scoreboard based on the score in descending order with a lambda function
        return std::get<1>(a) > std::get<1>(b);
        });
}

// Function to display the scoreboard containing player names, scores, and difficulty levels
void displayScoreboard(const std::vector<std::tuple<std::string, int, std::string>>& scoreboard) {
    std::cout << "Scoreboard:\n";
    // Iterate through the scoreboard and display each entry
    for (const auto& entry : scoreboard) {
        std::cout << std::get<0>(entry) << ": " << std::get<1>(entry) << " (" << std::get<2>(entry) << ")" << std::endl;
    }
}

// Function to run the game with specified parameters
void game(int rows, int cols, int numBombs, int& bombsRemaining, std::vector<std::tuple<std::string, int, std::string>>& scoreboard, const std::string& name, const std::string& difficulty) {
    // Initialize variables
    time_t start_time = time(nullptr);
    bombsRemaining = numBombs;
    GameBoard gameBoard(rows, cols, numBombs);
    bool gameOver = false;

    // Main game loop
    while (!gameOver) {
        system("cls");
        float numFlags = 0;
        gameBoard.printBoard(numFlags);

        int x, y;
        int action;

        // Display total bombs remaining and elapsed time
        std::cout << std::endl << "Total Bombs: " << bombsRemaining << std::endl;
        time_t end_time = time(nullptr);
        double elapsed_time = difftime(end_time, start_time);
        std::cout << "Elapsed time: " << elapsed_time << " seconds\n";

        // Get user input for action and coordinates
        userInput(action, x, y);

        // Check if coordinates are out of bounds
        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            std::cout << "Invalid coordinates. Please try again." << std::endl;
            continue;
        }

        // Handle user action
        switch (action) {
        case 1: {
            // Reveal squares and check if game is over
            if (gameBoard.revealSquares(x, y)) {
                gameOver = true;
                system("cls");
                std::cout << "******KABOOM******\nYOU LOST THE GAME!" << std::endl;
                updateScoreboard(scoreboard, name, -999999, difficulty);
            }
            else if (gameBoard.checkWin()) {
                gameOver = true;
                system("cls");
                std::cout << "*Congratulations*\nYOU WON THE GAME!" << std::endl;
                updateScoreboard(scoreboard, name, 1800 - static_cast<int>(elapsed_time), difficulty);
            }
            break;
        }
        case 2: {
            gameBoard.insertFlag(x, y);     // Insert or remove flag from square
            break;
        }
        default: {
            std::cout << "Invalid action. Please try again." << std::endl;
        }
        }
    }

    // Reveal all squares at the end of the game
    gameBoard.revealAll();
    gameBoard.printBoard(0);
    std::cout << "Press Enter to return to the main menu...";
    std::cin.ignore();
    std::cin.get();
    system("cls");
}