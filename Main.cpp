#include "MenuFunctions.h"
#include "Player.h"
#include "GameBoard.h"
#include "Functions.h"

int bombsRemaining = 0;                                                                     // Global Variable for tracking remaining bombs

int main() {
    std::cout << R"( 
     /$$$$$$$$                    /$$     /$$                     /$$       /$$$$$$$$                                          /$$ /$$
    |__  $$__/                   | $$    |__/                    | $$      |__  $$__/                                         |__/| $$
       | $$  /$$$$$$   /$$$$$$$ /$$$$$$   /$$  /$$$$$$$  /$$$$$$ | $$         | $$ /$$   /$$  /$$$$$$  /$$$$$$/$$$$   /$$$$$$  /$$| $$
       | $$ |____  $$ /$$_____/|_  $$_/  | $$ /$$_____/ |____  11| $$         | $$| $$  | $$ /$$__  $$| $$_  $$_  $$ /$$__  $$| $$| $$
       | $$  /$$$$$$$| $$        | $$    | $$| $$        /$$$$$1#| $$         | $$| $$  | $$| $$  \__/| $$ \ $$ \ $$| $$  \ $$| $$| $$
       | $$ /$$__  $$| $$        | $$ /$$| $$| $$       /$$__  11| $$         | $$| $$  | $$| $$      | $$ | $$ | $$| $$  | $$| $$| $$
       | $$|  $$$$$$$|  $$$$$$$  |  $$$$/| $$|  $$$$$$$|  $$$$$$$| $$         | $$|  $$$$$$/| $$      | $$ | $$ | $$|  $$$$$$/| $$| $$
       |__/ \_______/ \_______/   \___/  |__/ \_______/ \_______/|__/         |__/ \______/ |__/      |__/ |__/ |__/ \______/ |__/|__/
    )" << '\n';

    srand(time(0));                                                                         // Seed the random number generator with the current time
    std::vector<std::tuple<std::string, int, std::string>> scoreboard;                      // Vector to store player scores
    std::string name;                                                                       // Variable to store the player's name
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);                                                           // Get the player's name from the input
    std::string* namePtr = &name;                                                           // Pointer to the player's name
    Player player(namePtr);                                                                 // Create a Player object with the player's name
    system("cls");
    int choice;                                                                             // Variable to store the user's menu choice
    std::string input;                                                                      // Variable to store user input for various purposes
    
    // Main menu loop
    do {
        choice = getMenuChoice();                                                           // Get the user's menu choice
        system("cls");
        
        // Switch statement to handle different menu options
        switch (choice) {
        case 1: {
            int difficultyChoice = getDifficultyLevel();                                    // Get the difficulty level from the user
            handleDifficultyChoice(difficultyChoice, name, bombsRemaining, scoreboard);     // Call function to handle the selected difficulty level and start the game
            break;
        }
        case 2: {
            system("cls");
            player.displayInstructions();                                                   // Display game instructions to the player
            std::cout << "\nPress Enter to return to the main menu..." << std::endl;
            std::cin.ignore();                                                              // Ignore any remaining characters in the input buffer
            std::cin.get();                                                                 // Wait for the user to press Enter before continuing
            system("cls");
            break;
        }
        case 3: {
            system("cls");
            displayScoreboard(scoreboard);                                                  // Display the scoreboard to the player
            std::cout << "\nPress Enter to return to the main menu..." << std::endl;
            std::cin.ignore();                                                              // Ignore any remaining characters in the input buffer
            std::cin.get();                                                                 // Wait for the user to press Enter before continuing
            system("cls");
            break;
        }
        case 4: {
            return 0;                                                                       // Quit the game
        }
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;                  // Inform the user of an invalid choice
        }
    } while (choice != 4);                                                                  // Repeat the loop until the user chooses to exit

    return 0;
}