#include "Player.h"

// Constructor
Player::Player(std::string* playerName) : username(playerName) {}

// Destructor
Player::~Player() {}

// Member function to get the username
std::string Player::getName() const {
    return *username;
}

// Member function to display instructions
void Player::displayInstructions() const {
    std::cout << "Welcome to Tactical Turmoil, " << *username << "!" << std::endl;
    std::cout << "Instructions:" << std::endl;
    std::cout << "You are presented with a grid of squares. Some squares contain bombs (the 'mines')." << std::endl;
    std::cout << "Your goal is to uncover all squares that do not contain bombs." << std::endl;
    std::cout << "You can select a square by entering its row and column coordinates." << std::endl;
    std::cout << "If you uncover a square containing a bomb, you lose the game." << std::endl;
    std::cout << "If you uncover all safe squares without detonating any bombs, you win the game." << std::endl;
    std::cout << "You can also insert flags on suspected bomb squares to help keep track." << std::endl;
    std::cout << "Choose your difficulty level and start playing!" << std::endl;
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