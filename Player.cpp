#include "Player.h"

// Constructor
Player::Player(std::string* playerName) : username(playerName) {}

// Destructor
Player::~Player() {}

// Function to get the username
std::string Player::getName() const {
    return *username;
}

// Function to display instructions
void Player::displayInstructions() const {
    std::cout << "Welcome to Tactical Turmoil, " << *username << "!" << std::endl;
    std::cout << "Here are the instructions that will get you out alive:\n" << std::endl;
    std::cout << "1. Before starting a game, you will need to pick between 3 difficulties that\n   scale the size of the board and the total number of bombs you must avoid." << std::endl;
    std::cout << "\n2. The board will be easily navigable due to numbered rows and columns,\n   and these numbers will be used as your inputs while playing." << std::endl;
    std::cout << "\n3. To get started, you must pick a starting space on the board.\n   While this space is not always safe, trust your gut and you will be just fine." << std::endl;
    std::cout << "\n4. To actually input the tile you would like to start on, enter the number (1) then follow the on screen instructions to enter the row and column of your choice.\n   To play quicker, you may enter your selections all in one line using spaces to separate the numbers (Example input: 1 5 13)." << std::endl;
    std::cout << "\n5. After your first tile is chosen, the board will be updated to show you what is around your space.\n   Clear tiles will be identified with (-) and any tiles that are within one block of a bomb in any direction will be\n   displayed with a number between 1-8 which means there are that many bombs in the direct vicinity of that tile." << std::endl;
    std::cout << "\n6. If you do not want to reveal a square every turn, place a flag (#) on tiles that you suspect a bomb could be hiding.\n   To do this, enter the number (2) then follow the on screen instructions to enter the row and column of your choice.\n   To play quicker, the same rules apply as in Step 4 (Example input: 2 6 8)." << std::endl;
    std::cout << "\n7. So, what happens if you accidentally select a bomb? KABOOM, your game is over.\n   You can win by navigating the entire board and uncovering every tile that is not hiding a bomb." << std::endl;
    std::cout << "\nGood luck out there soldier!" << std::endl;
}

// Overloading the + operator to concatenate two Player names
Player Player::operator+(const Player& other) const {
    std::string newName = *username + " " + *other.username;
    return Player(&newName);
}

// Overloading the == operator to compare two Player objects
bool Player::operator==(const Player& other) const {
    return *username == *other.username;
}

// Overloading the << operator to print Player directly to the output stream
std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player: " << *player.username;
    return os;
}