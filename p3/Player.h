#ifndef _player_h
#define _player_h

#include <string>
#include <iostream>
#include "Util.h"
#include "Coordinate.h"
#include "Ship.h"

using namespace std;

enum MaxShip{
    1,2,3,4
};

class Player{

    protected:
        string name;
    public:
        Player(string);
        
        //Getter
        string getName() const;

        //Funciones
        void addShip(const Coordinate &pos, ShipType type, Orientation orientation);
        void addShips(string ships);
        bool attack(const Coordinate &coord);
        bool attack(string coord);
        ostream& operator<<(ostream &os, const Player &player);

};
#endif