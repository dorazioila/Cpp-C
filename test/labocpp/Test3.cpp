#include <stdlib.h>
#include <iostream>
#include "Car.h"

using namespace carconfig;

int  Menu();
void Essai1();
void Essai2();
void Essai3();
void Essai4();
void Essai5();
void Essai6();
void Essai7();
void Essai8();
void Essai9();

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
      case 5 : Essai5(); break;
      case 6 : Essai6(); break;
      case 7 : Essai7(); break;
      case 8 : Essai8(); break;
      case 9 : Essai9(); break;
      default : fini = true ; break;
    }
  }

  return 0;
}

/*******************************************************************************************************/
int Menu()
{
  std::cout << std::endl;
  std::cout << "--------------------------------------------------------------------------------------" << std::endl;
  std::cout << "--- JEU DE TESTS 3 -------------------------------------------------------------------" << std::endl;
  std::cout << "--------------------------------------------------------------------------------------" << std::endl;
  std::cout << " 1. Tests de l'operateur = de la classe Car" << std::endl;
  std::cout << " 2. Tests des operateurs + de la classe Car" << std::endl;
  std::cout << " 3. Tests des operateurs - de la classe Car" << std::endl;
  std::cout << " 4. Tests des operateurs < > == de la classe Car" << std::endl;
  std::cout << " 5. Tests des operateurs << et >> de la classe Option" << std::endl;
  std::cout << " 6. Tests des operateurs << et >> de la classe Model" << std::endl;
  std::cout << " 7. Tests de l'operateur << de la classe Car" << std::endl;
  std::cout << " 8. Tests des operateurs de pre/post decrementation de la classe Option" << std::endl;
  std::cout << " 9. Tests de l'opérateur [] de Car" << std::endl;
  std::cout << "10. Quitter" << std::endl << std::endl;

  int ch;
  std::cout << "  Choix : ";
  std::cin >> ch; // Faites pas le biess !
  std::cin.ignore();
  return ch;
}

/*******************************************************************************************************/
/*** Tests des operateurs = de la classe Car ***********************************************************/
/*******************************************************************************************************/
void Essai1()
{
  std::cout << "********************************************************************" << std::endl;
  std::cout << "(1) ***** Tests de l'operateur d'affectation de Car ****************" << std::endl;
  std::cout << "********************************************************************" << std::endl;
  {
    Car c1("Projet_208_MrDugenou",Model("208 Access 1.0",68,Engine::Petrol,12500.0f));
    c1.addOption(Option("0MM0","Peinture metallisee",450.0f));
    c1.addOption(Option("ZH75","Jante alliage leger 15 pouces",450.0f));
    std::cout << "---- c1 (avant affectation) --------------------" << std::endl;
    c1.display();
    {
      Car c2;
      std::cout << ">>>>> c2 = c1;  (+ on retire une option)" << std::endl;
      c2 = c1;
      c2.removeOption("0MM0");
      std::cout << "---- c2 ----------------------------" << std::endl;
      c2.display();
      // Destruction de c2
    }
    std::cout << "---- c1 (apres affectation) -------------------------" << std::endl;
    c1.display();
  }
}

/*******************************************************************************************************/
/*** Tests des operateurs + de la classe Car ***********************************************************/
/*******************************************************************************************************/
void Essai2()
{
  std::cout << std::endl << "********************************************************************" << std::endl;
  std::cout <<              "(2) ***** Tests des operateurs + de Car ****************************" << std::endl;
  std::cout <<              "********************************************************************" << std::endl;
  
  Car c("Projet_208_MrDugenou",Model("208 Access 1.0",68,Engine::Petrol,12500.0f)),c2;
  std::cout << "---- c (avant) --------------------------" << std::endl;
  c.display();
  {
    Option op1("VD09","Vitres laterales arriere surteintees",150.0f);
    Option op2("0MM0","Peinture metallisee",450.0f);
    std::cout << ">>>>> c2 = c + op1;" << std::endl;
    c2 = c + op1;
    std::cout << ">>>>> c2 = c2 + Option(...Pack Cuir...);" << std::endl;
    c2 = c2 + Option("0P3U","Pack Cuir ambiance Mistral",1100.0f);
    std::cout << ">>>>> c2 = op2 + c2;" << std::endl;
    c2 = op2 + c2;
  }
  std::cout << "---- c (apres) --------------------------" << std::endl; // c ne doit pas etre modifie !!!!
  c.display();
  std::cout << "---- c2 (c + 3 options) ------------------------" << std::endl;
  c2.display();
}

/*******************************************************************************************************/
/*** Tests des opérateurs - de la classe Car ***********************************************************/
/*******************************************************************************************************/
void Essai3()
{
  std::cout << std::endl << "********************************************************************" << std::endl;
  std::cout <<              "(3) ***** Tests des operateurs - de Car ****************************" << std::endl;
  std::cout <<              "********************************************************************" << std::endl;

  Car c3("Projet_3008_MrLegrand",Model("3008 Acces 1.6",120,Engine::Petrol,25030.0f));
  c3 = c3 + Option("ZV02","Vision tete haute",350.0f);
  c3 = c3 + Option("OK01","Toit panoramique vitre",500.0f);
  c3 = c3 + Option("0MM0","Peinture metallisee",570.0f);
  std::cout << "----- c3 (avant) -----------------" << std::endl;
  c3.display();
  c3 = c3 - Option("ZV02","Vision tete haute",350.0f);  // !!!
  c3 = c3 - "0MM0";                                     // !!!
  std::cout << "----- c3 (apres) ------------------" << std::endl;
  c3.display();
}

/*******************************************************************************************************/
/*** Test des opérateurs < > == de la classe Car *******************************************************/
/*******************************************************************************************************/
void Essai4()
{
  std::cout << "**********************************************************************" << std::endl;
  std::cout << "(4) Tests des opérateurs < > == de Car *******************************" << std::endl;
  std::cout << "**********************************************************************" << std::endl;

  Car c1("Projet1_208_MrDugenou",Model("208 Access 1.0",68,Engine::Petrol,12500.0f));
  c1.addOption(Option("0MM0","Peinture metallisee",450.0f));
  std::cout << "---- Projet 1 --------------------" << std::endl;
  c1.display();
  std::cout << "Prix du projet 1 = " << c1.getPrice() << " euros" << std::endl << std::endl;

  Car c2("Projet2_208_MrDugenou",Model("208 Access 1.0",68,Engine::Petrol,12500.0f));
  c2 = c2 + Option("0MM0","Peinture metallisee",450.0f);
  c2 = c2 + Option("ZH75","Jante alliage leger 15 pouces",450.0f);
  std::cout << "---- Projet 2 --------------------" << std::endl;
  c2.display();
  std::cout << "Prix du projet 2 = " << c2.getPrice() << " euros" << std::endl << std::endl;

  std::cout << "---- Comparaison des projets -------------------" << std::endl;
  if (c1 < c2) std::cout << "Le projet 1 est moins cher" << std::endl;
  if (c1 > c2) std::cout << "Le projet 1 est plus cher" << std::endl;
  if (c1 == c2) std::cout << "Les deux projets ont le meme prix" << std::endl;
}

/*******************************************************************************************************/
/*** Test des opérateurs << et >> de la classe Option **************************************************/
/*******************************************************************************************************/
void Essai5()
{
  std::cout << "**********************************************************************" << std::endl;
  std::cout << "(5) ***** Tests des opérateurs << et >> de Option ********************" << std::endl;
  std::cout << "**********************************************************************" << std::endl;
  Option o;
  std::cout << "Saisissez une nouvelle option :" << std::endl;
  std::cin >> o;
  std::cout << std::endl << "Voici l'option que vous avez encodee :" << std::endl;
  std::cout << o << std::endl << std::endl;
}

/*******************************************************************************************************/
/*** Test des opérateurs << et >> de la classe Model ***************************************************/
/*******************************************************************************************************/
void Essai6()
{
  std::cout << "**********************************************************************" << std::endl;
  std::cout << "(6) ***** Tests des opérateurs << et >> de Model *********************" << std::endl;
  std::cout << "**********************************************************************" << std::endl;
  Model m;
  std::cout << "Saisissez un nouveau modele :" << std::endl;
  std::cin >> m;
  std::cout << std::endl << "Voici le modele que vous avez encode :" << std::endl;
  std::cout << m << std::endl << std::endl;
}

/*******************************************************************************************************/
/*** Test de l'opérateur << de la classe Car ***********************************************************/
/*******************************************************************************************************/
void Essai7()
{
  std::cout << "**********************************************************************" << std::endl;
  std::cout << "(7) ***** Tests de l'opérateur << de Car *****************************" << std::endl;
  std::cout << "**********************************************************************" << std::endl;
  Car c("Projet_208_MrLagalere",Model("208 Access 1.0",68,Engine::Petrol,12500.0f));
  std::cout << std::endl << "Voici le projet de Car (sans option) :" << std::endl;
  std::cout << c << std::endl;

  c.addOption(Option("0MM0","Peinture metallisee",450.0f));
  c.addOption(Option("ZH75","Jante alliage leger 15 pouces",450.0f));
  c.addOption(Option("UB01","Detecteur obstacles arriere",250.0f));

  std::cout << std::endl << "Voici le projet de voiture (avec options) :" << std::endl;
  std::cout << c << std::endl;
}

/*******************************************************************************************************/
/*** Tests des operateurs de pre/post decrementation de la classe Option *******************************/
/*******************************************************************************************************/
void Essai8()
{
  std::cout << "**********************************************************************" << std::endl;
  std::cout << "(8.a) ***** Test de l'operateur de pre-decrementation ****************" << std::endl;
  std::cout << "**********************************************************************" << std::endl;
  Option op1("0MM0","Peinture metallisee",450.0f);
  std::cout << "Affichons d'abord op1 : " << op1 << std::endl;
  std::cout << "Resultat de std::cout << --op1 << std::endl; :" << std::endl;  
  std::cout << --op1 << std::endl;        // Si tout va bien, op1 est decremente avant d'etre affiche !
  std::cout << "et on reaffiche op1 : " << op1 << std::endl << std::endl;

  std::cout << "**********************************************************************" << std::endl;
  std::cout << "(8.b) ***** Test de l'operateur de post-decrementation ***************" << std::endl;
  std::cout << "**********************************************************************" << std::endl;
  Option op2("ZH75","Jantes alliage 15 pouces",350.0f);
  std::cout << "Affichons d'abord op2 : " << op2 << std::endl;
  std::cout << "Resultat de std::cout << op2-- << std::endl; :" << std::endl;  
  std::cout << op2-- << std::endl;        // Si tout va bien, op2 est decremente apres avoir ete affiche !
  std::cout << "et on reaffiche op2 : " << op2 << std::endl << std::endl;
}

/*******************************************************************************************************/
/*** Tests de l'opérateur [] de la classe Car **********************************************************/
/*******************************************************************************************************/
void Essai9()
{
  std::cout << "**********************************************************************" << std::endl;
  std::cout << "(9) ***** Tests de l'opérateur [] de Car *****************************" << std::endl;
  std::cout << "**********************************************************************" << std::endl;
  Car c("Projet_208_MrLagalere",Model("208 Access 1.0",68,Engine::Petrol,12500.0f));
  std::cout << std::endl << "Voici le projet de Car (sans option) :" << std::endl;
  std::cout << c << std::endl;

  c.addOption(Option("0MM0","Peinture metallisee",450.0f));
  c.addOption(Option("ZH75","Jante alliage leger 15 pouces",450.0f));
  c.addOption(Option("UB01","Detecteur obstacles arriere",250.0f));
  c.addOption(Option("OK01","Toit panoramique vitre",500.0f));
  c = c - "ZH75";

  std::cout << std::endl << "Voici le projet de voiture (avec options) :" << std::endl;
  std::cout << c << std::endl;

  std::cout << std::endl << "Voici les options affichées une à une :" << std::endl;
  for (int i=0 ; i<5 ; i++)
  {
    std::cout << i << " : ";
    if (c[i] != nullptr) std::cout << *(c[i]) << std::endl;
    else std::cout << "---" << std::endl;
  }
}

