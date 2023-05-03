#include<string>
#include<iostream>
#include "Player.h"

using namespace std;

const int BOARSIZE = 10;

//Constructor de la clase Player
Player::Player(string nombre){

    name = nombre;

    Coordinate board[BOARDSIZE][BOARDSIZE];

    for(int i = 0; i < BOARDSIZE; i++){
        for(int j = 0; j < BOARSIZE; i++){
            board[i][j].setRow(i);
            board[i][j].setColumn(j);
        }
    }
}

//Getter
string getName() const{
    return name;
}

//Funcion para añadir un barco al tablero del jugador
void addShip(const Coordinate &pos, ShipType type, Orientation orientation){
    
}