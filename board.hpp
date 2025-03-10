#pragma once

#include <array>

using std::array;

struct Coordinate {
    int row;
    int col;
};

class Board {
    private:
        array<array<int, 3>, 3> spaces;
        char player1;
        char player2;

    public:
        Board(char player1, char player2);
        Board() : Board('X', 'O') {};
        void print();
        bool setField(Coordinate coord, int player);
        char getField(Coordinate coord);
};