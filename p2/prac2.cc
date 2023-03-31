#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

const int KMAXSTRING = 50;
const int KMAXIP = 16;

enum Error
{
  ERR_OPTION,
  ERR_NAME,
  ERR_EMAIL,
  ERR_ID,
  ERR_IP,
  ERR_FILE,
  ERR_ARGS
};

struct Subscriber
{
  unsigned int id;
  string name;
  string email;
  string mainIp;
  vector<string> ips;
};

struct BinSubscriber
{
  unsigned int id;
  char name[KMAXSTRING];
  char email[KMAXSTRING];
  char mainIp[KMAXIP];
};

struct Platform
{
  string name;
  vector<Subscriber> subscribers;
  unsigned int nextId;
};

struct BinPlatform
{
  char name[KMAXSTRING];
  unsigned int nextId;
};

void error(Error e)
{
  switch (e)
  {
  case ERR_OPTION:
    cout << "ERROR: wrong menu option" << endl;
    break;
  case ERR_NAME:
    cout << "ERROR: wrong name" << endl;
    break;
  case ERR_EMAIL:
    cout << "ERROR: wrong email" << endl;
    break;
  case ERR_ID:
    cout << "ERROR: wrong subscriber id" << endl;
    break;
  case ERR_IP:
    cout << "ERROR: wrong IP" << endl;
    break;
  case ERR_FILE:
    cout << "ERROR: cannot open file" << endl;
    break;
  case ERR_ARGS:
    cout << "ERROR: wrong arguments" << endl;
    break;
  }
}

void showMainMenu()
{
  cout << "[Options]" << endl
       << "1- Show subscribers" << endl
       << "2- Add subscriber" << endl
       << "3- Add subscriber IP" << endl
       << "4- Delete subscriber" << endl
       << "5- Import/export" << endl
       << "q- Quit" << endl
       << "Option: ";
}

//Función para comprobar si el nombre es correcto
bool comprobarName(string name){

  for (int i = 0; i < (int)name.size(); i++){
    if (name[i] == ':'){
      return false;
    }
  }

  if (name.size() < 3){
    return false;
  }

  return true;
}

//Función para comprobar si las dos partes del email (antes y despues del @) son correctas
bool comprobarParteEmail(string email2){

  int n = email2.size();

  if (n == 0 || email2[0] == '.' || email2[n - 1] == '.') {
    return false;
  }

  for (int i = 0; i < n; i++) {

    char c = email2[i];

    if (!isalnum(c) && c != '.' && c != '_') {
      return false;
    }

  }

  return true;
}

//Función para contar las veces que aparece el simbolo @ dentro del string email
int encontrarArroba(string email, int &pos){

  int veces = 0;

  for(int i = 0; i < (int)email.size(); i++){

    if(email[i] == '@'){
      veces++;
      pos = i;
    }
  }

  return veces;
}

//Comprobación de la parte de atras del email(despues del @)
bool comprobarParteAtras(string parte){

  int vecesPunto = 0;

  for(int i = 0; i < (int)parte.size(); i++){
    if(parte[i] == '.'){
      vecesPunto++;
    }
  }

  if(vecesPunto < 1){
    return false;
  }

  return true;
}

//Función general de la comprobación del email
bool comprobarEmail(string email){

  string part1 = "";
  string part2 = "";
  int vecesArroba = 0;
  int posArroba = 0;

  vecesArroba = encontrarArroba(email,posArroba);

  if(vecesArroba != 1){
    return false;
  }else{//Si solo hay una @ dividimos el email en dos partes, una antes del @ y otra despues.
    part1 = email.substr(0,posArroba);
    part2 = email.substr(posArroba+1,email.size());
  }

  if(comprobarParteEmail(part1) == true && comprobarParteEmail(part2) == true && comprobarParteAtras(part2) == true){
    return true;
  }else{
    return false;
  }
}

//Función para imprimir un suscriptor
void mostrarSuscriptores(Subscriber suscriptor){

  cout << suscriptor.id << ":" << suscriptor.name << ":" << suscriptor.email << ":" << suscriptor.mainIp << ":";

  for(int j = 0; j < (int)suscriptor.ips.size(); j++){
    cout << suscriptor.ips[j];

    if(j < (int)suscriptor.ips.size()-1){
      cout << "|";
    }
  }

  cout << endl;
}

//Función para mostrar todos los suscriptores
void showSubscribers(const Platform &platform){

  for(int i = 0; i < (int)platform.subscribers.size(); i++){
    mostrarSuscriptores(platform.subscribers[i]);
  }

}

//Función para añadir un suscriptor a la plataforma
void addSubscriber(Platform &platform){

  string nameAux = "";
  bool nameOk = false;

  do{//Comprobamos que el nombre sea correcto, si no lo es se vuelve a pedir el nombre y envia un mensaje de error

    cout << "Enter name: " << endl;
    getline(cin,nameAux);

    nameOk = comprobarName(nameAux);

    if(!nameOk){error(ERR_NAME);}

  }while(nameOk == false);

  string emailAux = "";
  bool emailOk = false;

  do{//Comprobamos si email es correcto, si no se envia un mensaje de error y se vuelve a pedir

    cout << "Enter email: " << endl;
    getline(cin,emailAux);
    emailOk = comprobarEmail(emailAux);

    if(!emailOk){error(ERR_EMAIL);}

  } while(emailOk == false);

  //Se añade el suscriptor a la plataforma
  platform.nextId++;

  Subscriber suscriptor;

  suscriptor.id = platform.nextId;
  suscriptor.email = emailAux;
  suscriptor.name = nameAux;

  platform.subscribers.push_back(suscriptor);

}

//Función para comprobar que el id pasado por teclado existe en la plataforma, si existe devuelve su posición en el vector
int comprobarId(int id, Platform plataforma){

  for(int i = 0; i < (int)plataforma.subscribers.size(); i++){

    if((int)plataforma.subscribers[i].id == id){
      return i;
    }
  }

  return -1;
}

//Comprobamos si el número del cual se compone la IP es correcto
bool comprobarNumIP(string numero){

  int num = stoi(numero);
  
  if(num > 255 || num < 0){
    return false;
  }
  return true;
}

//Comprobamos si el caracter es un número y comprobamos que no haya 0's a la izquierda
bool comprobarStringNum(string num){

  if(num.size() != 1 && num[0] == '0'){
    return false;
  }

  for (char c : num) {
    if (!isdigit(c)) {
      return false;
    }
  }

  return true;
}

//Función para separar la IP en 4 números y los comprueba. Si son correctos devuelve true, si no false.
bool separarNumeroIP(string IP){

  stringstream ss(IP);
  string token;
  while (getline(ss, token, '.')) {
    if(!comprobarStringNum(token) || !comprobarNumIP(token)){
      return false;
    }
  }

  return true;
}

//Función para comprobar si la IP es correcta.
bool comprobarIP(string IP){

  int contP = 0;
  bool numOk = false;
  
  for(int i = 0; i < (int)IP.size(); i++){
    if(IP[i] == '.'){
      contP++;
    }
  }

  if(contP != 3){
    return false;
  }

  numOk = separarNumeroIP(IP);

  if(numOk == false){
    return false;
  }

  return true;
}

//Función para calcular cual es la IP principal dentro del vector ips.
string calcularMain(vector<string> ips){

  if(1 == (int)ips.size()){//Si ips solo tiene un elemento, la IP principal es ese elemento
    return ips[0];
  }

  int maxApariciones = 0;

  string elementoMasComun;

  for (const string &elemento : ips) {//Bucle donde se guarda en elemento la IP a comparar

    int apariciones = 0;

    for (const string &otroElemento : ips) {//Se guarda en otroElemento otra IP y la compara con la anterior, si son iguales se suma 1 a apariciones

      if (elemento == otroElemento) {
        apariciones++;
      }

    }

    if (apariciones > maxApariciones) {//Se comprueba si el elemento con más apariciones es el mismo, el nuevo elemento pasa a ser que que tiene más apariciones
      maxApariciones = apariciones;
      elementoMasComun = elemento;
    }
    
  }
  return elementoMasComun;
}

//Función para añadir IP a suscriptores
void addSubscriberIp(Platform &platform){

  int auxId = 0;
  string auxIP = "";
  int idOk = -1;
  bool ipOk = false;
  string linea = "";

  cout << "Enter subscriber id: " << endl;
  getline(cin,linea);

  stringstream ss(linea);

  if((ss >> auxId)){
    auxId = stoi(linea);
    idOk = comprobarId(auxId,platform);
  }

  if(idOk == -1 || !comprobarStringNum(linea)){//Se comprueba que lo que se ha introducido por teclado es una id valida
    error(ERR_ID);
  }else{

    do{

      cout << "Enter IP:" << endl;
      getline(cin,auxIP);

      ipOk = comprobarIP(auxIP);

      if(ipOk != true){
        error(ERR_IP);
      }

    }while(ipOk != true);

    //Si la id y la IP son validas, se añaden al suscriptor 
    platform.subscribers[idOk].ips.push_back(auxIP);

    platform.subscribers[idOk].mainIp = calcularMain(platform.subscribers[idOk].ips);

  }
}

//Función para borrar un suscriptor
void deleteSubscriber(Platform &platform){

  int idOk = -1;
  int auxId = 0;

  cout << "Enter subscriber id: " << endl;
  cin >> auxId;
  idOk = comprobarId(auxId,platform);//Se comprueba que el id es correcto

  if(idOk == -1){//Si el id no es correcto se envia un mensaje de error, si lo es se borra el suscriptor deseado

    error(ERR_ID);

  }else{

    for(int i = 0; i < (int)platform.subscribers.size(); i++){
      if(idOk == i){
        platform.subscribers.erase(platform.subscribers.begin()+i);
      }
    }
  }
}

//Función para comprobar que todas las IP que se pasas en ips son correctas
bool comprobarIps(string ips, Subscriber &suscriptor){

  string token;
  stringstream ss(ips);

  while(getline(ss, token, '|')){

    if(!comprobarIP(token)){return false;}
    
    suscriptor.ips.push_back(token);
  }

  return true;
}

//Función para importar suscriptores desde un archivo csv
void importFromCsv(Platform &platform, string nomFichero){

  string token = "";

  ifstream fich;
  fich.open(nomFichero);
  int i = 0;

  if(fich.is_open()){

    string linea;

    while(getline(fich,linea)){//Vamos cogiendo linea a linea del fichero la información

      istringstream ss(linea);
      vector<string> datos;
      Subscriber suscriptor;

      //Lo dividimos por tokens separados por : y lo almacenamos en el vector datos. En cada elemento del vector datos hay almacenado un dato de suscriptor
      //En el elemento 0 del vector esta el nombre, en el 1 el email...
      while (getline(ss, token, ':')) {
        datos.push_back(token);
      }

      if(!comprobarEmail(datos[1]) && (int)datos.size() >= 2){
        error(ERR_EMAIL);
      }else if(!comprobarName(datos[0]) && (int)datos.size() >= 2){
        error(ERR_NAME);
      }else if((!comprobarIP(datos[2]) || !comprobarIps(datos[3],suscriptor)) && (int)datos.size() == 4){
        error(ERR_IP);
      }else{
        //Cuando ya hemos comprobado que estan todos los datos correctos, los almacenamos y los metemos al vector de suscriptores
        platform.nextId++;

        suscriptor.email = datos[1];
        suscriptor.name = datos[0];
        suscriptor.mainIp = datos[2];
        suscriptor.id = platform.nextId;

        platform.subscribers.push_back(suscriptor);
      }
      i++;
    }

    fich.close();

  }else{error(ERR_FILE);}
}

//Función para exportar los datos de los suscriptores a un archivo csv
void exportToCsv(const Platform &platform, string nomFichero){

  ofstream fich;

  fich.open(nomFichero);

  if(fich.is_open()){

    for(int i = 0; i < (int)platform.subscribers.size(); i++){//Bucle para recorrer el vector de los suscriptores

      fich << platform.subscribers[i].name << ":" << platform.subscribers[i].email << ":" << platform.subscribers[i].mainIp << ":";//Imprimimos en el archivo

      for(int j = 0; j < (int)platform.subscribers[i].ips.size(); j++){//Bucle para almacenar todas las IP's del vector ips

        fich << platform.subscribers[i].ips[j];

        if(j < (int)platform.subscribers[i].ips.size()-1){
          fich << "|";
        }
      }

      fich << endl;
    }

    fich.close();

  }else{error(ERR_FILE);}
  
}

//Función para borrar todos los datos de la plataforma
void borrarPlataforma(Platform &platform){

  platform.name = "";
  platform.nextId = 0;
  platform.subscribers.clear();

}

//Función para cargar datos de suscriptores desde un archivo binario
bool loadData(Platform &platform, bool opcion, string nom){

  string op = "";
  string nomFich;

  if(opcion == true){//Si la llamada a la funcion LoadData viene desde la opción de comandos, se salta la parte de confirmar la acción
    nomFich = nom;
    borrarPlataforma(platform);
  }else{//Si viene de la llamada por menú se hara la confirmación y se pedira el nombre del fichero

    do{
      cout << "All data will be erased. Continue? [y/n]:" << endl;
      cin >> op;
    }while(op != "y" && op != "Y" && op != "n" && op != "N");

    if(op == "N" || op == "n"){
      return true;
    }

    borrarPlataforma(platform);

    cout << "Enter filename: " << endl;
    cin >> nomFich;
  }

  ifstream fich;

  fich.open(nomFich,ios::binary);

  if(fich.is_open()){
    
    BinPlatform binPlatform;

    fich.read((char*)&binPlatform,sizeof(BinPlatform));//Leo los datos de la plataforma binaria y la añado a la plataforma normal

    platform.name = binPlatform.name;
    platform.nextId = binPlatform.nextId;

    while(fich.peek() != EOF){//Se van leyendo las lineas hasta que se llegue al final del fichero
      BinSubscriber binSuscriber;
      fich.read((char*)&binSuscriber,sizeof(BinSubscriber));//Se almacenan en binSuscriber

      Subscriber suscriptor;//Se pasan a un suscriptor normal y se añade al vector de suscriptores

      suscriptor.email = binSuscriber.email;
      suscriptor.name = binSuscriber.name;
      suscriptor.id = binSuscriber.id;
      suscriptor.mainIp = binSuscriber.mainIp;
      suscriptor.ips.push_back(binSuscriber.mainIp);

      platform.subscribers.push_back(suscriptor);
    }
    
  }else{error(ERR_FILE); return false;}

  fich.close();

  return true;
    
}

//Función para almacenar los datos de los suscriptores en un archivo binario
void saveData(const Platform &platform){

  string nomFich;

  cout << "Enter filename: " << endl;
  cin >> nomFich;

  ofstream fich;

  fich.open(nomFich,ios::binary);

  if(!fich.is_open()){
    error(ERR_FILE);
    return;
  }

  BinPlatform binPlatform;

  //Como en la plataforma normal se trabaja con string y en binario con cadenas de caracteres, uso strcpy para copiar uno en el otro
  strncpy(binPlatform.name,platform.name.c_str(),KMAXSTRING-1);
  binPlatform.nextId = platform.nextId+1;

  fich.write((char*)&binPlatform,sizeof(BinPlatform));

  //Recorro el vector de suscriptores y los voy almacenando en binSuscriptor para la posterior escritura en el archivo
  for(int i = 0; i < (int)platform.subscribers.size(); i++){

    BinSubscriber binSuscriptor;

    strncpy(binSuscriptor.name,platform.subscribers[i].name.c_str(),KMAXSTRING-1);
    strncpy(binSuscriptor.email,platform.subscribers[i].email.c_str(),KMAXSTRING-1);
    binSuscriptor.id = platform.subscribers[i].id;
    strcpy(binSuscriptor.mainIp,platform.subscribers[i].mainIp.c_str());

    fich.write((char*)&binSuscriptor,sizeof(BinSubscriber));
      
  }

  fich.close();
  
}

//Función para mostrar el menu de import/export
void showImportMenu(){

  cout << "[Import/export options]" << endl
    << "1- Import from CSV" << endl
    << "2- Export to CSV" << endl
    << "3- Load data" << endl
    << "4- Save data" << endl
    << "b- Back to main menu" << endl
    << "Option: ";

}

//Función principal para la importación y exportación de archivos
void importExportMenu(Platform &platform){

  char option;
  string nomFichero;
  do
  {
    showImportMenu();
    cin >> option;
    cin.get();

    switch (option)
    {
    case '1':
      cout << "Enter filename:" << endl;
      getline(cin,nomFichero);
      importFromCsv(platform,nomFichero);
      break;
    case '2':
      cout << "Enter filename:" << endl;
      getline(cin,nomFichero);  
      exportToCsv(platform,nomFichero);
      break;
    case '3':
      loadData(platform,false,"");
      break;
    case '4':
      saveData(platform);
      break;
    case 'b':
      break;
    default:
      error(ERR_OPTION);
    }
  } while (option != 'b');

}

//Función para controlar el paso de los comando por argumento
bool argumentos(Platform &platform, int argc, char *argv[]){

  if(argc == 3){

    if(strcmp(argv[1], "-l") == 0){

      return loadData(platform,true,argv[2]);

    }else if(strcmp(argv[1], "-i") == 0){

      importFromCsv(platform,argv[2]);
      return true;

    }else{error(ERR_ARGS);}

  }else if(argc == 5){

    if(strcmp(argv[1], "-l") == 0){

      if(!loadData(platform,true,argv[2])){
        return false;
      }

      if(strcmp(argv[3], "-i") == 0){

        importFromCsv(platform,argv[4]);
        return true;

      }else{error(ERR_ARGS);}

    }else if(strcmp(argv[1], "-i") == 0){

      if(strcmp(argv[3], "-l") == 0){

        loadData(platform,true,argv[4]);
        importFromCsv(platform,argv[4]);
        return true;

      }else{error(ERR_ARGS);}

    }else{error(ERR_ARGS);}

  }else{error(ERR_ARGS);}

  return false;

}

int main(int argc, char *argv[])
{
  
  Platform platform;
  platform.name = "Streamflix";
  platform.nextId = 0;
  bool arg = false;

  if(argc > 1){

    arg = argumentos(platform,argc,argv);

    if(arg == false){
      return 0;
    }

  }
    
  char option;
  do
  {
    showMainMenu();
    cin >> option;
    cin.get();

    switch (option)
    {
    case '1':
      showSubscribers(platform);
      break;
    case '2':
      addSubscriber(platform);
      break;
    case '3':
      addSubscriberIp(platform);
      break;
    case '4':
      deleteSubscriber(platform);
      break;
    case '5':
      importExportMenu(platform);
      break;
    case 'q':
      break;
    default:
      error(ERR_OPTION);
    }
  } while (option != 'q');

  return 0;
}