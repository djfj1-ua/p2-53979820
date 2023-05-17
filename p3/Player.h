#ifndef _player_h
#define _player_h

#include <string>
#include <iostream>
#include <vector>
#include "Util.h"
#include "Coordinate.h"
#include "Ship.h"

using namespace std;

const int BOARDSIZE = 10;

class Player{

    protected:
        string name;
        vector<Ship> ships;
        Coordinate board[BOARDSIZE][BOARDSIZE];
    public:
        Player(string);
        
        //Getter
        string getName() const;

        //Funciones
        void comprobarPosTablero(const Coordinate aux);
        void addShip(const Coordinate &pos, ShipType type, Orientation orientation);
        void addShips(string ships);
        bool attack(const Coordinate &coord);
        bool attack(string coord);
        friend ostream& operator<<(ostream &os, const Player &player);

};
#endif