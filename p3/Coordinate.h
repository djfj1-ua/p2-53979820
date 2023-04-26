#ifndef _coordinate_h
#define _coordinate_h

#include<string>
#include<iostream>
#include "Util.h"

using namespace std;

enum CellState{
    NONE,SHIP,HIT,WATER
};

enum Orientation{
    NORTH,EAST,SOUTH,WEST
};

class Coordinate{
    protected:  //Para el corrector
        int row, column;
        CellState cellState; //Variables protected.
    public:
        Coordinate(); //Constructor
        Coordinate(int,int);
        Coordinate(string);

    //Getters
    int getRow() const;
    int getColumn() const;
    CellState getState() const;
    char getStateChar() const;

    //Setters
    void setRow(int);
    void setColumn(int);
    void setState(CellState);

    bool compare(const Coordinate&) const;
    Coordinate addOffset(int, const Orientation) const;
    static Orientation orientationFromChar(char);
    friend ostream& operator << (ostream&, const Coordinate&); //Derechos de acceso

};

#endif