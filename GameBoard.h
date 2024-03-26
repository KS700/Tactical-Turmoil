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

class GameBoard : public GameObject {
private:
    int rows;
    int cols;
    int numBombs;
    std::vector<std::vector<Square>> board;
public:
    GameBoard(int rows, int cols, int numBombs);

    // Method to initialize the game board
    void initializeBoard(int numBombs);

    // Method to count bombs nearby a given square
    int countBombsNearby(int row, int col);

    // Method to print the game board
    void printBoard(int numFlags);

    // Method to check if the player has won the game
    bool checkWin();

    // Method to reveal all squares at the end of the game
    void revealAll();

    // Method to reveal squares recursively
    bool revealSquares(int row, int col);

    // Method to insert or remove a flag on a square
    void insertFlag(int row, int col);

    // Getter method for number of bombs
    int getNumBombs() const;

    // Virtual destructor------------------------------------------------------------------------------------------------------------
    virtual ~GameBoard() {}
};

#endif // GAMEBOARD_H