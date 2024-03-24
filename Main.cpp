#include "MenuFunctions.h"
#include "Player.h"
#include "GameBoard.h"
#include "Functions.h"

int main() {
    srand(time(0));
    std::vector<std::tuple<std::string, int, std::string>> scoreboard;
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    Player player(name);
    system("cls");
    int choice;
    int bombsRemaining = 0;
    std::string input;
    do {
        std::cout << "1. Start Game" << std::endl
            << "2. Instructions" << std::endl
            << "3. Scoreboard" << std::endl
            << "4. Quit Game" << std::endl;
        choice = getMenuChoice();
        system("cls");
        switch (choice) {
        case 1: {
            int difficultyChoice = getDifficultyLevel();
            handleDifficultyChoice(difficultyChoice, name, bombsRemaining, scoreboard); // Call the new function
            break;
        }
        case 2: {
            system("cls");
            player.displayInstructions();
            std::cout << "\nPress Enter to return to the main menu..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            system("cls");
            break;
        }
        case 3: {
            system("cls");
            displayScoreboard(scoreboard);
            std::cout << "\nPress Enter to return to the main menu..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            system("cls");
            break;
        }
        case 4: {
            return 0;
        }
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}