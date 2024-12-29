#pragma once

const int NUM_ROWS = 6;
const int NUM_COLS = 7; 

enum class Slot { EMPTY, P1_PIECE, P2_PIECE };

class Game {
    public:
        Game(bool player_one_turn=true);

        void display_game();
        bool make_move(int move);

    private:
        Slot board[NUM_ROWS][NUM_COLS];
        bool player_one_turn;
};
