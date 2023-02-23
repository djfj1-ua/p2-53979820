#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int KNAME=40;
const int KMAXOBSTACLES=20;

enum Error{
    ERR_OPTION,
    ERR_DIFFICULTY,
    ERR_LEVEL,
    ERR_COORDINATE,
    ERR_OBSTACLES,
    ERR_ID,
    ERR_INSTRUCTION
};

// Registro para las coordenadas
struct Coordinate{
    int row;
    int column;
};

// Registro para el jugador
struct Player{
    char name[KNAME];
    int difficulty;
    int score;
    int wins;
    int losses;
};

// Registro para el nivel
struct Level{
    int id;
    int size;
    int numObstacles;
    Coordinate obstacles[KMAXOBSTACLES];
    Coordinate start;
    Coordinate finish;
};

// Función que muestra los mensajes de error
void error(Error e){
    switch(e){
        case ERR_OPTION: cout << "ERROR: wrong option" << endl;
            break;
        case ERR_DIFFICULTY: cout << "ERROR: wrong difficulty" << endl;
            break;
        case ERR_LEVEL: cout << "ERROR: cannot create level" << endl;
            break;
        case ERR_COORDINATE: cout << "ERROR: wrong coordinate" << endl;
            break;
        case ERR_OBSTACLES: cout << "ERROR: wrong number of obstacles" << endl;
            break;
        case ERR_ID: cout << "ERROR: wrong id" << endl;
            break;
        case ERR_INSTRUCTION: cout << "ERROR: wrong instruction" << endl;
            break;
    }
}

// Función que muestra el menú de opciones
void showMenu(){
    cout << "[Options]" << endl
        << "1- Create level" << endl
        << "2- Delete level" << endl
        << "3- Show levels" << endl
        << "4- Play" << endl
        << "5- Report" << endl
        << "q- Quit" << endl
        << "Option: ";
}

void datosJug(Player &jug){

    cout << "Name: " << endl;
    cin.getline(jug.name,49,'\n');

    int dif = 0;

    do{

        cout << "Difficulty: " << endl;
        cin >> dif;
        cin.get();

        if(dif < 1 || dif > 3){

            error(ERR_DIFFICULTY);

        }

    }while(dif < 1 || dif > 3);

    jug.difficulty = dif;
    jug.wins = 0;
    jug.losses = 0;
    jug.score = 0;

}

void mostrarNivel(vector<Level> niveles){

    for(int i = 0; i < (int)niveles.size(); i++){

        cout << "Nivel " << i+1 << ":" << endl;
        cout << "Id: " << niveles[i].id << endl;
        cout << "numObstaculos: " << niveles[i].numObstacles << endl;
        cout << "Size: " << niveles[i].size << endl;


    }

}

bool comprobarObstaculos(vector<Coordinate> &coordenada,int tam, int &j){

    for(int i = 0; i < (int)coordenada.size(); i++){

        cout << "Columna: " << coordenada[i].column << "  Fila: " << coordenada[i].row << endl;

    }

    if(tam < j){

        error(ERR_OBSTACLES);
        j = 0;
        return false;

    }

    cout << "Tamaño: " << tam << endl;

    for(int i = 0; i < (int)coordenada.size(); i++){
        
        if((coordenada[i].column > tam-1 || coordenada[i].row > tam-1) 
        || (coordenada[i].column == 0 && coordenada[i].row == tam-1) 
        || (coordenada[i].column == tam-1 && coordenada[i].row == 0)){

            cout << 111111111 << endl;
            error(ERR_COORDINATE);
            j = 0;
            return false;

        }

        for(int k = i + 1; k < (int)coordenada.size(); k++){

            if(coordenada[i].column == coordenada[k].column && coordenada[i].row == coordenada[k].row){
                cout << "Columna: " << coordenada[i].column << "J: " << j << endl;
                cout << 222222222 << endl;
                error(ERR_COORDINATE);
                j = 0;
                return false;

            }

            if ((pow((coordenada[i].column - coordenada[k].column),2) + pow((coordenada[i].row - coordenada[k].row),2)) <= 2){
                
                cout << 333333333 << endl;
                error(ERR_COORDINATE);
                j = 0;
                return false;

            }

        }

    }

    return true;

}

void obstaculos(Level &nivel, int nObs){

    int vObstaculos[3] = {5,10,20};
    int nObstaculos = vObstaculos[nObs-1];

    // vector<Coordinate> temp;
    Coordinate aux;

    bool obsOk = true;

    bool new_try = true;

    int i = 0,j = 0;

    // string obs = "";

    do{

        cout << "Obstaculos: " << endl;

        vector<Coordinate> temp;

        string obs = "";

        getline(cin,obs);

        i = 0;

        // cout << "Size: " << (int)obs.size() << endl;

        while(i < (int)obs.size() && (obsOk == true || new_try == true)){
            
            // cout << "i: " << i << ", obsOk: " << obsOk << ", new_try: " << new_try << endl;

            new_try = false;

            int fila = obs[i] - '0';
            // cout << "Fila: " << fila << endl;

            i++;
            i++;

            int columna = obs[i] - '0';
            // cout << "Columna: " << columna << endl;

            if(i < (int)obs.size()){

                i++;
                i++;

            }

            aux.row = fila;
            aux.column = columna;

            temp.push_back(aux);

            cout << "J: " << j << endl;

            j++;

            obsOk = comprobarObstaculos(temp,nObstaculos,j);

            cout << "obsOk: " << obsOk << endl;

        }

        new_try = true;


    }while(obsOk == false);

    cout << "De locos." << endl;

}

void crearNivel(Player jug,vector<Level> &niveles,int &id){

    int tam[3] = {5,7,10};

    id++;

    Level nivel;
    nivel.id = id;
    nivel.size = tam[jug.difficulty-1];

    nivel.start.row = (tam[jug.difficulty] - 1);
    nivel.start.column = 0;

    nivel.finish.row = 0;
    nivel.finish.column = (tam[jug.difficulty] - 1);

    mostrarNivel(niveles);

    obstaculos(nivel,jug.difficulty);

    niveles.push_back(nivel);

}

// Función principal (tendrás que añadirle más código tuyo)
int main(){
    char option;
    int id = 0;

    Player jug;
    datosJug(jug);

    vector<Level> niveles;

    do{
        showMenu();
        cin >> option;
        cin.get(); // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
        
        switch(option){
            case '1': // Llamar a la función para crear un nuevo nivel

                if(niveles.size() < 10){
                    
                    crearNivel(jug,niveles,id);

                }else{

                    error(ERR_LEVEL);

                }
                
                break;
            case '2': // Llamar a la función para borrar un nivel existente
                break;
            case '3': // Llamar a la función para mostrar los niveles creados
                break;
            case '4': // Llamar a la función para jugar
                break;
            case '5': // Llamar a la función para mostrar información del jugador
                break;
            case 'q': break;
            default: error(ERR_OPTION); // Muestra "ERROR: wrong option"
        }
    }while(option!='q');
}