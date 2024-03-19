// AERSP 424 Final Project - Tactical Turmoil
// Keegan Scott, Bhavya Patel, Garrett Varvil

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <time.h>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;

//Initialize Difficulties (Board Size + # of bombs)
const int EASY_ROWS = 10;
const int EASY_COLS = 10;
const int EASY_BOMBS = 10;
int bombsRemaining = 10;

const int HARD_ROWS = 16;
const int HARD_COLS = 16;
const int HARD_BOMBS = 40;

const int VERY_HARD_ROWS = 30;
const int VERY_HARD_COLS = 30;
const int VERY_HARD_BOMBS = 180;

// Struct------------------------ADD more classes/structs-------------------------------------------------------------------------------------------------------
struct Square {
    bool bomb;
    bool revealed;
    bool flagged;
    int bombsNearby;
};

// Function to update the scoreboard-------------------------------------------Record diffculty as well------------------------------------------
void updateScoreboard(vector<pair<string, int>>& scoreboard, const string& name, int score) {
    scoreboard.push_back(make_pair(name, score));
    sort(scoreboard.begin(), scoreboard.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
        });
}

// Display the selected board size
void printBoard(const vector<vector<Square>>& board, int numBombs, int numFlags) {
    int width = to_string(board[0].size() - 1).size(); // Calculate the width dynamically based on the number of columns
    cout << "   ";
    if (board.size() > EASY_ROWS || board[0].size() > EASY_COLS) {
        cout << " "; // Extra space before the first column number for larger boards
    }
    for (int col = 0; col < board[0].size(); col++) {
        cout << setw(width) << col << " "; // Set the width dynamically
    }
    cout << endl;
    for (int row = 0; row < board.size(); row++) {
        cout << setw(width) << row << " |";
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
            cout << setw(width) << c << "|"; // Set the width dynamically
        }
        cout << endl;
    }
}

// Check if the player has beat the game
bool checkWin(const vector<vector<Square>>& board, int numBombs) {
    unsigned int numFlags = 0;
    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board[row].size(); col++) {
            if (!board[row][col].revealed && !board[row][col].flagged) {
                return false;
            }
            if (board[row][col].flagged) {
                numFlags++;
            }
        } 
    }
    return true;
}

// Reveal the board at the end of a game
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
        system("cls");
        cout << "******KABOOM******\n";
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
    // Game breaking "feature" -> Flag a bomb and the number decreases, you can flag every tile to find them--------------------------------------------------
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
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator
    signed int count = 0;
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


// Function to handle user input
void userInput(int& action, int& x, int& y) {
    cout << "Choose an action:" << endl;
    cout << "1. Choose a unit" << endl;
    cout << "2. Insert a flag" << endl;
    cin >> action;
    cout << "Enter the coordinates of the square (row): ";
    cin >> x;
    cout << "Enter the coordinates of the square (column): ";
    cin >> y;
}

// Display and make a scoreboard-------------------------------------------------------------------------------------------------------------------
void displayScoreboard(const vector<pair<string, int>>& scoreboard) {
    cout << "Scoreboard:\n";
    for (const auto& entry : scoreboard) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

// Run the game
void game(int rows, int cols, int numBombs, int& bombsRemaining, vector<pair<string, int>>& scoreboard, const string& name) {
    time_t start_time = time(nullptr);
    bombsRemaining = numBombs;
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

        userInput(action, x, y);

        if (x < 0 || x >= board.size() || y < 0 || y >= board[x].size()) {
            cout << "Invalid coordinates. Please try again." << endl;
            continue;
        }

        switch (action) {
        case 1: {
            if (revealSquares(board, x, y)) {
                gameOver = true;
                cout << "YOU LOST THE GAME!" << endl;
                updateScoreboard(scoreboard, name, 0);
            }
            else if (checkWin(board, numBombs)) {
                gameOver = true;
                system("cls");
                cout << "*Congratulations*\nYOU WON THE GAME!" << endl;
                updateScoreboard(scoreboard, name, static_cast<int>(elapsed_time));
            }
            break;
        }
        case 2: {
            insertFlag(board, x, y);
            break;
        }
        default: {
            cout << "Invalid action. Please try again." << endl;
        }
        }
    }
    revealAll(board); // Reveals all squares after the game ends
    printBoard(board, numBombs, 0); // Print the final board with all squares revealed
    cout << "Press Enter to return to the main menu...";
    cin.ignore(); // Ignore any previous newline characters
    cin.get(); // Wait for the user to press Enter
    system("cls");
}


int main() {
    srand(time(0));
    vector<pair<string, int>> scoreboard;
    string name;
    cout << "Enter your name: ";
    cin >> name;
    system("cls");
    int choice;
    do {
        cout << "1. Start Game" << endl
             << "2. Instructions" << endl
             << "3. Scoreboard" << endl
             << "4. Quit Game" << endl;
        cin >> choice;
        system("cls");
        switch (choice) {
        case 1: {
            int b;
            cout << "1. Easy" << endl << "2. Hard" << endl << "3. Good Luck" << endl;
            cin >> b;
            string difficulty;
            switch (b) {
            case 1: {
                difficulty = "E";
                thread gameThread(game, EASY_ROWS, EASY_COLS, EASY_BOMBS, ref(bombsRemaining), ref(scoreboard), name);
                gameThread.join();
                break;
            }
            case 2: {
                difficulty = "H";
                thread gameThread2(game, HARD_ROWS, HARD_COLS, HARD_BOMBS, ref(bombsRemaining), ref(scoreboard), name);
                gameThread2.join();
                break;
            }
            case 3: {
                difficulty = "GL";
                thread gameThread3(game, VERY_HARD_ROWS, VERY_HARD_COLS, VERY_HARD_BOMBS, ref(bombsRemaining), ref(scoreboard), name);
                gameThread3.join();
                break;
            }
            }
            break;
        }
        case 2: { //Need to write detailed instructions-------------------------------------------------------------------------------------------------------
                  //Pointer to username for Welcome instructions vvvvv
            system("cls");
            cout << "Welcome to Tactical Turmoil, *NAME HERE*!" << endl;
            cout << "Instructions:" << endl;
            cout << "You are presented with a grid of squares. Some squares contain bombs (the 'mines')." << endl;
            cout << "Your goal is to uncover all squares that do not contain bombs." << endl;
            cout << "You can select a square by entering its row and column coordinates." << endl;
            cout << "If you uncover a square containing a bomb, you lose the game." << endl;
            cout << "If you uncover all safe squares without detonating any bombs, you win the game." << endl;
            cout << "You can also insert flags on suspected bomb squares to help keep track." << endl;
            cout << "Choose your difficulty level and start playing!" << endl;
            cout << "\nPress Enter to return to the main menu..." << endl;
            cin.ignore(); 
            cin.get();
            system("cls");
            break;
        }
        case 3: { //Scoreboard needs units an difficulty--------Seconds (E)---------------------------------------------------------------------------------------------------------------
            system("cls");
            displayScoreboard(scoreboard);
            cout << "\nPress Enter to return to the main menu..." << endl;
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
        case 4: {
            return 0;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}