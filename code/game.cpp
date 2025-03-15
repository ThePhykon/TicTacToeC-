#include <cstdlib>
#include <random>
#include <csignal>
#include <vector>
#include "game.hpp"
#include "bot.hpp"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void signalHandler(int signum) {
    clearScreen();
    
    if(signum == SIGINT) {
        std::cout << "You pressed Ctrl+C!" << std::endl;
        std::cout << "Do you want to exit the game? (y/n): ";
        char choice;
        std::cin >> choice;

        if(choice == 'y') {
            std::cout << "Goodbye!" << std::endl;
            exit(signum);
        }
        
        return;
    }
}

User* user = new User(1);
std::vector<Game> games;

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

bool pause_menu(){
    clearScreen();
    std::cout << "============================\n";
    std::cout << "\033[1;33m         PAUSE MENU         \033[0m\n";
    std::cout << "============================\n";
    std::cout << " Do you want to return to the main menu? (y/n): ";
    char choice;
    std::cin >> choice;

    if(choice == 'y' || choice == 'Y') {
        return true;
    }

    return false;
}

void game_loop(Game game){
    bool turn = 0;
    int counter = game.current;

    if(game.current != 0){
        turn = (game.current % 2) ? true:false;
    }

    Coordinate choice;

    while(true) {
        clearScreen();
        game.board.print();
        std::cout << "============================" << std::endl;
        std::cout << "\033[1;36mPlayer " << (turn + 1) << "'s turn\033[0m" << std::endl << std::endl;

        if(!turn){
            choice = game.player1->move(game.board);
        }

        else{
            choice = game.player2->move(game.board);
        }

        if(choice.row == -1 && choice.col == -1){
            if(pause_menu()){
                game.current = counter;
                games.push_back(game);
                return;
            }
        }

        if(!game.board.setField(choice, (turn + 1))) {
            continue;
        }

        if(check_win(game.board)){
            clearScreen();
            game.board.print();
            std::cout << "============================" << std::endl;
            std::cout << "\033[1;32m      CONGRATULATIONS!      \033[0m" << std::endl;
            std::cout << "============================" << std::endl;
            std::cout << "   \033[1;33mPlayer " << (turn + 1) << " wins the game!\033[0m   " << std::endl;
            std::cout << "============================" << std::endl;
            std::cout << "Press Enter to return to the main menu..." << std::endl;
            std::cin.ignore();
            std::cin.get();
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


void showTitleScreen() {
    clearScreen();
    std::cout << "============================\n";
    std::cout << "      TIC-TAC-TOE MENU      \n";
    std::cout << "============================\n";
    std::cout << "        \033[1;34mX | O | X\033[0m\n";
    std::cout << "        ----------\n";
    std::cout << "        \033[1;31mO | X | O\033[0m\n";
    std::cout << "        ----------\n";
    std::cout << "        \033[1;34mX | O | X\033[0m\n";
    std::cout << "============================\n";
    std::cout << " [1] Player vs Player\n";
    std::cout << " [2] Player vs Computer\n";
    std::cout << " [3] Load Game\n";
    std::cout << " [4] Exit\n";
    std::cout << "============================\n";
    std::cout << " Enter your choice: ";
}

void main_menu(){
    string choice;

    while(true){
        showTitleScreen();
        std::cin >> choice;

        if(choice == "1"){
            Game game = {Board(), 0, user, user};
            game_loop(game);
        }

        else if(choice == "2"){
            std::random_device rd;  // Hardware-basierter Zufallsgenerator
            std::mt19937 gen(rd()); // Mersenne-Twister Zufallszahlengenerator
            std::uniform_int_distribution<int> dist(0, 1);

            int starting = dist(gen);

            Player* bot = new RandomBot(1);
            Game game = {Board(), starting, user, bot};
            game_loop(game);
        }

        else if(choice == "3"){
            if(games.empty()){
                std::cout << "No saved games!" << std::endl;
                std::cin.ignore();
                std::cin.get();
                continue;
            }

            // List saved games
            clearScreen();
            std::cout << "============================" << std::endl;
            std::cout << "       SAVED GAMES MENU      " << std::endl;
            std::cout << "============================" << std::endl;
            for(unsigned int i = 0; i < games.size(); i++){
                std::cout << " [" << (i + 1) << "] Game " << (i + 1) << std::endl;
            }
            std::cout << "============================" << std::endl;
            std::cout << " Enter your choice: ";
            int choice;
            std::cin >> choice;

            if(choice < 1 || choice > games.size()){
                std::cout << "Invalid choice!" << std::endl;
                std::cin.ignore();
                std::cin.get();
                continue;
            }

            Game game = games[choice - 1];
            games.erase(games.begin() + (choice - 1));
            game_loop(game);
        }

        else if(choice == "4"){
            std::cout << "Goodbye!" << std::endl;
            return;
        }

        else{
            std::cout << "Invalid choice!" << std::endl;
            std::cin.ignore();
            std::cin.get();
        }
    }

    return;
}

void init() {
    signal(SIGINT, signalHandler);
    games.empty();
    main_menu();
}