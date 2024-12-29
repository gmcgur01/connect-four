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

void Game::display_game()
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
    int player_num = player_one_turn ? 1 : 2;
    cout << "Player " << player_num << "'s turn!" << endl;
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
