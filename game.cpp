#include <iostream>
#include "game.h"

using namespace std;

Game::Game(bool player_one_turn) 
{
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            board[row][col] = Slot::EMPTY;
        }
    }

    this->player_one_turn = player_one_turn;
}

void Game::display_game(bool turn)
{
    for (int row = NUM_ROWS - 1; row >= 0; row--) {
        for (int col = 0; col < NUM_COLS; col++) {
            if (board[row][col] == Slot::EMPTY) {
                cout << ".";
            } else if (board[row][col] == Slot::P1_PIECE) {
                cout << "X";
            } else if (board[row][col] == Slot::P2_PIECE) {
                cout << "O";
            } else {
                cerr << "Unknown slot piece!";
                exit(1);
            }
        }
        cout << "\n";
    }

    if (turn) {
        int player_num = player_one_turn ? 1 : 2;
        cout << "Player " << player_num << "'s turn!" << endl;
    }
}

bool Game::make_move(int move)
{
    if (move < 0 || move >= NUM_COLS) {
        return false;
    }

    if (board[NUM_ROWS - 1][move] != Slot::EMPTY) {
        return false;
    }

    int row;
    for (row = NUM_ROWS - 1; row >= 1; row--) {
        if (board[row - 1][move] != Slot::EMPTY) {
            break;
        }
    }

    board[row][move] = player_one_turn ? Slot::P1_PIECE : Slot::P2_PIECE;
    player_one_turn = !player_one_turn;
    return true;
}


int check_slot(Slot curr_slot, Slot& prev, int& count) 
{
    if (curr_slot == prev) {
        count++;
    } else {
        prev = curr_slot;
        count = 1;
        return 0;
    }

    if (prev == Slot::EMPTY || count < 4) {
        return 0;
    }

    return prev == Slot::P1_PIECE ? 1 : 2;
}

int Game::check_win()
{  
    for (int row = 0; row < NUM_ROWS; row++) {
        Slot prev = board[row][0];
        int count = 1;
        for (int col = 1; col < NUM_COLS; col++) {
            int ret;
            if ((ret = check_slot(board[row][col], prev, count))) {
                return ret;
            }
        }
    }

    for (int col = 0; col < NUM_COLS; col++) {
        Slot prev = board[0][col];
        int count = 1;
        for (int row = 1; row < NUM_ROWS; row++) {
            int ret;
            if ((ret = check_slot(board[row][col], prev, count))) {
                return ret;
            }
        }
    }

    for (int offset = -3; offset < 3; offset++) {
        int row_idx = offset < 0 ? 0 : offset;
        int col_idx = offset < 0 ? -offset : 0;
        Slot prev = board[row_idx++][col_idx++];
        int count = 1;
        while (row_idx < NUM_ROWS && col_idx < NUM_COLS) {
            int ret;
            if ((ret = check_slot(board[row_idx++][col_idx++], prev, count))) {
                return ret;
            }
        } 
    }

    for (int offset = -3; offset < 3; offset++) {
        int row_idx = offset < 0 ? 0 : offset;
        int col_idx = offset < 0 ? -offset : 0;
        Slot prev = board[row_idx++][col_idx++];
        int count = 1;
        while (row_idx < NUM_ROWS && col_idx < NUM_COLS) {
            int ret;
            if ((ret = check_slot(board[row_idx++][col_idx++], prev, count))) {
                return ret;
            }
        } 
    }

    for (int offset = 3; offset < 9; offset++) {
        int row_idx = offset >= NUM_ROWS ? NUM_ROWS - 1 : offset;
        int col_idx = offset >= NUM_ROWS ? offset - NUM_ROWS + 1 : 0;
        Slot prev = board[row_idx--][col_idx++];
        int count = 1;
        while (row_idx >= 0 && col_idx < NUM_COLS) {
            int ret;
            if ((ret = check_slot(board[row_idx--][col_idx++], prev, count))) {
                return ret;
            }
        } 
    }

    return 0;
}
