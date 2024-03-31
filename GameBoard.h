#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include "Square.h"
#include "GameObject.h"

// GameBoard Class - Inheritance from GameObject
class GameBoard : public GameObject {
private:
    int rows;                                   // Number of rows in the game board
    int cols;                                   // Number of columns in the game board
    int numBombs;                               // Number of bombs on the game board
    std::vector<std::vector<Square>> board;     // 2D vector representing the game board
public:
    // Constructor to initialize the GameBoard
    GameBoard(int rows, int cols, int numBombs);

    // Initialize the game board
    void initializeBoard(int numBombs);

    // Count bombs nearby a given square
    int countBombsNearby(int row, int col);

    // Print the game board
    void printBoard(int numFlags);

    // Check if the player has won the game
    bool checkWin();

    // Reveal all squares at the end of the game
    void revealAll();

    // Reveal squares - including adjacent squares without bombs
    bool revealSquares(int row, int col);

    // Insert or remove a flag on a square
    void insertFlag(int row, int col);

    // Getter method to retrieve the number of bombs on the game board
    int getNumBombs() const;

    // Virtual destructor for proper cleanup of derived class objects
    virtual ~GameBoard() {}
};

#endif // GAMEBOARD_H