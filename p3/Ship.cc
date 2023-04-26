#include<string>
#include<iostream>
#include <vector>
#include "Coordinate.h"
#include "Ship.h"

Ship::Ship(ShipType tipo, const vector <Coordinate*> &pos){

    type = tipo;
    state = OK;
    bool tamOk = false;

    if(tipo == BATTLESHIP && pos.size() == 4){
        tamOk = true;
    }else if(tipo == DESTROYER && pos.size() == 3){
        tamOk = true;
    }else if(tipo == CRUISE && pos.size() == 2){
        tamOk = true;
    }else if(tipo == SUBMARINE && pos.size() == 1){
        tamOk = true;
    }

    if(!tamOk){throw EXCEPTION_WRONG_COORDINATES;}

    for(int i = 0; i < pos.size(); i++){
        pos[i]->setState(SHIP);
    }

}

unsigned Ship::shipSize(ShipType tipo){

    switch(tipo){
        case BATTLESHIP: return 4;
        case DESTROYER: return 3;
        case CRUISE: return 2;
        case SUBMARINE: return 1;
    }

}

ShipType Ship::typeFromChar(char type){

    switch(tipo){
        case 'S': return SUBMARINE;
        case 'D': return DESTROYER;
        case 'C': return CRUISE;
        case 'B': return BATTLESHIP;
        default: throw EXCEPTION_WRONG_SHIP_TYPE;
    }
}

Coordinate *Ship::getPosition(unsigned pos) const{

    if(pos >= 0 && pos < position.size()){
        return positions[pos];
    }else{
        return NULL;//Puede que de error, meterlo en una variable y devolver la variable
    }

}

//Getters
ShipType Ship::getType() const{
    return type;
}

ShipState Ship::getState() const{
    return state;
}

//Aqui va la funcion hit

ostream& operator<<(ostream &os, const Ship &ship){
    
}