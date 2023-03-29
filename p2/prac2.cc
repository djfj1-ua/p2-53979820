#include <iostream>
#include <vector>

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
      error(ERR_NAME);
      return false;
    }
  }

  if (name.size() < 3){
    error(ERR_NAME);
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
    error(ERR_EMAIL);
    return false;
  }else{
    part1 = email.substr(0,posArroba);
    part2 = email.substr(posArroba+1,email.size());
  }

  if(comprobarParteEmail(part1) == true && comprobarParteEmail(part2) == true && comprobarParteAtras(part2) == true){
    return true;
  }else{
    error(ERR_EMAIL);
    return false;
  }
}

void mostrarIP(string ips){

  cout << "|" << ips;
  
}

void mostrarSuscriptores(Subscriber suscriptor){

  cout << suscriptor.id << ":" << suscriptor.name << ":" << suscriptor.email << ":" << suscriptor.mainIp << ":";

  for(int j = 0; j < (int)suscriptor.ips.size(); j++){

    mostrarIP(suscriptor.ips[j]);

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
    cin >> nameAux;
    cin.get();
    nameOk = comprobarName(nameAux);

  }while(nameOk == false);

  string emailAux = "";
  bool emailOk = false;

  do{

    cout << "Enter email: " << endl;
    cin >> emailAux;
    cin.get();
    emailOk = comprobarEmail(emailAux);

  } while(emailOk == false);

  platform.nextId++;

  Subscriber suscriptor;

  suscriptor.id = platform.nextId;
  suscriptor.email = emailAux;
  suscriptor.name = nameAux;

  platform.subscribers.push_back(suscriptor);

}

bool comprobarId(int id,Platform plataforma){

  for(int i = 0; i < (int)plataforma.subscribers.size(); i++){

    if((int)plataforma.subscribers[i].id == id){
      return true;
    }

  }

  return false;

}

bool  comprobarNum(int num[4]){

  for(int i = 0; i < 4; i++){
    if(num[i] > 255 && num[i] < 0){
      return false;
    }
  }
  return true;
}

int comprobarStringNum(string num){

  if(num.size() != 1 && num[0] == '0'){
    return 1;
  }

  for (char c : num) {
    if (!isdigit(c)) {
      return 1;
    }
  }

  return 0;

}

bool separarNumeroIP(string IP){

  size_t pos = 0;
  string delimiter = ".";
  string token;
  int ceroOk = 0, i = 0;
  int coordP[4];
  bool compNum = false;

  while ((pos = (int)IP.find(delimiter)) != string::npos) {
    token = IP.substr(0, pos);
    ceroOk = comprobarStringNum(token);

    if(ceroOk != 0){
      return false;
    }

    coordP[i] = stoi(token);
    IP.erase(0, pos + delimiter.length());
    i++;
  }
  
  ceroOk = comprobarStringNum(token);

  if(ceroOk != 0){
    return false;
  }

  coordP[i] = std::stoi(IP);

  compNum = comprobarNum(coordP);

  if(!compNum){
    return false;
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

  vector<string> aux;
  vector<int> frec;

  aux.push_back(ips[0]);
  frec.push_back(1);

  for(int i = 0; i < (int)ips.size(); i++){

    for(int j = 0; j < (int)aux.size(); j++){

      if(ips[i] == aux[j]){

        frec[i]++;

      }else{

        aux.push_back(ips[i]);
        frec.push_back(1);

      }
      
    }

  }

  int auxFrec = 0;
  int pos;

  for(int i = 0; i < (int)ips.size(); i++){

    if(frec[i] > auxFrec){

      auxFrec = frec[i];
      pos = i;

    }

  }

  return ips[pos];

}

int addSubscriberIp(Platform &platform){

  int auxId = 0;
  string auxIP;
  bool idOk = false;
  bool ipOk = false;

  cout << "Enter subscriber id: " << endl;
  cin >> auxId;
  idOk = comprobarId(auxId,platform);

  if(idOk != true){
    error(ERR_IP);
    return 0;
  }

  do{

    cout << "Enter IP:" << endl;
    cin >> auxIP;

    ipOk = comprobarIP(auxIP);

    if(ipOk != true){
      error(ERR_IP);
    }

  }while(ipOk != true);

  platform.subscribers[auxId].ips.push_back(auxIP);

  platform.subscribers[auxId].mainIp = calcularMain(platform.subscribers[auxId].ips);

 return 0;
}

void deleteSubscriber(Platform &platform)
{
}

void importFromCsv(Platform &platform)
{
}

void exportToCsv(const Platform &platform)
{
}

void loadData(Platform &platform)
{
}

void saveData(const Platform &platform)
{
}

void importExportMenu(Platform &platform)
{
}

int main(int argc, char *argv[])
{

  Platform platform;
  platform.name = "Streamflix";
  platform.nextId = 0;

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
