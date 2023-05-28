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
    if(aux.getStateChar() != 'N'){//Si el estado es diferente de NONE, esa posición no esta libre y devuelvo una excepción.
        throw EXCEPTION_NONFREE_POSITION;
    }else if(aux.getRow() > 9 || aux.getRow() < 0 || aux.getColumn() > 9 || aux.getColumn() < 0){//Si la columna y la fila se salen del tablero, devuelvo una excepción.
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
        }
        if(numType > type){
            throw EXCEPTION_MAX_SHIP_TYPE;
        }
    }
    
    //Compruebo que la partida no ha empezado todavía
    for(int i = 0; i < BOARDSIZE; i++){
        for(int j = 0; j < BOARDSIZE; j++){
            if(board[i][j].getState() == WATER || board[i][j].getState() == HIT){
                throw EXCEPTION_GAME_STARTED;
            }
        }
    }

    vector<Coordinate*> posShip;//Creo el vector de punteros a coordenada y un auxiliar donde copio la coordenada pos.
    Coordinate aux;
    aux = pos;

    comprobarPosTablero(aux);//Compruebo que esta primera coordenada no esta fuera del tablero ni ya esta ocupada.

    posShip.push_back(&(board[pos.getRow()][pos.getColumn()]));//Meto el puntero de esta coordenada dentro del vector.

    for(int i = 0; i < tamShip[type]-1; i++){//Bucle para crear las coordenadas necesarias para cada tipo de barco.
        aux = aux.addOffset(1,orientation);//Con la función addOffset creo la coordenada siguiente a partir de la orientación.
        comprobarPosTablero(aux);//Compruebo que la coordenada que se ha creado sea adecuada para añadir un barco.
        posShip.push_back(&(board[aux.getRow()][aux.getColumn()]));//Añado el puntero a la coordenada dentro del vector de coordenadas.
    }

    Ship barco(type,posShip);//Creo el barco.
    ships.push_back(barco);//Lo añado al vector de barcos del jugador.
}

void Player::addShips(string ships){

    stringstream linea(ships);
    string barco;
    string aux;
    
    //Separo por espacios y guardo las cadenas de caracteres en la variable barco.
    while(linea >> barco){

        stringstream temp(barco);
        vector<string> datosBarco;//Creo un vector para guardar la información.

        while(getline(temp,aux,'-')){//Separo esa cadena de caracteres por el separador "-".
            datosBarco.push_back(aux);
        }
        
        ShipType tipo = Ship::typeFromChar(datosBarco[0][0]);//En la posicion 0 del vector estará el tipo de barco.
        Orientation orientation = Coordinate::orientationFromChar(datosBarco[2][0]);//En la posición 2, la orientación.
        Coordinate coord(datosBarco[1]);//En la posición 1, la coordenada inicial del barco.

        addShip(coord,tipo,orientation);//Con esos datos, llamo a la función addShip.

    }
}

bool Player::attack(const Coordinate &coord){

    bool tocado,hundido;
    int cont = 0, i = 0;

    for(i = 0; i < (int)ships.size(); i++){//Recorro el vector de barcos
        tocado = false;
        hundido = false;
        try{//Llamo a la función hit del objeto barco dentro de un try catch para capturar una posible excepción.
            tocado = ships[i].hit(coord);//Si el ataque se lleva a cabo, devuelve un true.
        }catch (Exception e){
            Util::debug(e);//Si encuentra una excepción se llama a la función debug que devolverá el texto de la excepción capturada.
            return false;//Devuelvo falso porque no se ha completado correctamente el ataque.
        }

        if(tocado==true){//Si el ataque ha tenido exito compruebo si el barco que se ha tocado se ha hundido o no.
            if(ships[i].getState() == SUNK){//Si el barco se ha hundido, ponemos la varible hundido a true.
                hundido = true;
            }
            break;
        }
    }

    if(hundido == true){//Si el barco se ha hundido compruebo cuantos barcos del vector de barcos se han hundido.(Si hundido == true significa que tocado == true también aunque no lo ponga)
        for(int j = 0; j < (int)ships.size(); j++){
            if(ships[j].getState() == SUNK){
                cont++;
            }
        }

        if(cont == (int)ships.size()){//Si los barcos que se han hundido son los mismos a la cantidad total de barcos que hay, se ha terminado la partida.
            throw EXCEPTION_GAME_OVER;
        }else{//Si no, se ha hundido un barco pero no se ha terminado la partida.
            return true;
        }
    }else if(tocado == true){//Si entra aqui significa que no se ha hundido el barco pero que si se ha tocado, por lo que devolvemos true porque el ataque ha tenido exito.
        return true;
    }

    //Si no pasa nada de lo anterior significa que el ataque ha caido en el agua, por lo que ponemos el estado de la casilla en WATER y devolvemos false.
    board[coord.getRow()][coord.getColumn()].setState(WATER);
    return false;
}

bool Player::attack(string coord){

    Coordinate coordenada(coord);//Creo la coordenada con el constructor de coordenadas al que se le pasa una cadena de caracteres.
    return attack(coordenada);//Le paso esa coordenada a la función anterior, y devuelvo su resultado.

}

ostream& operator<<(ostream &os,const Player &player){

    os << player.getName() << endl;
    char letra = 'A';
    for(int i = 0; i <= BOARDSIZE; i++){
        if(i != 0){
            os << letra;
            letra++;
        }
        for(int j = 0; j <= BOARDSIZE; j++){
            if(i == 0){
                if(j == 0){
                    os << " ";
                }else{
                    os << " " << j << " ";
                }
            }else if(j > 0){
                if(player.board[i-1][j-1].getStateChar() == 'N'){
                    os << "   ";
                }else{
                    os << " " << player.board[i-1][j-1].getStateChar() << " ";
                }
            }
        }
        os << endl;
    }

    for(int i = 0; i < (int)player.ships.size(); i++){
        os << player.ships[i];
    }

    return os;
}