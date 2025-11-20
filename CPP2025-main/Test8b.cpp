#include <iostream>
#include "Garage.h"

using namespace std;

int main()
{
  // Creation du Garage
  // implicite !!! (variable statique)

  // Ajout de modeles disponibles
  cout << "//***** Modeles disponibles ***********************" << endl;
  Garage::getInstance().addModel(Model("208 Active 1.5 BlueHDi 5P",100,Engine::Diesel,21800.0f));
  Garage::getInstance().addModel(Model("308 Allure 1.6 Hybrid 5P",150,Engine::Hybrid,38650.0f));
  Garage::getInstance().addModel(Model("2008 GT 1.2 PureTech 130 Man.6",130,Engine::Petrol,31400.0f));
  Garage::getInstance().displayAllModels();

  cout << "//***** Recuperation du modele d'indice 1 *********" << endl;
  cout << Garage::getInstance().getModel(1).toString() << endl << endl;

  // Ajout d'options disponibles
  cout << "//***** Options disponibles ***********************" << endl;
  Garage::getInstance().addOption(Option("0MM0","Peinture metallisee",450.0f));
  Garage::getInstance().addOption(Option("ZH75","Jante alliage leger 15 pouces",450.0f));
  Garage::getInstance().addOption(Option("UB01","Detecteur obstacles arriere",250.0f));
  Garage::getInstance().displayAllOptions();

  cout << "//***** Recuperation de l'option d'indice 2 *********" << endl;
  cout << Garage::getInstance().getOption(2).toString() << endl << endl;

  // Ajout de clients
  Garage::getInstance().addClient("Wagner","Jean-Marc","0498/25.36.23");
  Garage::getInstance().addClient("Leonard","Anne","0478/11.23.65");
  Garage::getInstance().addClient("Quettier","Patrick","0476/78.45.12");
  Garage::getInstance().addClient("Madani","Mounawar","0477/45.29.98");
  Garage::getInstance().addClient("Charlet","Christophe","0475/71.31.89");

  // Ajout d'employes
  Garage::getInstance().addEmployee("Issier","Paul","issipaul",Employee::SELLER);
  Garage::getInstance().addEmployee("Coptere","Elie","coptelie",Employee::ADMINISTRATIVE);
  Garage::getInstance().addEmployee("Duviver","Isabelle","duviisab",Employee::ADMINISTRATIVE);
  Garage::getInstance().addEmployee("Cadabras","Habras","cadahabr",Employee::SELLER);
  
  // Affichage
  cout << "////////// Avant ///////////////////////////////////////////////////////////////////////" << endl;
  Garage::getInstance().displayClients();
  Garage::getInstance().displayEmployees();

  cout << "////////// Recherches //////////////////////////////////////////////////////////////////" << endl;
  cout << "Client d'indice 2  : " << Garage::getInstance().findClientByIndex(2).toString() << endl;
  cout << "Client d'id 1      : " << Garage::getInstance().findClientById(1).toString() << endl;
  cout << "Employe d'indice 1 : " << Garage::getInstance().findEmployeeByIndex(1).toString() << endl;
  cout << "Employe d'id 8     : " << Garage::getInstance().findEmployeeById(8).toString() << endl << endl;

  // Suppression par indice
  Garage::getInstance().deleteClientByIndex(1);
  Garage::getInstance().deleteEmployeeByIndex(1);
  
  // Affichage
  cout << "////////// Apres suppression par indice (1) ////////////////////////////////////////////" << endl;
  Garage::getInstance().displayClients();
  Garage::getInstance().displayEmployees();

  // Suppression par nid
  Garage::getInstance().deleteClientById(4);
  Garage::getInstance().deleteEmployeeById(9);

  // Affichage
  cout << "////////// Apres suppression par id (C4 et V9) /////////////////////////////////////////" << endl;
  Garage::getInstance().displayClients();
  Garage::getInstance().displayEmployees();

  // Manipulation du projet de voiture en cours
  cout << "////////// Projet en cours : Avant /////////////////////////////////////////////////////" << endl;
  Garage::getCurrentProject().display();

  Garage::getCurrentProject().setName("Projet_208_MrLagalere");
  Garage::getCurrentProject().setModel(Garage::getInstance().getModel(0));
  Garage::getCurrentProject().addOption(Garage::getInstance().getOption(2));
  Garage::getCurrentProject().addOption(Garage::getInstance().getOption(0));

  cout << "////////// Projet en cours : Apres /////////////////////////////////////////////////////" << endl;
  Garage::getCurrentProject().display();

  cout << "////////// Projet en cours : Apres reset ///////////////////////////////////////////////" << endl;
  Garage::resetCurrentProject();
  Garage::getCurrentProject().display();

  return 0;
}

