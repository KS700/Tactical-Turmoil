// AERSP 424 Final Project - Tactical Turmoil
// Keegan Scott, Bhavya Patel, Garrett Varvil

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

//Initialize Difficulties (Board Size + # of bombs)
const int EASY_ROWS = 10;
const int EASY_COLS = 10;
const int EASY_BOMBS = 10;
int bombsRemaining = 10;

const int HARD_ROWS = 16;
const int HARD_COLS = 16;
const int HARD_BOMBS = 40;

const int VERY_HARD_ROWS = 16;
const int VERY_HARD_COLS = 40;
const int VERY_HARD_BOMBS = 99;

// Struct-------------------------------------------------------------------------------------------------------------------------------
struct Square {
    bool bomb;
    bool revealed;
    bool flagged;
    int bombsNearby;
};

// Display the selected board size
void printBoard(const vector<vector<Square>>& board, int numBombs, int numFlags) {
    cout << "   ";
    for (int col = 0; col < board[0].size(); col++) {
        cout << col << " ";
    }
    cout << endl;
    for (int row = 0; row < board.size(); row++) {
        cout << row << " |";
        for (int col = 0; col < board[row].size(); col++) {
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
            cout << c << "|";
        }
        cout << endl;
    }
}

// Check if the player has beat the game
bool checkWin(const vector<vector<Square>>& board, int numBombs) {
    int numFlags = 0;
    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board[row].size(); col++) {
            if (!board[row][col].revealed && !board[row][col].flagged) {
                return false;
            }
            if (board[row][col].flagged) {
                numFlags++;
            }
        }
        return true;
    }
}

void revealAll(vector<vector<Square>>& board) {
    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board[row].size(); col++) {
            board[row][col].revealed = true;
        }
    }
}

// Determine the number of bombs next to the selected block
int countBombsNearby(const vector<vector<Square>>& board, int row, int col) {
    const int dr[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    const int dc[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int r = row + dr[i];
        int c = col + dc[i];
        if (r >= 0 && r < board.size() && c >= 0 && c < board[r].size()) {
            if (board[r][c].bomb) {
                count++;
            }
        }
    }
    return count;
}

// Action to occur to the selected square depending on what is there
bool revealSquares(vector<vector<Square>>& board, int row, int col) {
    if (row < 0 || row >= board.size() || col < 0 || col >= board[row].size()) {
        return false;
    }
    Square& square = board[row][col];
    if (square.flagged || square.revealed) {
        return false;
    }
    square.revealed = true;
    if (square.bomb) {
        bombsRemaining = bombsRemaining - 1;
        cout << "KABOOM\n";
        return true;
    }
    if (square.bombsNearby > 0) {
        return false;
    }
    const int dr[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    const int dc[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    for (int i = 0; i < 8; i++) {
        int r = row + dr[i];
        int c = col + dc[i];
        if (r >= 0 && r < board.size() && c >= 0 && c < board[r].size() && board[r][c].flagged) {
            if (board[r][c].bomb) {
                return true;
            }
        }
        else {
            revealSquares(board, r, c);
        }
    }
    return false;
}

// Decrease the bomb counter and change the square to be flagged when a flag is placed
void insertFlag(vector<vector<Square>>& board, int row, int col) {
    Square& square = board[row][col];
    if (!square.revealed) {
        square.flagged = !square.flagged;
    }
    if (square.bomb) {
        bombsRemaining = bombsRemaining - 1;
    }
}

// Initialize the board size
void initializeBoard(vector<vector<Square>>& board, int numBombs) {
    int count = 0;
    while (count < numBombs) {
        int row = rand() % board.size();
        int col = rand() % board[row].size();
        if (!board[row][col].bomb) {
            board[row][col].bomb = true;
            count++;
        }
    }
    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board[row].size(); col++) {
            board[row][col].bombsNearby = countBombsNearby(board, row, col);
        }
    }
}

// Run the game?------------------------------------------------------------------------------------------------------------------------------
void game(int rows, int cols, int numBombs) {
    time_t start_time = time(nullptr);
    vector<vector<Square>> board(rows, vector<Square>(cols));
    initializeBoard(board, numBombs);
    bool gameOver = false;
    while (!gameOver) {
        system("cls");
        int numFlags = 0;
        for (int row = 0; row < board.size(); row++) {
            for (int col = 0; col < board[row].size(); col++) {
                if (board[row][col].flagged) {
                    numFlags++;
                }
            }
        }
        printBoard(board, numBombs, numFlags);
        
        int x, y;
        int action;
        
        cout << endl << "Bombs remaining: " << bombsRemaining << endl;
        
        time_t end_time = time(nullptr);
        
        double elapsed_time = difftime(end_time, start_time);
        cout << "Elapsed time: " << elapsed_time << " seconds\n";
        cout << "Choose an action:" << endl;
        cout << "1. Choose a unit" << endl;
        cout << "2. Insert a flag" << endl;
        cin >> action;
        cout << "Enter the coordinates of the square (row): ";
        cin >> x;
        cout << "Enter the coordinates of the square (column): ";
        cin >> y;
        if (x < 0 || x >= board.size() || y < 0 || y >= board[x].size()) {
            cout << "Invalid coordinates. Please try again." << endl;
            continue;
        }
        switch (action) {  //Need to check here why I am able to win by not beating the game---------------------------------------------------------
        case(1): {
            if (revealSquares(board, x, y)) {
                gameOver = true;
                cout << "YOU LOST THE GAME!" << endl;
            }
            else if (checkWin(board, numBombs)) {
                gameOver = true;
                cout << "YOU WIN THE GAME!" << endl;
            }
            break;
        }
        case(2): {
            {
                insertFlag(board, x, y);
            }
            break;
        }
        default:
        {
            cout << "Invalid action. Please try again." << endl;
        }
        }

    }
    revealAll(board); // Does not work currently-----------------------------------------------------------------------------------------------
}


int main() {
    srand(time(0));
    ofstream records("records.txt", ios_base::app);
    string name;
    cout << "enter your name: ";
    cin >> name;
    system("cls");
    cout << "1.Start Game" << endl << "2.Quit" << endl << "3.Records" << endl << "4.Instructions" << endl;
    int a, b;
    string output;
    cin >> a;
    system("cls");
    switch (a) {
    case (1): {
        cout << "1.Easy" << endl << "2.Hard" << endl << "3.Good Luck" << endl;
        cin >> b;
        switch (b) {
        case (1): {
            game(EASY_ROWS, EASY_COLS, EASY_BOMBS);
            records << name << " " << bombsRemaining << "/" << 10 << endl;
            records.close();
            break;
        }
        case (2): {
            bombsRemaining += 30;
            game(HARD_ROWS, HARD_COLS, HARD_BOMBS);
            records << name << " " << bombsRemaining << "/" << 40 << endl;
            records.close();
            break;
        }
        case (3): {
            bombsRemaining += 89;
            game(VERY_HARD_ROWS, VERY_HARD_COLS, VERY_HARD_BOMBS);
            records << name << " " << bombsRemaining << "/" << 99 << endl;
            records.close();
            break;
        }
        }
    }
    case(2): {
        return 0;
        break;
    }
    case(3): {
        system("cls");
        ifstream records("records.txt");
        while (getline(records, output)) {
            cout << output << endl;
        }
        break;
    }
    //case(4): {
    //    system("cls");
    //    ifstream instructions(".txt");
    //       // Case 4 for Instructions-------------------------------------------------------------------------------------------------------
    //       // Use Pointer to Name given and say "Hi .... Here are the instructions for Tactical Turmoil"
    //}
    }
}

