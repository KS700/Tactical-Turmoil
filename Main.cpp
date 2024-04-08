#include "MenuFunctions.h"
#include "Player.h"
#include "GameBoard.h"
#include "Functions.h"

int bombsRemaining = 0;                                                                     // Global Variable for tracking remaining bombs

int main() {
    std::cout << R"( 
     /1#2##1--                    /22     /**                     /2#       /1#2221--                                          /** /##
    |__  33__/                   | ##    |__/                    | #2      |__  ##__/                                         |__/| 4#
       | 1#  /1#1-11   /22#2#2# /-2#42-   /11  /---1#1-  /1#2#1- | 22         | 33 /#2   /11  /-1#111  /2#21#2/1#2#   /12#11#  /11| 3#
       | 22 |____  #2 /##_____/|_  3#_/  | 2# /11_____/ |____  11| #2         | #1| #3  | #1 /11__  #1| 2#_  #1_  22 /1#__  22| 2#| #2
       | #2  /---1#5#| 44        | #2    | #3| #1        /#1---1#| #2         | 11| 2#  | 22| #2  \__/| 22 \ 22 \ #1| 22  \ #1| #2| 22
       | 3# /11__  ##| ##        | 11 /2#| #2| 11       /12__  22| 11         | --| 12  | #1| #2      | #1 | #2 | 22| 2#  | 22| 33| 1#
       | 2#|  #1-1#32|  21-1#1-  |  -1#2/| 11|  ---1#2#|  1#1--1#| --         | --|  1#1-11/| 11      | 11 | #2 | 1#|  #2#11#/| ##| 11
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