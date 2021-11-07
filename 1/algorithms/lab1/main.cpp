#include <cstdio>
#include <fstream>
#include <iostream>
#include "game.h"

using namespace std;

HammurapiGame createGame()
{
    ifstream fin(SAVE_FILE_NAME);
    if (fin.good())
    {
        cout << "\nFound a save file. Would you like to continue your previous game? (y/n) ";
        char c;
        cin >> c;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (c == 'y') 
        {
            HammurapiGame game = HammurapiGame::load(fin);
            remove(SAVE_FILE_NAME);
            return game; 
        }
    }

    return HammurapiGame();
}

int main() 
{
    HammurapiGame game = createGame();
    game.play();
}