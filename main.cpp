#include <iostream>
#include <vector>

using namespace std;

struct Tile{
    bool occupied=false;
    bool threatened=false;
};

int letterInterpreter(char letter) {
    switch (letter) {
        case 'a': return 0;
        case 'b': return 1;
        case 'c': return 2;
        case 'd': return 3;
        case 'e': return 4;
        case 'f': return 5;
        case 'g': return 6;
        case 'h': return 7;
        case 'i': return 8;
        case 'j': return 9;
        case 'k': return 10;
        case 'l': return 11;
        case 'm': return 12;
        case 'n': return 13;
        case 'o': return 14;
        case 'p': return 15;
        case 'r': return 16;
        case 's': return 17;
        case 't': return 18;
        case 'u': return 19;
        case 'w': return 20;
        case 'x': return 21;
        case 'y': return 22;
        case 'z': return 23;
        default: return -1;
    }
}

void checkForThreat(vector<vector<Tile> >& chessboard, int row, int col, const int& size, bool thread) {
    for(int i=0; i<size; ++i){
        chessboard[row][i].threatened=thread;
    }
    for(int i=0; i<size; ++i){
        chessboard[i][col].threatened=thread;
    }
    
    // lewa gorna
    for (int i=row, j=col; i>=0 && j>=0; --i, --j) {
        chessboard[i][j].threatened=thread;
    }
    // prawa gorna
    for (int i=row, j=col; i>=0 && j<size; --i, ++j) {
        chessboard[i][j].threatened=thread;
    }
    // lewa dolna
    for (int i=row, j=col; i<size && j>=0; ++i, --j) {
        chessboard[i][j].threatened=thread;
    }
    // prawa dolna
    for (int i=row, j=col; i<size && j<size; ++i, ++j) {
        chessboard[i][j].threatened=thread;
    }
}

void showChessboardWithThreat(vector<vector<Tile> >& chessboard, const int& size){
    for(int i=0; i<size; ++i){
        for(int j=0; j<size; ++j){
            if(chessboard[i][j].occupied)
                cout<<"[H]  ";
            else {
                if(chessboard[i][j].threatened)
                    cout<<"[T]  ";
                else
                    cout<<"[_]  ";
            }
        }
        cout<<endl<<endl;
    }
}

void showChessboard(vector<vector<Tile> >& chessboard, const int& size){
    for(int i=0; i<size; ++i){
        for(int j=0; j<size; ++j){
            if(chessboard[i][j].occupied)
                cout<<"[H]  ";
            else 
               cout<<"[_]  ";
        }
        cout<<endl<<endl;
    }
}

void solveBoard(vector<vector<Tile> >& chessboard, int row, int startingRow, int startingCol, const int& size, int& solutions) {
    if (row==size){
        solutions++;
        cout<<"Solution "<<solutions<<":"<<endl;
        showChessboard(chessboard, size);
        cout<<endl;
        return;
    }

    if (row==startingRow) {
        solveBoard(chessboard, row+1, startingRow, startingCol, size, solutions);
        return;
    }

    for (int col=0; col<size; ++col) {
        if (!chessboard[row][col].threatened) {
            chessboard[row][col].occupied=true;
            checkForThreat(chessboard, row, col, size, true);

            solveBoard(chessboard, row+1, startingRow, startingCol, size, solutions);

            chessboard[row][col].occupied=false;
            checkForThreat(chessboard, row, col, size, false);

            checkForThreat(chessboard, startingRow, startingCol, size, true);
            for (int i=0; i<size; ++i) {
                for (int j=0; j<size; ++j) {
                    if (chessboard[i][j].occupied)
                        checkForThreat(chessboard, i, j, size, true);
                }
            }
        }
    }
}


int main() {
    const int size=8;
    vector<vector<Tile> > chessboard(size, vector<Tile>(size));

    string choice;
    cout<<"Podaj pole w ktorym chcesz ustawic 1 hetmana: ";
    cin>>choice;

    char sizeChar = '0' + size;
    char colLetter=choice[0];
    int col=letterInterpreter(colLetter);
    int row=sizeChar-choice[1];

    if(row>=0 && row<size && col>=0 && col<size){
        cout<<"Wybrales kolumne "<<choice[0]<<" oraz rzad "<<choice[1]<<", aktualny stan tablicy: "<<endl<<endl;

        chessboard[row][col].occupied=true;
        checkForThreat(chessboard, row, col, size, true);
        showChessboardWithThreat(chessboard, size);

        int solutions = 0;
        solveBoard(chessboard, 0, row, col, size, solutions);
    }
    else
        cout<<"Sa to wartosci poza granicami szachownicy.";

    return 0;
}