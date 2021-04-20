//
//  main.cpp
//  ttt
//
//  Created by Joseph Gu on 4/16/21.
//

#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

class GameStatus {
    bool gameOver;
    int nodeValue;
  public:
    GameStatus(bool gameOver_, int nodeValue_) {
        gameOver = gameOver_;
        nodeValue = nodeValue_;
    }
    void setGameOver (bool gameOver_) {
        gameOver = gameOver_;
    }
    void setGameOver (int nodeValue_) {
        nodeValue = nodeValue_;
    }
    int getNodeValue() {return nodeValue;}
    int getGameOver() {return gameOver;}
};

void updategrid (int r, char c, char grid[3][3], char playerinput) {
    if (c == 'a') {
        grid [r-1][0] = playerinput;
    } else if (c == 'b') {
        grid [r-1][1] = playerinput;
    } else if (c == 'c') {
        grid [r-1][2] = playerinput;
    }
}

void printgrid (char grid[3][3]) {
    cout << "-------\n";
    cout << "|"<< grid[0][0]<<"|" <<grid[0][1] << "|" << grid[0][2] << "| \n";
    cout << "-------\n";
    cout << "|"<< grid[1][0]<<"|" <<grid[1][1] << "|" << grid[1][2] << "| \n";
    cout << "-------\n";
    cout << "|"<< grid[2][0]<<"|" <<grid[2][1] << "|" << grid[2][2] << "| \n";
    cout << "-------\n";
}

GameStatus* checkGameOver (char grid[3][3]) {
    for (int i = 0; i < 3; i++) { //check rows
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] )
        {
            if (grid[i][2] == 'o') {
                return new GameStatus(true, -1);
            }
            if (grid[i][2] == 'x') {
                return new GameStatus(true ,1);
        }
    }
    }
    for (int i = 0; i < 3; i++) { // check columns
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) {
            if (grid[0][i] == 'o') {
                return new GameStatus(true, -1);
            }
            if (grid[0][i] == 'x') {
                return new GameStatus(true ,1);
        }
        }
    }
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
            if (grid[2][2] == 'o') {
                return new GameStatus(true, -1);
            }
            if (grid[2][2] == 'x') {
                return new GameStatus(true ,1);
        }
    }
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
            if (grid[1][1] == 'o') {
                return new GameStatus(true, -1);
            }
            if (grid[1][1] == 'x') {
                return new GameStatus(true ,1);
        }
    }
    if (grid[0][0] != ' ' && grid[0][1] != ' ' && grid[0][2] != ' ' && // tie situation
        grid[1][0] != ' ' && grid[1][1] != ' ' && grid[0][2] != ' ' &&
        grid[2][0] != ' ' && grid[2][1] != ' ' && grid[0][2] != ' '
        ) {
        return new GameStatus(true, 0.5);
    }
    return new GameStatus (false, 2); // return this if the game is not done, hopefully that int of 2 does not get used
}



int minimax (char grid[3][3], bool isAI, int step) {
    GameStatus *pGameStatus = checkGameOver(grid); /*check game over, if over, return the terminal node value*/
    static int newR, newC;
    bool gameOver = pGameStatus->getGameOver();
    int value = pGameStatus->getNodeValue();
    delete pGameStatus;
    if (gameOver) {
        return value;
    }
    if (isAI== true) {
        //iterate through possible moves, need coords of unused squares, double for loop, create new grid with move and minimax again
        int maxNode = -2;
        for (int r=0; r<3; r++){
            for (int c=0; c<3; c++) {
            if (grid[r][c] == ' ') {
                char grid2[3][3];
                for (int r2=0; r2<3; r2++) { // for loop copies old grid to new grid
                    for (int c2=0; c2<3; c2++) {
                        grid2[r2][c2] = grid[r2][c2];
                    }
                }
                grid2[r][c] = 'x'; // copies the new node to new grid
                int newNode = minimax (grid2, false, step+1);
                if (newNode > maxNode) {
                    maxNode = newNode;
                    if (step == 1) {
                        newR = r;
                        newC = c;
                    }
                }
        }
            }
        }
        if (step == 1) {
            grid[newR][newC] = 'x';
        }
        return maxNode;
    }
    if (isAI == false) {
        //iterate through possible moves, need coords of unused squares, double for loop, create new grid with move and minimax again
        int minNode = 2;
        for (int r=0; r<3; r++){
            for (int c=0; c<3; c++) {
            if (grid[r][c] == ' ') {
                char grid2[3][3];
                for (int r2=0; r2<3; r2++) { // for loop copies old grid to new grid
                    for (int c2=0; c2<3; c2++) {
                        grid2[r2][c2] = grid[r2][c2];
                    }
                }
                grid2[r][c] = 'o'; // copies the new node to new grid
                int newNode = minimax (grid2, true, step++);
                minNode = min(newNode, minNode);
            }
        }
        }
        return minNode;
    }
    return 0;
}

int main() {
    string input;
    int row;
    char column;
    char grid [3][3] = {' ',' ',' ',' ','x',' ',' ',' ',' '};
    char playerinput; // if O, the input was player, if X, it was from the AI
    cout << "Welcome to unbeatable Tic-Tac-Toe! The rows top to bottom are numbered 1-2-3, the columns from left to right are a-b-c. Thus 2b is the middle square \n";
    printgrid (grid);
    while (true) {
        cout << "Make your move: ";
        getline (cin, input);
        if (input == "2b") {
            cout << "hey cut that out \n";
            continue;
        }
        row = int (input[0]) - 48;
        column = input[1];
        updategrid (row, column, grid, 'o');
        printgrid (grid);
        if (checkGameOver(grid)->getGameOver()) {
             cout << "u won congrats \n";
            break;
         };
        cout << "Press enter to see enemy move:";
        getline (cin, input);
        minimax (grid, true, 1);
        printgrid(grid);
        if (checkGameOver(grid)->getGameOver()) {
             cout << "u lost, good game \n";
            break;
         };

    }
    return 0;
}
