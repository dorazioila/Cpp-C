#include <iostream>
#include "Option.h"

// Tests de la classe Option seule

int main()
{
  std::cout << std::endl <<"(1) ***** Test du constructeur par defaut de Option *******************************" << std::endl;
  {
    carconfig::Option option;
    option.display();
  }

  std::cout << std::endl << "(2) **** Test des setters/getters ************************************************" << std::endl;
  {
    carconfig::Option option;
    option.setCode("0MM0");
    option.setLabel("Peinture metallisee");
    option.setPrice(450.0f);
    option.display();
  }

  std::cout << std::endl << "(3) ***** Test du constructeur d'initialisation de Option ************************" << std::endl;
  {
    carconfig::Option option("ZH75","Jante alliage leger 15 pouces",450.0f);
    option.display();
  }

  std::cout << std::endl << "(4) ***** Test du constructeur de copie de Option ********************************" << std::endl;
  {
    carconfig::Option option1("UB01","Detecteur obstacles arriere",250.0f);
    std::cout << "option1 (AVANT) :" << std::endl;
    option1.display();
    {   
      carconfig::Option option2(option1);
      std::cout << "option2 :" << std::endl;
      option2.display();
      option2.setPrice(300.0f);
      option2.display();
    }
    std::cout << "option1 (APRES) :" << std::endl;
    option1.display();
  }

  return 0;
}


