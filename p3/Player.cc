#include<string>
#include<iostream>
#include<vector>
#include<sstream>
#include "Player.h"

using namespace std;

//Constructor de la clase Player
Player::Player(string nombre){

    name = nombre;

    for(int i = 0; i < BOARDSIZE; i++){
        for(int j = 0; j < BOARDSIZE; j++){
            board[i][j].setRow(i);
            board[i][j].setColumn(j);
        }
    }
}

//Getter
string Player::getName() const{
    return name;
}

void Player::comprobarPosTablero(const Coordinate aux){
    if(aux.getStateChar() != 'N'){
        throw EXCEPTION_NONFREE_POSITION;
    }else if(aux.getRow() > 9 || aux.getRow() < 0 || aux.getColumn() > 9 || aux.getColumn() < 0){
        throw EXCEPTION_OUTSIDE;
    }
}

//Funcion para añadir un barco al tablero del jugador
void Player::addShip(const Coordinate &pos, ShipType type, Orientation orientation){

    int tamShip[4] = {4,3,2,1};
    int numType = 0;
    
    //Compruebo que no supera el número máximo de barcos
    for(int i = 0; i < (int)ships.size(); i++){
        if(ships[i].getType() == type){
            numType++;
        }else if(numType > type){
            throw EXCEPTION_MAX_SHIP_TYPE;
            break;
        }
    }
    
    //Compruebo que la partida no ha empezado todavía
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(board[i][j].getState() != NONE && board[i][j].getState() != SHIP){
                throw EXCEPTION_GAME_STARTED;
            }
        }
    }

    vector<Coordinate*> posShip;
    Coordinate aux;
    aux = pos;

    comprobarPosTablero(aux);

    posShip.push_back(&(board[pos.getRow()][pos.getColumn()]));

    for(int i = 0; i < tamShip[type]-1; i++){
        aux = aux.addOffset(1,orientation);
        comprobarPosTablero(aux);
        posShip.push_back(&(board[aux.getRow()][aux.getColumn()]));
    }

    Ship barco(type,posShip);
    ships.push_back(barco);
}

void Player::addShips(string ships){

    stringstream linea(ships);
    string barco;
    string aux;
    //Ya esta separado por barco y todo, hay que hacer cosas con eso
    while(linea >> barco){
        stringstream temp(barco);
        while(getline(temp,aux,'-')){
            cout << "Salida: " << aux << endl;
        }
        cout << endl;
    }
}