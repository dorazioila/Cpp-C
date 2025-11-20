#include <iostream>
#include "Model.h"
#include "Option.h"
#include "Car.h"

using namespace carconfig;

// Tests de la classe Car (avec options)

int main()
{
  std::cout << "(1) ***** on cree un objet Car *************************************************" << std::endl;
  Car car("Projet_208_MrLagalere",Model("208 Access 1.0",68,Engine::Petrol,12500.0f));
  car.display(); // display() doit a present tenir comptes des options

  std::cout << "(2) ***** on ajoute 3 options ******************************************************" << std::endl;
  car.addOption(Option("0MM0","Peinture metallisee",450.0f));
  car.addOption(Option("ZH75","Jante alliage leger 15 pouces",450.0f));
  car.addOption(Option("UB01","Detecteur obstacles arriere",250.0f));
  car.display();

  std::cout << "(3) ***** on calcule le prix du projet *********************************************" << std::endl;
  std::cout << "Prix du projet : " << car.getPrice() << " euros" << std::endl << std::endl;

  std::cout << "(4) ***** on retire l'option ZH75 **************************************************" << std::endl;
  car.removeOption("ZH75");
  car.display();
  std::cout << "Prix du projet : " << car.getPrice() << " euros" << std::endl << std::endl;

  std::cout << "(5) ***** on ajoute une derniere option ********************************************" << std::endl;
  car.addOption(Option("FE10","Pack LED",350.0f));
  car.display();
  std::cout << "Prix du projet : " << car.getPrice() << " euros" << std::endl << std::endl;

  std::cout << "(6) ***** Test du constructeur de copie et du destructeur de Car ***************" << std::endl;
  {
    Car car2(car);
    car2.removeOption("0MM0");
    std::cout << "Copie modifiee du projet de depart :" << std::endl;
    car2.display();
    // on regarde comment se comporte le destructeur de car :)
    // et surtout si celui de Option est appele un nombre de fois suffisant !
  }

  std::cout << "(7) ***** on regarde si le projet de depart n'a pas ete modifie ********************" << std::endl;
  car.display();

  return 0;
}


