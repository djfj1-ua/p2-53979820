#include<string>
#include<iostream>
#include<vector>
#include "Player.h"

using namespace std;

//Constructor de la clase Player
Player::Player(string nombre){

    name = nombre;

    Coordinate board[BOARDSIZE][BOARDSIZE];

    for(int i = 0; i < BOARDSIZE; i++){
        for(int j = 0; j < BOARDSIZE; i++){
            board[i][j].setRow(i);
            board[i][j].setColumn(j);
        }
    }
}

//Getter
string Player::getName() const{
    return name;
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
        for(int j = 0; j < 10; i++){
            if(board[i][j].getState() != NONE && board[i][j].getState() != SHIP){
                throw EXCEPTION_GAME_STARTED;
            }
        }
    }

    vector<Coordinate*> posShip;

    posShip.push_back(&(board[pos.getRow()][pos.getColumn()]));
    
    for(int i = 0; i < tamShip[type]; i++){
        pos.addOffset(1,orientation);
        posShip.push_back(&(board[pos.getRow()][pos.getColumn()]));
    }
//Falta comprobar si las coordenadas del vector son correctas
//Y crear el barco con ese vector de coordenadas
}