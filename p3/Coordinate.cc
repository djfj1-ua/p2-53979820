#include<string>
#include<iostream>
#include "Coordinate.h"

using namespace std;

//Constructor vacío.
Coordinate::Coordinate(){

 row = -1;
 column = -1;
 cellState = NONE;
}

//Constructor con filas y columnas.
Coordinate::Coordinate(int f, int c){

    row = f;
    column = c;
    cellState = NONE;
}

//Constructor con fila y columna a partir de una cadena.
Coordinate::Coordinate(string coord){

    row = coord[0] - 'A';
    string num = coord.substr(1,2);
    column = stoi(num) - 1;
    cellState = NONE;

}

//Getters
int Coordinate::getRow() const{
    return row;
}

int Coordinate::getColumn() const{
  return column;
}

CellState Coordinate::getState() const{
    return cellState;
}

char Coordinate::getStateChar() const{
    
    if(cellState == NONE){
        return 'N';
    }else if(cellState == SHIP){
        return 'S';
    }else if(cellState == HIT){
        return 'H';
    }else{
        return 'W';
    }
}

//Setters
void Coordinate::setRow(int f){
    row = f;
}

void Coordinate::setColumn(int c){
    column = c;
}

void Coordinate::setState(CellState estado){
    cellState = estado;
}

bool Coordinate::compare(const Coordinate& c) const{
 if(row == c.row && column == c.column){
    return true;
  }
  return false;
}

//Recibe una letra y devuelve la orientación asociada a esa letra, o en caso de que la letra no sea correcta salta una excepción.
Orientation Coordinate::orientationFromChar(char a){
  switch(a){
    case 'N': return NORTH;
    case 'S': return SOUTH;
    case 'E': return EAST;
    case 'W': return WEST;
    default: throw EXCEPTION_WRONG_ORIENTATION;
  }
}

//Operador de salida que muestra la coordenada con un formato determinado.
ostream &operator<<(ostream &os, const Coordinate &c){

    if(c.row < 0 || c.column < 0){
        os << "--";
    }else{
        char fila = 'A' + c.row;
        int col = c.column + 1;
        char inicial = c.getStateChar();

        if(inicial == 'N'){
            os << fila << col;
        }else{
            os << fila << col << inicial;
        }
    }
    return os;
}

//Método que devuelve una coordenada que es resultado de sumar 
//a la coordanada (this) un número offset posiciones en la orientacion indicada
Coordinate Coordinate::addOffset(int offset, Orientation orientation) const{

    if(orientation == NORTH){
        return Coordinate(this->row+offset,this->column);
    }else if(orientation == EAST){
        return Coordinate(this->row,this->column+offset);
    }else if(orientation == SOUTH){
        return Coordinate(this->row-offset,this->column);
    }else{
        return Coordinate(this->row,this->column-offset);
    }
}