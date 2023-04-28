#ifndef SHIP_H
#define SHIP_H
#include "Coordinate.h"

enum ShipType{
    BATTLESHIP, DESTROYER, CRUISE, SUBMARINE
};

enum ShipState{
    OK, DAMAGED, SUNK
};

class Ship{
    protected://Variables
        ShipType type;
        ShipState state;
        vector<Coordinate*> positions;
    public:

        //Constructor
        Ship(ShipType, const vector <Coordinate*>&);

        //Funciones
        static unsigned shipSize(ShipType);
        string typeToString(ShipType type) const;
        string stateToString(ShipState state) const;
        static ShipType typeFromChar(char);
        Coordinate *getPosition(unsigned) const;
        ShipType getType() const;
        ShipState getState() const;
        bool hit(const Coordinate&);
        friend ostream& operator<<(ostream&, const Ship&);
};
#endif