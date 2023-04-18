#include<string>
#include<iostream>
#include "Coordinate.h"

using namespace std;

Coordinate::Coordinate(){

 row = -1;
 column = -1;
 cellState = NONE;
}

Coordinate::Coordinate(int f, int c){

    row = f;
    column = c;
    cellState = NONE;
}

Coordinate::Coordinate(string coord){

    row = coord[0] - 'A';
       

}