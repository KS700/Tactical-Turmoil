#include "Functions.h"
#include "GameBoard.h"

void userInput(int& action, int& x, int& y) {
    bool validInput = false;
    while (!validInput) {
        std::cout << "Choose an action:\n1. Select a square\n2. Place a flag\n";
        std::cin >> action;
        if (std::cin.fail() || (action != 1 && action != 2)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid action. Please enter 1 or 2." << std::endl;
        }
        else {
            validInput = true;
        }
    }

    validInput = false;
    while (!validInput) {
        std::cout << "Enter the coordinates of the square (row): ";
        std::cin >> x;
        if (std::cin.fail() || x < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid row coordinate. Please enter a non-negative integer." << std::endl;
        }
        else {
            validInput = true;
        }
    }

    validInput = false;
    while (!validInput) {
        std::cout << "Enter the coordinates of the square (column): ";
        std::cin >> y;
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

void updateScoreboard(std::vector<std::tuple<std::string, int, std::string>>& scoreboard, const std::string& name, int score, const std::string& difficulty) {
    scoreboard.push_back(std::make_tuple(name, score, difficulty));
    std::sort(scoreboard.begin(), scoreboard.end(), [](const auto& a, const auto& b) {      //Lambda Function----------------------------------------------------------------------
        return std::get<1>(a) > std::get<1>(b);
        });
}


void displayScoreboard(const std::vector<std::tuple<std::string, int, std::string>>& scoreboard) {
    std::cout << "Scoreboard:\n";
    for (const auto& entry : scoreboard) {
        std::cout << std::get<0>(entry) << ": " << std::get<1>(entry) << " (" << std::get<2>(entry) << ")" << std::endl;
    }
}

void game(int rows, int cols, int numBombs, int& bombsRemaining, std::vector<std::tuple<std::string, int, std::string>>& scoreboard, const std::string& name, const std::string& difficulty) {
    time_t start_time = time(nullptr);
    bombsRemaining = numBombs;
    GameBoard gameBoard(rows, cols, numBombs);
    bool gameOver = false;

    while (!gameOver) {
        system("cls");
        float numFlags = 0;
        gameBoard.printBoard(numFlags);

        int x, y;
        int action;

        std::cout << std::endl << "Total Bombs: " << bombsRemaining << std::endl;

        time_t end_time = time(nullptr);
        double elapsed_time = difftime(end_time, start_time);
        std::cout << "Elapsed time: " << elapsed_time << " seconds\n";

        userInput(action, x, y);

        if (x < 0 || x >= rows || y < 0 || y >= cols) {
            std::cout << "Invalid coordinates. Please try again." << std::endl;
            continue;
        }

        switch (action) {
        case 1: {
            if (gameBoard.revealSquares(x, y)) {
                gameOver = true;
                system("cls");
                std::cout << "******KABOOM******\nYOU LOST THE GAME!" << std::endl;
                updateScoreboard(scoreboard, name, 0, difficulty);
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
            gameBoard.insertFlag(x, y);
            break;
        }
        default: {
            std::cout << "Invalid action. Please try again." << std::endl;
        }
        }
    }
    gameBoard.revealAll();
    gameBoard.printBoard(0);
    std::cout << "Press Enter to return to the main menu...";
    std::cin.ignore();
    std::cin.get();
    system("cls");
}