#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>

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

bool comprobarParteEmail(string email2){

  if(email2 == ""){

    return false;

  }

  for (int i = 0; i < (int)email2.size(); i++){

    if (email2[0] == '.' || email2[email2.size() - 1] == '.'){
      return false;

    }else if ((toupper(email2[i]) < 'A' && toupper(email2[i]) > 'Z') /*|| email2[i] != '.' || email2[i] != '_' || (email2[i] < '0' && email2[i] > '9')*/){
      return false;

    }else{

      return true;

    }
  }

  return true;

}

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

bool comprobarEmail(string email){

  string part1 = "";
  string part2 = "";
  int vecesArroba = 0;
  int posArroba = 0;

  vecesArroba = encontrarArroba(email,posArroba);

  if(vecesArroba != 1){
    return false;
  }else{
    part1 = email.substr(0,posArroba);
    part2 = email.substr(posArroba+1,email.size());
  }

  if(comprobarParteEmail(part1) == true && comprobarParteEmail(part2) == true && comprobarParteAtras(part2) == true){
    return true;
  }else{
    return false;
  }
}

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

void showSubscribers(const Platform &platform){

  for(int i = 0; i < (int)platform.subscribers.size(); i++){

    mostrarSuscriptores(platform.subscribers[i]);

  }

}

void addSubscriber(Platform &platform){

  string nameAux = "";
  bool nameOk = false;

  do{

    cout << "Enter name: " << endl;
    getline(cin,nameAux);
    nameOk = comprobarName(nameAux);
    if(!nameOk){error(ERR_NAME);}

  }while(nameOk == false);

  string emailAux = "";
  bool emailOk = false;

  do{

    cout << "Enter email: " << endl;
    getline(cin,emailAux);
    emailOk = comprobarEmail(emailAux);
    if(!emailOk){error(ERR_EMAIL);}

  } while(emailOk == false);

  platform.nextId++;

  Subscriber suscriptor;

  suscriptor.id = platform.nextId;
  suscriptor.email = emailAux;
  suscriptor.name = nameAux;

  platform.subscribers.push_back(suscriptor);

}

int comprobarId(int id, Platform plataforma){

  for(int i = 0; i < (int)plataforma.subscribers.size(); i++){

    if((int)plataforma.subscribers[i].id == id){
      return i;
    }
  }

  return -1;

}

bool comprobarNumIP(string numero){

  int num = stoi(numero);
  
  if(num > 255 || num < 0){
    return false;
  }
  return true;
}

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

string calcularMain(vector<string> ips){

  if(1 == (int)ips.size()){
    return ips[0];
  }

  int maxApariciones = 0;

  string elementoMasComun;

  for (const string &elemento : ips) {

    int apariciones = 0;

    for (const string &otroElemento : ips) {

      if (elemento == otroElemento) {
        apariciones++;
      }

    }

    if (apariciones > maxApariciones) {
      maxApariciones = apariciones;
      elementoMasComun = elemento;
    }
    
  }
  return elementoMasComun;
}

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

  if(idOk == -1 || !comprobarStringNum(linea)){
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

    platform.subscribers[idOk].ips.push_back(auxIP);

    platform.subscribers[idOk].mainIp = calcularMain(platform.subscribers[idOk].ips);

  }
}

void deleteSubscriber(Platform &platform){

  int idOk = -1;
  int auxId = 0;

  cout << "Enter subscriber id: " << endl;
  cin >> auxId;
  idOk = comprobarId(auxId,platform);

  if(idOk == -1){

    error(ERR_ID);

  }else{

    for(int i = 0; i < (int)platform.subscribers.size(); i++){
      if(idOk == i){
        platform.subscribers.erase(platform.subscribers.begin()+i);
      }
    }
  }

}

bool comprobarIps(string ips, Subscriber &suscriptor){

  string token;
  stringstream ss(ips);

  while(getline(ss, token, '|')){

    if(!comprobarIP(token)){return false;}
    
    suscriptor.ips.push_back(token);
  }

  return true;

}

void importFromCsv(Platform &platform, string nomFichero){

  string token = "";

  ifstream fich;
  fich.open(nomFichero);
  int i = 0;

  if(fich.is_open()){

    string linea;

    while(getline(fich,linea)){

      istringstream ss(linea);
      vector<string> datos;
      Subscriber suscriptor;

      while (getline(ss, token, ':')) {
        //cout << token << endl;
        datos.push_back(token);
        //Guardarlo en un vector, cada posicion del vector es un dato
      }

      if(!comprobarEmail(datos[1]) && (int)datos.size() >= 2){
        error(ERR_EMAIL);
      }else if(!comprobarName(datos[0]) && (int)datos.size() >= 2){
        error(ERR_NAME);
      }else if((!comprobarIP(datos[2]) || !comprobarIps(datos[3],suscriptor)) && (int)datos.size() == 4){
        error(ERR_IP);
      }else{
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

void exportToCsv(const Platform &platform, string nomFichero){

  ofstream fich;

  fich.open(nomFichero);

  if(fich.is_open()){

    for(int i = 0; i < (int)platform.subscribers.size(); i++){

      fich << platform.subscribers[i].name << ":" << platform.subscribers[i].email << ":" << platform.subscribers[i].mainIp << ":";

      for(int j = 0; j < (int)platform.subscribers[i].ips.size(); j++){

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

void borrarPlataforma(Platform &platform){

  platform.name = "";
  platform.nextId = 0;
  
  for(int i = 0; i < (int)platform.subscribers.size(); i++){

    platform.subscribers.erase(platform.subscribers.begin());

  }

}

void loadData(Platform &platform){

  string op = "";
  string nomFich;

  do{

    cout << "All data will be erased. Continue? [y/n]:" << endl;
    cin >> op;

  }while(op != "y" && op != "Y" && op != "n" && op != "N");

  if(op == "Y" || op == "y"){

    borrarPlataforma(platform);
    string plataforma;

    cout << "Enter filename: " << endl;
    cin >> nomFich;

    ifstream fich;

    fich.open(nomFich,ios::binary);

    if(fich.is_open()){
      //Investigar ficheros binarios
    }else{error(ERR_FILE);}

    fich.close();
    
  }
  
}

void saveData(const Platform &platform)
{
  cout << "save data" << endl;
}

void showImportMenu(){

  cout << "[Import/export options]" << endl
    << "1- Import from CSV" << endl
    << "2- Export to CSV" << endl
    << "3- Load data" << endl
    << "4- Save data" << endl
    << "b- Back to main menu" << endl
    << "Option: ";

}

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
      loadData(platform);
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

void argumentos(Platform &platform, int argc, char *argv[]){

  if(argc == 3){

    if(strcmp(argv[1], "-i") == 0){

      importFromCsv(platform,argv[2]);

    }else if(strcmp(argv[1], "-l") == 0){

      cout << "Binario" << endl;

    }else{error(ERR_ARGS);cout << "1" << endl;}

  }else if(argc == 5){

    if(strcmp(argv[1], "-i") == 0){

      importFromCsv(platform,argv[2]);

      if(strcmp(argv[3], "-i") == 0){

        importFromCsv(platform,argv[4]);

      }else if(strcmp(argv[1], "-l") == 0){

        cout << "Binario" << endl;

      }else{error(ERR_ARGS);cout << "2" << endl;}

    }else if(strcmp(argv[1], "-l") == 0){

      cout << "Binario" << endl;

    }else{error(ERR_ARGS);cout << "3" << endl;}

  }else{error(ERR_ARGS);cout << "4" << endl;}

}

int main(int argc, char *argv[])
{
  
  Platform platform;
  platform.name = "Streamflix";
  platform.nextId = 0;

  if(argc > 1){

    argumentos(platform,argc,argv);

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
