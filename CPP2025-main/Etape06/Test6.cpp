#include <iostream>
#include <fstream>
#include "Option.h"
#include "Model.h"
#include "Car.h"
#include "Client.h"

using namespace std;
using namespace carconfig;

int  Menu();
void Essai1();
void Essai2();
void Essai3();
void Essai4();

int main(int argc,char* argv[])
{
  int choix;
  bool fini = false;
  
  while(!fini)
  {
    if (argc == 2) { choix = atoi(argv[1]); fini = true; }
    else choix = Menu();
    switch(choix)
    {
      case 1 : Essai1(); break;
      case 2 : Essai2(); break;
      case 3 : Essai3(); break;
      case 4 : Essai4(); break;
      default : fini = true ; break;
    }
  }

  return 0;
}

int Menu()
{
  cout << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 6 ---------------------------------------------------------" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << " 1. Sérialisation/Désérialisation d'un objet de la classe Option" << endl;
  cout << " 2. Sérialisation/Désérialisation d'un objet de la classe Model" << endl;
  cout << " 3. Sérialisation/Désérialisation d'un objet de la classe Car" << endl;
  cout << " 4. Sérialisation/Désérialisation d'un objet de la classe Client" << endl;
  cout << " 5. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  cin.ignore();
  return ch;
}

/*********************************************************************************************/
void Essai1()  // Attention : utilisez les flux texte (<< et >>) !!!!
{
  cout << "----- 1. Sérialisation/Désérialisation d'un objet de la classe Option ------" << endl;
  
  Option o("0MM0","Peinture metallisee",449.99f);
  o.display();
  cout << endl;

  cout << "----- Sauvegarde de l'option dans le fichier O.xml -----" << endl;
  ofstream fichier1("O.xml",ios::out);
  fichier1 << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  fichier1 << o << endl;  // serialisation
  fichier1.close();

  cout << "----- Chargement de l'option situee dans le fichier O.xml -----" << endl;
  ifstream fichier2("O.xml",ios::in);
  Option o2;
  string tag;
  getline(fichier2,tag);
  fichier2 >> o2;  // deserialisation
  fichier2.close();
  o2.display();
  cout << endl;
}

/*********************************************************************************************/
void Essai2()  // Attention : utilisez les flux texte (<< et >>) !!!!
{
  cout << "----- 2. Sérialisation/Désérialisation d'un objet de la classe Model ------" << endl;
  
  Model m("208 Access 1.0",68,Engine::Petrol,12500.0f);
  cout << "Avant sérialisation : " << m.toString() << endl;

  cout << "----- Sauvegarde du modele dans le fichier M.xml -----" << endl;
  ofstream fichier1("M.xml",ios::out);
  fichier1 << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  fichier1 << m << endl;
  fichier1.close();

  cout << "----- Chargement du modele situe dans le fichier M.xml -----" << endl;
  ifstream fichier2("M.xml",ios::in);
  Model m2;
  string tag;
  getline(fichier2,tag);
  fichier2 >> m2;
  fichier2.close();
  cout << "Après sérialisation : " << m2.toString() << endl;
}

/*********************************************************************************************/
void Essai3()  // Attention : utilisez les flux texte (<< et >>) !!!!
{
  cout << "----- 3. Sérialisation/Désérialisation d'un objet de la classe Car ------" << endl;
  
  Car car("Projet_208_MrLagalere",Model("208 Access 1.0",68,Engine::Petrol,12500.0f));
  car.addOption(Option("0MM0","Peinture metallisee",450.0f));
  car.addOption(Option("ZH75","Jante alliage leger 15 pouces",450.0f));
  car.addOption(Option("UB01","Detecteur obstacles arriere",250.0f));
  car.display();
  cout << endl;

  cout << "----- Sauvegarde de la voiture dans le fichier C.xml -----" << endl;
  ofstream fichier1("C.xml",ios::out);
  fichier1 << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  fichier1 << car << endl;
  fichier1.close();

  cout << "----- Chargement de la voiture situee dans le fichier C.xml -----" << endl;
  ifstream fichier2("C.xml",ios::in);
  string tag;
  Car c2;
  getline(fichier2,tag);
  fichier2 >> c2;
  fichier2.close();
  c2.display();
  cout << endl;
}

/*********************************************************************************************/
void Essai4()  // Attention : utilisez les flux texte (<< et >>) !!!!
{
  cout << "----- 4. Sérialisation/Désérialisation d'un objet de la classe Client ------" << endl;
  
  Client c("Wagner","Jean-Marc",23,"0499.65.89.76");
  cout << "Avant sérialisation : " << c.toString() << endl;

  cout << "----- Sauvegarde du client dans le fichier CL.xml -----" << endl;
  ofstream fichier1("CL.xml",ios::out);
  fichier1 << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  fichier1 << c << endl;
  fichier1.close();

  cout << "----- Chargement du client situe dans le fichier CL.xml -----" << endl;
  ifstream fichier2("CL.xml",ios::in);
  Client c2;
  string tag;
  getline(fichier2,tag);
  fichier2 >> c2;
  fichier2.close();
  cout << "Après sérialisation : " << c2.toString() << endl;
}
