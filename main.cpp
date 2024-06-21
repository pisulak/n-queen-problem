#include <iostream>
#include <vector>

using namespace std;

struct Tile {
    bool occupied = false;
    bool threatened = false;
};

int letterInterpreter(char letter) {
    if (letter >= 'A' && letter <= 'Z') {
        return letter - 'A';
    } else if (letter >= 'a' && letter <= 'z') {
        return letter - 'a';
    } else {
        return -1;
    }
}

void checkForThreat(vector<vector<Tile> >& chessboard, int row, int col, const int& size, bool thread) {
    for (int i = 0; i < size; ++i) {
        chessboard[row][i].threatened = thread;
        chessboard[i][col].threatened = thread;
    }

    // Upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j) {
        chessboard[i][j].threatened = thread;
    }
    // Upper right diagonal
    for (int i = row, j = col; i >= 0 && j < size; --i, ++j) {
        chessboard[i][j].threatened = thread;
    }
    // Bottom left diagonal
    for (int i = row, j = col; i < size && j >= 0; ++i, --j) {
        chessboard[i][j].threatened = thread;
    }
    // Bottom right diagonal
    for (int i = row, j = col; i < size && j < size; ++i, ++j) {
        chessboard[i][j].threatened = thread;
    }
}

void showChessboardWithThreat(vector<vector<Tile> >& chessboard, const int& size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (chessboard[i][j].occupied) {
                cout << "[Q]  ";
            } else {
                if (chessboard[i][j].threatened) {
                    cout << "[T]  ";
                } else {
                    cout << "[_]  ";
                }
            }
        }
        cout << endl << endl;
    }
}

void showChessboard(vector<vector<Tile> >& chessboard, const int& size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (chessboard[i][j].occupied) {
                cout << "[Q]  ";
            } else {
                cout << "[_]  ";
            }
        }
        cout << endl << endl;
    }
}

void solveBoard(vector<vector<Tile> >& chessboard, int row, int startingRow, int startingCol, const int& size, int& solutions) {
    if (row == size) {
        solutions++;
        cout << "Solution " << solutions << ":" << endl;
        showChessboard(chessboard, size);
        cout << endl;
        return;
    }

    if (row == startingRow) {
        solveBoard(chessboard, row + 1, startingRow, startingCol, size, solutions);
        return;
    }

    for (int col = 0; col < size; ++col) {
        if (!chessboard[row][col].threatened) {
            chessboard[row][col].occupied = true;
            checkForThreat(chessboard, row, col, size, true);

            solveBoard(chessboard, row + 1, startingRow, startingCol, size, solutions);

            chessboard[row][col].occupied = false;
            checkForThreat(chessboard, row, col, size, false);

            checkForThreat(chessboard, startingRow, startingCol, size, true);
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    if (chessboard[i][j].occupied) {
                        checkForThreat(chessboard, i, j, size, true);
                    }
                }
            }
        }
    }
}

int main() {
    int size;
    cout << "Enter chessboard size (max 26): ";
    cin >> size;

    vector<vector<Tile> > chessboard(size, vector<Tile>(size));

    string firstQueen;
    cout << "Enter the tile that you want to put the first queen (format [A-Za-z][1-26]): ";
    cin >> firstQueen;

    char colLetter = firstQueen[0];
    int col = letterInterpreter(colLetter);
    int row = 0;

    if (firstQueen.size() == 3) {
        int firstDigit = firstQueen[1] - '0';
        int secondDigit = firstQueen[2] - '0';
        row = size - ((firstDigit * 10) + secondDigit);
    } else {
        int digit = firstQueen[1] - '0';
        row = size - digit;
    }

    if (col == -1 || row < 0 || row >= size || col < 0 || col >= size) {
        cout << "Out of bounds values.";
    } else {
        cout << "You put the queen in column " << firstQueen[0] << " and row " << firstQueen.substr(1) << ".\nChessboard now looks like this (Q - queen, T - threatened): " << endl;

        chessboard[row][col].occupied = true;
        checkForThreat(chessboard, row, col, size, true);
        showChessboardWithThreat(chessboard, size);

        int solutions = 0;
        solveBoard(chessboard, 0, row, col, size, solutions);
        if (solutions == 0) {
            cout << "No solutions for this chessboard" << endl;
        }
    }

    return 0;
}
