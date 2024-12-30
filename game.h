#pragma once

const int NUM_ROWS = 6;
const int NUM_COLS = 7;

typedef __int128 GameKey;

enum class Slot {
    EMPTY = 0,
    P1_PIECE = 1,
    P2_PIECE = 2
};

class Game {
    public:
        Game(bool player_one_turn=true);
        Game(GameKey key);

        void display_game(bool turn=true);
        bool make_move(int move);
        int check_win();

        GameKey to_key();

    private:
        Slot board[NUM_ROWS][NUM_COLS];
        bool player_one_turn;
};
