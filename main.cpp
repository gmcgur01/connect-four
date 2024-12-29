#include <iostream>
#include "game.h"

using namespace std;

int main() 
{
    Game connect4 = Game();

    while (true) {
        int move;
        do {
            connect4.display_game();
            cout << "Enter a number between 1 and 7: ";
            cin >> move;
        } while (!connect4.make_move(move - 1));
    }

    return 0;
}