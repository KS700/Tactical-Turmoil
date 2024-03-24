#include "Player.h"

Player::Player(const std::string& playerName) : name(playerName) {}

std::string Player::getName() const {
    return name;
}

void Player::displayInstructions() const {
    std::cout << "Welcome to Tactical Turmoil, " << name << "!" << std::endl;
    std::cout << "Instructions:" << std::endl;
    std::cout << "You are presented with a grid of squares. Some squares contain bombs (the 'mines')." << std::endl;
    std::cout << "Your goal is to uncover all squares that do not contain bombs." << std::endl;
    std::cout << "You can select a square by entering its row and column coordinates." << std::endl;
    std::cout << "If you uncover a square containing a bomb, you lose the game." << std::endl;
    std::cout << "If you uncover all safe squares without detonating any bombs, you win the game." << std::endl;
    std::cout << "You can also insert flags on suspected bomb squares to help keep track." << std::endl;
    std::cout << "Choose your difficulty level and start playing!" << std::endl;
}

Player Player::operator+(const Player& other) const {
    return Player(name + " " + other.name);
}

bool Player::operator==(const Player& other) const {
    return name == other.name;
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player: " << player.name;
    return os;
}