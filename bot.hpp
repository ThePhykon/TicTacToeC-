#pragma once

#include "board.hpp"
#include "player.hpp"

class RandomBot : public Player {
    public:
        RandomBot(int num): Player(num) {};
        inline Coordinate move(Board board) override {
            Coordinate coord;
            coord.row = rand() % 3;
            coord.col = rand() % 3;

            return coord;
        }
};