#include <iostream>
#include "Garage.h"

using namespace std;

int main()
{
  // Creation du Garage
  Garage g;

  // Ajout de modeles disponibles
  cout << "//***** Modeles disponibles ***********************" << endl;
  g.addModel(Model("208 Active 1.5 BlueHDi 5P",100,Engine::Diesel,21800.0f));
  g.addModel(Model("308 Allure 1.6 Hybrid 5P",150,Engine::Hybrid,38650.0f));
  g.addModel(Model("2008 GT 1.2 PureTech 130 Man.6",130,Engine::Petrol,31400.0f));
  g.displayAllModels();

  cout << "//***** Recuperation du modele d'indice 1 *********" << endl;
  cout << g.getModel(1).toString() << endl << endl;

  // Ajout d'options disponibles
  cout << "//***** Options disponibles ***********************" << endl;
  g.addOption(Option("0MM0","Peinture metallisee",450.0f));
  g.addOption(Option("ZH75","Jante alliage leger 15 pouces",450.0f));
  g.addOption(Option("UB01","Detecteur obstacles arriere",250.0f));
  g.displayAllOptions();

  cout << "//***** Recuperation de l'option d'indice 2 *********" << endl;
  cout << g.getOption(2).toString() << endl << endl;

  // Ajout de clients
  g.addClient("Wagner","Jean-Marc","0498/25.36.23");
  g.addClient("Leonard","Anne","0478/11.23.65");
  g.addClient("Quettier","Patrick","0476/78.45.12");
  g.addClient("Madani","Mounawar","0477/45.29.98");
  g.addClient("Charlet","Christophe","0475/71.31.89");

  // Ajout d'employes
  g.addEmployee("Issier","Paul","issipaul",Employee::SELLER);
  g.addEmployee("Coptere","Elie","coptelie",Employee::ADMINISTRATIVE);
  g.addEmployee("Duviver","Isabelle","duviisab",Employee::ADMINISTRATIVE);
  g.addEmployee("Cadabras","Habras","cadahabr",Employee::SELLER);
  
  // Affichage
  cout << "////////// Avant ///////////////////////////////////////////////////////////////////////" << endl;
  g.displayClients();
  g.displayEmployees();

  cout << "////////// Recherches //////////////////////////////////////////////////////////////////" << endl;
  cout << "Client d'indice 2  : " << g.findClientByIndex(2).toString() << endl;
  cout << "Client d'id 1      : " << g.findClientById(1).toString() << endl;
  cout << "Employe d'indice 1 : " << g.findEmployeeByIndex(1).toString() << endl;
  cout << "Employe d'id 8     : " << g.findEmployeeById(8).toString() << endl << endl;

  // Suppression par indice
  g.deleteClientByIndex(1);
  g.deleteEmployeeByIndex(1);
  
  // Affichage
  cout << "////////// Apres suppression par indice (1) ////////////////////////////////////////////" << endl;
  g.displayClients();
  g.displayEmployees();

  // Suppression par nid
  g.deleteClientById(4);
  g.deleteEmployeeById(9);

  // Affichage
  cout << "////////// Apres suppression par id (C4 et V9) /////////////////////////////////////////" << endl;
  g.displayClients();
  g.displayEmployees();

  return 0;
}

