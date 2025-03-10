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
    cout << " ";
    int counter = 0;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(!this->spaces[i][j]) symbol = '0' + counter;
            else symbol = (this->spaces[i][j] == 1) ? player1:player2;

            cout << symbol;

            if(j != 2) cout << " | ";
            counter++;
        }
        cout << endl;
        cout << "----------" << endl;
    }
}

bool Board::setField(Coordinate coord, int player){
    if(spaces[coord.row][coord.col] != 0){
        return false;
    }

    if(!(player == 1 || player == 2)){
        return false;
    }

    spaces[coord.row][coord.col] = player;
    return true;
}

char Board::getField(Coordinate coord){
    return spaces[coord.row][coord.col];
}