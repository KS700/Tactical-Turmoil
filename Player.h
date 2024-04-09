#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "GameObject.h"

// Player Class - Inheritance from GameObject
 class Player : public GameObject {
 private:
     std::string* username; // Pointer to a string
 public:
     // Constructor
     Player(std::string* playerName);   //Function Overloading
     Player(const char* playerName);
     
     // Destructor
     ~Player();

     // Member function to get the username
     std::string getName() const;

     // Add virtual function to display instructions for the player
     virtual void displayInstructions() const;

     // Overloading the + operator to concatenate two Player names
     Player operator+(const Player& other) const;

     // Overloading the == operator to compare two Player objects
     bool operator==(const Player& other) const;

     // Overloading the << operator to print Player directly to the output stream
     friend std::ostream& operator<<(std::ostream& os, const Player& player);
 };


#endif // PLAYER_H
