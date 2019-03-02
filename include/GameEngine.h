#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <string>
#include <vector>

#include "Pawn.h"
#include "Player.h"

using namespace std;

class GameEngine
{
    private:
        vector< vector<Pawn> > grid;
        Player *P1;
        Player *P2;
        bool isPlayer1turn = true;
        Pawn SelectedPawn;
        vector<Pawn> AvailablePawn;
        int Form;

    public:
        GameEngine(){};
        GameEngine(string P1, string P2);
        ~GameEngine(){};
        bool isWon(int i, int j);
        void addPawn(int i, int j);
        void SelectPawn(int i, int j);
        bool isPlayable(int i, int j);

};

#endif // GAMEENGINE_H
