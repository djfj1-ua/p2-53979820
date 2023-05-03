#include<string>
#include<iostream>
#include <vector>
#include "Ship.h"

Ship::Ship(ShipType tipo, const vector <Coordinate*> &posiciones){

    type = tipo;
    state = OK;
    positions = posiciones;
    bool tamOk = false;

    if(tipo == BATTLESHIP && posiciones.size() == 4){
        tamOk = true;
    }else if(tipo == DESTROYER && posiciones.size() == 3){
        tamOk = true;
    }else if(tipo == CRUISE && posiciones.size() == 2){
        tamOk = true;
    }else if(tipo == SUBMARINE && posiciones.size() == 1){
        tamOk = true;
    }

    if(!tamOk){throw EXCEPTION_WRONG_COORDINATES;}

    for(int i = 0; i < (int)posiciones.size(); i++){
        posiciones[i]->setState(SHIP);
    }

}

unsigned Ship::shipSize(ShipType tipo){

    if(tipo == BATTLESHIP){
        return 4;
    }else if(tipo == DESTROYER){
        return 3;
    }else if(tipo == CRUISE){
        return 2;
    }else{
        return 1;
    }
}

ShipType Ship::typeFromChar(char type){

    switch(type){
        case 'S': return SUBMARINE;
        case 'D': return DESTROYER;
        case 'C': return CRUISE;
        case 'B': return BATTLESHIP;
        default: throw EXCEPTION_WRONG_SHIP_TYPE;
    }
}

Coordinate *Ship::getPosition(unsigned pos) const{

    if(pos >= 0 && pos < (unsigned)positions.size()){
        return positions[pos];
    }else{
        return NULL;//Puede que de error, meterlo en una variable y devolver la variable
    }
}

//Función para convertir el shiptype en string
string Ship::typeToString(ShipType type) const{
    switch(type) {
        case BATTLESHIP:
            return "BATTLESHIP";
        case DESTROYER:
            return "DESTROYER";
        case CRUISE:
            return "CRUISE";
        default:
            return "SUBMARINE"; // Opcional: en caso de que se pase un valor inválido, se devuelve una cadena de caracteres que lo indique.
    }
}

//Función para convertir el shipstate en string
string Ship::stateToString(ShipState state) const {
    switch(state) {
        case OK: return "O";
        case DAMAGED: return "D";
        default: return "S";
    }
}

//Getters
ShipType Ship::getType() const{
    return type;
}

ShipState Ship::getState() const{
    return state;
}

bool Ship::hit(const Coordinate &coord){

    bool allHit = false;

    for(int i = 0; i < (int)positions.size(); i++){

        if((*positions[i]).compare(coord) == true){//Compruebo si la coordenada coincide

            if((*positions[i]).getState() == HIT){//Si ya ha sido atacada salta excepcion
                throw EXCEPTION_ALREADY_HIT;
            }else if(state == SUNK){//Si se ha hundido el barco salta excepcion
                throw EXCEPTION_ALREADY_SUNK;
            }else{//Si no, estamos en una coordenada que se puede atacar

                (*positions[i]).setState(HIT);//Cambiamos el estado a HIT
                allHit = true;//Inicializamos allHit a true

                for(int j = 0; j < (int)positions.size(); j++){//Recorremos todas las coordenadas del barco, si alguna no ha sido atacada el barco no se ha hundido
                    if((*positions[j]).getState() == SHIP){
                        allHit = false;
                        break;
                    }
                }

                if(allHit){//Si todas las coordenadas del barco han sido atacadas
                    state = SUNK;//Cambiamos el estado a SUNK
                }else{
                    state = DAMAGED;//Si no, cambiamos el estado del barco a DAMAGED
                }
                return true;//Devolvemos true si se ha completado el ataque
            }
        }
    }
    return false;//Devolvemos false si no se ha podido llevar a cabo el ataque
}

ostream& operator<<(ostream &os, const Ship &ship) {
    os << ship.typeToString(ship.getType()) << " (" << ship.stateToString(ship.getState()) << "):";
    for(int i = 0; i < (int)ship.positions.size(); i++) {
        os << " " << *(ship.getPosition(i));
    }
    os << endl;
    return os;
}