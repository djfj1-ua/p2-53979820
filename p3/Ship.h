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

    protected:
        ShipType type;
        ShipState state;
    public:
        Ship(ShipType, const vector <Coordinate*>&);
        static unsigned shipSize(ShipType);
        static ShipType typeFromChar(char);
        Coordinate *getPosition(unsigned) const;
        ShipType getType() const;
        ShipState getState() const;
        bool hit(const Coordinate&);
        friend ostream& operator(ostream&, const Ship&);
}
#endif