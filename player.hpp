#pragma once

#include "board.hpp"
#include <string>
#include <iostream>

using std::cin;
using std::string;

class Player {
    private:
        int number;

    public:
        Player(int num): number(num) {};
        virtual ~Player() = default;
        inline int getNumber(){ return this->number;};
        virtual Coordinate move(Board board) = 0;
};

class User : public Player {
    public:
        User(int num): Player(num) {};
        inline Coordinate move(Board board) override {
            string temp;
            std::cout << "Your choice: "; 
            cin >> temp;

            if(temp == "PAUSE"){
                return {-1, -1};
            }

            int input = stoi(temp);

            return {(input / 3), (input % 3)};
        }
};