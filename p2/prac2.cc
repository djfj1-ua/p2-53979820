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

bool comprobarName(string name)
{

  for (int i = 0; i < (int)name.size(); i++)
  {

    if (name[i] == ':')
    {

      error(ERR_NAME);
      return false;
    }
  }

  if (name.size() >= 3)
  {

    return true;
  }
  else
  {

    error(ERR_NAME);
    return false;
  }
}

bool comprobarParteEmail(string email2){

  cout << "Partes: " << email2 << endl;

  for (int i = 0; i < (int)email2.size(); i++)
  {
    if (email2[0] == '.' && email2[email2.size()] == '.'){
      cout << "1" << endl;
      return false;

    }else if (toupper(email2[i]) < 'A' && toupper(email2[i]) > 'Z'){
      cout << "2" << endl;
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

bool comprobarEmail(string email){

  string part1 = "";
  string part2 = "";
  int vecesArroba = 0;
  int posArroba = 0;

  vecesArroba = encontrarArroba(email,posArroba);

  if(vecesArroba != 1){
    error(ERR_EMAIL); cout << "3" << endl;
    return false;

  }else{

    part1 = email.substr(0,posArroba);
    part2 = email.substr(posArroba+1,email.size());

  }

  if(comprobarParteEmail(part1) == true && comprobarParteEmail(part2) == true){

    return true;

  }else{
    error(ERR_EMAIL); cout << "4" << endl;
    return false;
  
  }

}

void showSubscribers(const Platform &platform)
{
}

void addSubscriber(Platform &platform)
{

  string nameAux = "";
  bool nameOk = false;

  do
  {

    cout << "Enter name: " << endl;
    cin >> nameAux;
    cin.get();
    nameOk = comprobarName(nameAux);

  } while (nameOk == false);

  string emailAux = "";
  bool emailOk = false;

  do
  {

    cout << "Enter email: " << endl;
    cin >> emailAux;
    cin.get();
    emailOk = comprobarEmail(emailAux);

  } while (emailOk == false);
}

void addSubscriberIp(Platform &platform)
{
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
  platform.nextId = 1;

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
