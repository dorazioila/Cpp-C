#include <iostream>
#include "Model.h"
#include "Car.h"

using namespace carconfig;

// Tests de base de la classe Car (sans les options)

int main()
{
  std::cout << std::endl << "(1) ***** Test du constructeur par defaut de Car *******************************" << std::endl;
  {
    Car car;
    car.display();
  }

  std::cout << std::endl << "(2) ***** Test des setters/getters *************************************************" << std::endl;
  {
    Car c;
    c.setName("Projet_208_MrDugenou");
    Model m("208 Active 1.5 BlueHDi 5P",100,Engine::Diesel,21800.0f);
    c.setModel(m);
    c.display();
    std::cout << "Nom du projet : " << c.getName() << std::endl;
    std::cout << "Model du projet : ";
    c.getModel().display();
  }

  std::cout << std::endl << "(3) ***** Test du constructeur d'initialisation de Car *************************" << std::endl;
  {
    Car c("Projet_508SW_MmeLoreille",Model("508SW Style 1.6 HDi",115,Engine::Diesel,28500.0f));
    c.display();
    std::cout << "Nom du projet : " << c.getName() << std::endl;
    std::cout << "Model du projet : ";
    c.getModel().display();
  }

  std::cout << std::endl << "(4) ***** Test du constructeur de copie de Car *********************************" << std::endl;
  {
    Car c1("Projet_208GTi_MrLepresse",Model("208 GTi 1.6",200,Engine::Petrol,34100.0f));
    std::cout << "c1 (AVANT) :" << std::endl;
    c1.display();
    {   
      Car c2(c1);
      std::cout << "c2 :" << std::endl;
      c2.display();
      c2.setName("Projet_208GTi_MrLepresse_bis");
      c2.display();
    }
    std::cout << "c1 (APRES) :" << std::endl;
    c1.display();
  }

  return 0;
}


