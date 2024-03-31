#include "GameBoard.h"

// Constructor for GameBoard class
GameBoard::GameBoard(int rows, int cols, int numBombs) : rows(rows), cols(cols), numBombs(numBombs), board(rows, std::vector<Square>(cols)) {
    initializeBoard(numBombs);
}

// Initialize the game board
void GameBoard::initializeBoard(int numBombs) {
    // Seed random number generator (Different game boards)
    srand(static_cast<unsigned int>(time(nullptr)));       
    int count = 0;
    
    // Randomly place bombs on the board
    while (count < numBombs) {
        int row = rand() % rows;
        int col = rand() % cols;
        if (!board[row][col].bomb) {
            board[row][col].bomb = true;
            count++;
        }
    }

    // Calculate and set the number of bombs nearby each square
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            board[row][col].bombsNearby = countBombsNearby(row, col);
        }
    }
}

// Count the number of bombs nearby a given square
int GameBoard::countBombsNearby(int row, int col) {
    // Lambda function to check if a position is valid
    auto isValidPosition = [this](int r, int c) {
        return r >= 0 && r < rows && c >= 0 && c < cols;
        };

    // Offsets for neighboring squares
    const int dr[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    const int dc[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    
    // Count the number of bombs nearby
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int r = row + dr[i];
        int c = col + dc[i];
        if (isValidPosition(r, c) && board[r][c].bomb) {
            count++;
        }
    }
    return count;
}

// Print the game board
void GameBoard::printBoard(int numFlags) {
    // Determine the width for formatting
    int width = std::to_string(cols - 1).size();
    std::cout << "   ";
    if (rows > 10 || cols > 10) {
        std::cout << " ";
    }
    
    // Print column numbers
    for (int col = 0; col < cols; col++) {
        std::cout << std::setw(width) << col << " ";
    }
    std::cout << std::endl;

    // Print the game board
    for (int row = 0; row < rows; row++) {
        std::cout << std::setw(width) << row << " |";
        for (int col = 0; col < cols; col++) {
            char c;
            if (!board[row][col].revealed) {
                c = ' ';
            }
            else if (board[row][col].bomb) {
                c = '*';
            }
            else if (board[row][col].bombsNearby > 0) {
                c = '0' + board[row][col].bombsNearby;
            }
            else {
                c = '-';
            }
            if (board[row][col].flagged) {
                c = '#';
            }
            std::cout << std::setw(width) << c << "|";
        }
        std::cout << std::endl;
    }
}

// Check if the player has won the game
bool GameBoard::checkWin() {
    int unrevealedSafeSquares = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (!board[row][col].revealed && !board[row][col].bomb) {
                unrevealedSafeSquares++;
            }
        }
    }
    return unrevealedSafeSquares == 0;
}

// Reveal all squares at the end of the game
void GameBoard::revealAll() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            board[row][col].revealed = true;
        }
    }
}

// Method to reveal squares
bool GameBoard::revealSquares(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }
    Square& square = board[row][col];
    if (square.flagged || square.revealed) {
        return false;
    }
    square.revealed = true;
    if (square.bomb) {
        return true;
    }
    if (square.bombsNearby > 0) {
        return false;
    }

    // Offsets for neighboring squares
    std::array<int, 8> dr = { -1, -1, -1, 0, 0, 1, 1, 1 };
    std::array<int, 8> dc = { -1, 0, 1, -1, 1, -1, 0, 1 };

    // Recursively reveal neighboring squares
    for (int i = 0; i < 8; i++) {
        int r = row + dr[i];
        int c = col + dc[i];
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            if (revealSquares(r, c) && !board[r][c].flagged) {
                return true;
            }
        }
    }
    return false;
}

// Insert or remove a flag on a square
void GameBoard::insertFlag(int row, int col) {
    Square& square = board[row][col];
    if (!square.revealed) {
        square.flagged = !square.flagged;
    }
}