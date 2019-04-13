#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>

using namespace std;


class Player
{
    protected:
        string name;

    public:
        Player(){};
        Player(string);
        ~Player(){};

        string getName() const;
        string getType() const;

};

#endif // PLAYER_H
