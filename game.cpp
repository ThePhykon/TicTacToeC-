#include "game.hpp"
#include <cstdlib>
#include <ctime>

User* user = new User(1);
array<Game, 16> games;

bool check_win(Board &board){
    Coordinate coord;

    // Check rows
    for(int i = 0; i < NUM_OF_ROWS; i++){
        coord.row = i;
        if(board.getField({.row = i, .col = 0}) == board.getField({.row = i, .col = 1}) && board.getField({.row = i, .col = 0}) == board.getField({.row = i, .col = 2}) && board.getField({.row = i, .col = 0})){
            return true;
        }
    }

    // Check cols
    for(int i = 0; i < NUM_OF_COLS; i++){
        coord.row = i;
        if(board.getField({.row = 0, .col = i}) == board.getField({.row = 1, .col = i}) && board.getField({.row = 0, .col = i}) == board.getField({.row = 2, .col = i}) && board.getField({.row = 0, .col = i})){
            return true;
        }
    }

    // Check diagonal
    if(board.getField({.row = 0, .col = 0}) == board.getField({.row = 1, .col = 1}) && board.getField({.row = 0, .col = 0}) == board.getField({.row = 2, .col = 2}) && board.getField({.row = 1, .col = 1})) {
        return true;
    }

    else if (board.getField({.row = 1, .col = 1}) == board.getField({.row = 0, .col = 2}) && board.getField({.row = 1, .col = 1}) == board.getField({.row = 2, .col = 0}) && board.getField({.row = 1, .col = 1})){
        return true;
    }

    return false;
}

void game_loop(Game game){
    bool turn;
    int counter = 0;

    Coordinate choice;

    std::cout << "Starting game...";

    std::srand(std::time(NULL));
    turn = std::rand()%2;

    while(true) {
        game.board.print();

        if(!turn){
            choice = game.player1->move(game.board);
        }

        else{
            choice = game.player2->move(game.board);
        }

        if(!game.board.setField(choice, (turn + 1))) {
            continue;
        }

        if(check_win(game.board)){
            std::cout << "You won the Game!" << std::endl;
            return;
        }

        turn = (turn) ? false:true;
        counter++;

        if(counter > 9){
            std::cout << "TIE!" << std::endl;
            return;
        }
    }
}


void main_menu(){
    Game game = {Board(), 0, user, user};
    game_loop(game);
    return;
}