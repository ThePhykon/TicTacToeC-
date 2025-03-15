#include "board.hpp"

#include <iostream>

using std::cout;
using std::endl;

Board::Board(char p1, char p2){
    this->player1 = p1;
    this->player2 = p2;

    for(unsigned int i = 0; i < 3; i++){
        for(unsigned int j = 0; j < 3; j++){
            this->spaces[i][j] = 0;
        }
    }
}


void Board::print(){
    char symbol;
    int counter = 0;
    const int padding = 9; // Adjust padding to center the board

    for(int i = 0; i < 3; i++){
        cout << std::string(padding, ' '); // Add padding spaces
        for(int j = 0; j < 3; j++){
            if(!this->spaces[i][j]) {
                symbol = '0' + counter;
                cout << "\033[1;30m"; // Grey color for numbers
            }
            else {
                symbol = (this->spaces[i][j] == 1) ? player1 : player2;
                cout << (this->spaces[i][j] == 1 ? "\033[1;31m" : "\033[1;34m"); // Red for player1, Blue for player2
            }

            cout << " " << symbol << " ";

            if(j != 2) cout << "\033[0m|"; // Reset to default color and print separator
            counter++;
        }
        cout << "\033[0m" << endl; // Reset to default color
        if(i != 2) {
            cout << std::string(padding, ' '); // Add padding spaces
            cout << "-----------" << endl;
        }
    }
    cout << "\033[0m"; // Reset to default color
}

bool Board::setField(Coordinate coord, int player){
    if(spaces[coord.row][coord.col] != 0){
        cout << "Invalid move! " << spaces[coord.row][coord.col] << endl;
        return false;
    }

    if(!(player == 1 || player == 2)){
        cout << "Invalid player!" << endl;
        return false;
    }

    spaces[coord.row][coord.col] = player;
    return true;
}

char Board::getField(Coordinate coord){
    return spaces[coord.row][coord.col];
}