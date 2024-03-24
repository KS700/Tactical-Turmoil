#include <thread>
#include "Player.h"
#include "GameBoard.h"
#include "Functions.h"

int main() {
    srand(time(0));
    std::vector<std::tuple<std::string, int, std::string>> scoreboard;
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    Player player(name); // Creating an instance of the Player class
    system("cls");
    int choice;
    int bombsRemaining = 0; // Define bombsRemaining variable
    std::string input;
    do {
        std::cout << "1. Start Game" << std::endl
            << "2. Instructions" << std::endl
            << "3. Scoreboard" << std::endl
            << "4. Quit Game" << std::endl;
        // Input validation for the menu choice
        while (true) {
            std::cout << "\nEnter your choice: ";
            std::cin >> input;
            try {
                choice = std::stoi(input);
                if (choice >= 1 && choice <= 4) {
                    break;
                }
                else {
                    std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
                }
            }
            catch (const std::exception& e) {
                std::cout << "Invalid choice. Please enter a number between 1 and 4." << std::endl;
            }
        }
        system("cls");
        switch (choice) {
        case 1: {
            int b;
            std::cout << "1. Easy" << std::endl << "2. Hard" << std::endl << "3. Good Luck" << std::endl;
            std::cin >> b;
            std::string difficulty;
            int rows, cols, numBombs; // Define rows, cols, and numBombs variables
            switch (b) {
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