#include <iostream>
#include "game.h"

using namespace std;

int main() 
{
    Game connect4 = Game();

    while (true) {
        int move;
        do {

            int winning_player;
            if ((winning_player = connect4.check_win())) {
                connect4.display_game(false);
                cout << "Player " << winning_player << " wins!" << endl;
                return 0;
            }

            connect4.display_game();
            cout << "Enter a number between 1 and 7: ";
            cin >> move;
        } while (!connect4.make_move(move - 1));
    
    }
}