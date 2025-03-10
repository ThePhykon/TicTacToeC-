#pragma once

#include "board.hpp"
#include "player.hpp"

struct Game {
    Board board;
    int current;
    Player* player1;
    Player* player2;
};

// Function prototypes
void main_menu();

// Constants
constexpr int NUM_OF_ROWS = 3;
constexpr int NUM_OF_COLS = 3;