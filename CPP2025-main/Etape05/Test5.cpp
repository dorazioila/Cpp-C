#include <iostream>
#include <string>
#include "Option.h"
#include "OptionException.h"
#include "Car.h" 
#include "Employee.h"
#include "PasswordException.h"

using namespace std;
using namespace carconfig;

/**********************************************************************************************/
/*                                                                                            */
/*                                     A T T E N T I O N                                      */
/*                                                                                            */
/*                             Ce jeu de tests est à compléter !                              */
/*                                                                                            */
/**********************************************************************************************/

int  Menu();
void Essai1();
void Essai2();
void Essai3();
void Essai4();

int main()
{
  int choix;
  bool fini = false;
  srand((unsigned)time(NULL));

  while(!fini)
  {
    choix = Menu();
    switch(choix)
    {
      case 1 : Essai1(); break;
      case 2 : Essai2(); break;
      case 3 : Essai3(); break;
      case 4 : Essai4(); break;
      default : fini = true ; break;
    }
  }

  exit(0);
}

int Menu()
{
  cout << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 5 ---------------------------------------------------------" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << " 1. Test des methodes de Option susceptibles de lancer une OptionException" << endl;
  cout << " 2. Test des methodes de Car susceptibles de lancer une OptionException" << endl;
  cout << " 3. Test des methodes de Employee susceptibles de lancer une PasswordException" << endl;
  cout << " 4. Gestion de plusieurs exceptions simultanement" << endl;
  cout << " 5. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  cin.ignore();
  return ch;
}

/**********************************************************************************************/
// ATTENTION !!!!
// Les methodes de vos classes NE doivent PAS contenir de TRY{...} CATCH{...} mais
// uniquement des THROW !!! Donc, votre classe lance une exception (une erreur) mais
// ce n'est pas elle qui la traite. C'est l'application qui utilise votre classe
// qui doit traiter les exceptions. C'est donc uniquement dans le main (ou les fonctions appelees)
// que l'on trouve des try...catch 
/**********************************************************************************************/
void Essai1()
{
  cout << "----- 1. Test des methodes de Option susceptibles de lancer une OptionException --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee

  try
  {
    cout << "----- 1.1 Test des setters la classe Option -----------------------------------" << endl;
    Option o1;
    string c,l;
    float p;
    cout << "Encodez une option :" << endl;
    cout << "Code = ";
    getline(cin,c);
    o1.setCode(c);   // !!!
    cout << "Intitule = ";
    getline(cin,l);
    o1.setLabel(l);  // !!!
    cout << "Prix = ";
    cin >> p;
    cin.ignore();
    o1.setPrice(p);  // !!!
    cout << "Voici l'option encodee : " << o1 << endl << endl;

    cout << "----- 1.2 Test du constructeur d'initialisation de Option --------------------" << endl;
    cout << "Encodez une option :" << endl;
    cout << "Code = ";
    getline(cin,c);
    cout << "Intitule = ";
    getline(cin,l);
    cout << "Prix = ";
    cin >> p;
    cin.ignore();
    Option o2(c,l,p);  // !!!
    cout << "Voici l'option encodee : " << o2 << endl << endl;

    cout << "----- 1.3 Test de l'operateur -- de Option -----------------------------------" << endl;
    cout << "Ristourne de 50 euros sur la derniere option encodee..." << endl;
    o2--;  // !!!
    cout << "Voici l'option apres ristourne : " << o2 << endl;
    cout << "Nouvelle ristourne de 50 euros sur la derniere option encodee..." << endl;
    cout << "Voici l'option apres ristourne : " << --o2 << endl;  // !!!
  }
  catch (const OptionException& e)
  {
    cout << "ERREUR : " << e.what() << endl;
  }
  
  cout << endl;
}

/**********************************************************************************************/
void Essai2()
{
  cout << "----- 2. Test des methodes de Car susceptibles de lancer une OptionException --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee

  try
  {
    cout << "----- 2.1 Creation d'une voiture sans options -----------------------------------" << endl;
    Car c1("Projet_208_MrDugenou",Model("208 Access 1.0",68,Engine::Petrol,12500.0f));
    cout << c1 << endl;

    cout << "----- 2.2 Ajout d'options -------------------------------------------------------" << endl;
    Option opts[6];
    opts[0] = Option("0MM0","Peinture metallisee",450.0f);
    opts[1] = Option("ZH75","Jante alliage leger 15 pouces",450.0f);
    opts[2] = Option("UB01","Detecteur obstacles arriere",250.0f);
    opts[3] = Option("VH02","Volant croute de cuir noir",150.0f);
    opts[4] = Option("TC07","Toit ouvrant electrique vitre",800.0f);
    opts[5] = Option("WLQU","Systeme de navigation Europe",490.0f);
    cout << "Options disponibles :" << endl;
    cout << "0) FIN ajout options" << endl;
    for (int i=0 ; i<6 ; i++) cout << (i+1) << ") " << opts[i] << endl;
    int ch;
    do
    {
      cout << "Choix : ";
      cin >> ch;
      cin.ignore();
      if (ch>=1 && ch<=6) c1.addOption(opts[ch-1]);  // !!!
    } while (ch != 0);
    cout << endl;

    cout << "----- 2.3 La voiture apres l'ajout des options ----------------------------------" << endl;
    cout << c1 << endl;

    cout << "----- 2.4 On retire une option --------------------------------------------------" << endl;
    string codeOption;
    cout << "Code : ";
    getline(cin,codeOption);
    c1.removeOption(codeOption);  // !!!

    cout << "----- 2.4 La voiture apres le retrait de l'option -------------------------------" << endl;
    cout << c1 << endl;
  }
  catch (const OptionException& e)
  {
    cout << "ERREUR : " << e.what() << endl;
  }
  
  cout << endl;
}

/**********************************************************************************************/
void Essai3()
{
  cout << "----- 3. Test des methodes de Employee susceptibles de lancer une PasswordException --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : Tester le code de l'erreur et affiche la cause exacte de l'erreur.

  try
  {
    Employee e1("Dupont","Michel",2,"dupomich",Employee::ADMINISTRATIVE);
    cout << e1 << endl << endl;
    cout << "Voulez-vous encoder un mot de passe pour cet Employee (o/n) ? ";
    char ch;
    cin >> ch;
    cin.ignore();
    if (ch == 'o')
    {
      cout << "Encodez son mot de passe : ";
      string mdp;
      getline(cin,mdp);
      e1.setPassword(mdp);  // !!!
    }
    cout << "Affichage du mot de passe :" << endl;
    cout << "Mot de passe = " << e1.getPassword() << endl;  // !!!
  }
  catch (const PasswordException& e)
  {
    cout << "ERREUR : " << e.what() << endl;
    switch (e.getCode())
    {
      case PasswordException::INVALID_LENGTH:
        cout << "Cause : Le mot de passe doit contenir au moins 6 caracteres" << endl;
        break;
      case PasswordException::ALPHA_MISSING:
        cout << "Cause : Le mot de passe doit contenir au moins une lettre" << endl;
        break;
      case PasswordException::DIGIT_MISSING:
        cout << "Cause : Le mot de passe doit contenir au moins un chiffre" << endl;
        break;
      case PasswordException::NO_PASSWORD:
        cout << "Cause : L'employe ne possede pas de mot de passe" << endl;
        break;
      default:
        cout << "Cause : Erreur de mot de passe inconnue" << endl;
        break;
    }
  }
  
  cout << endl;
}

/**********************************************************************************************/
void Essai4()
{
  cout << "----- 4. Gestion de plusieurs exceptions simultanement ---" << endl;
  // A COMPLETER : Traitez TOUTES les exceptions susceptible d'etre lancee par le bloc de code suivant (try...catch)

  try
  {
    Option o;
    cout << "Encodez une option : " << endl;
    cin >> o;
    cout << "Voici l'option encodee : " << o << endl << endl;
    Employee e1("Dupont","Michel",2,"dupomich",Employee::ADMINISTRATIVE);
    cout << e1 << endl;
    cout << "Encodez son mot de passe : ";
    string mdp;
    cin.ignore();
    getline(cin,mdp);
    e1.setPassword(mdp);
    cout << "Affichage du mot de passe :" << endl;
    cout << "Mot de passe = " << e1.getPassword() << endl;
  }
  catch (const OptionException& e)
  {
    cout << "ERREUR D'OPTION : " << e.what() << endl;
  }
  catch (const PasswordException& e)
  {
    cout << "ERREUR DE MOT DE PASSE : " << e.what() << endl;
    switch (e.getCode())
    {
      case PasswordException::INVALID_LENGTH:
        cout << "Cause : Le mot de passe doit contenir au moins 6 caracteres" << endl;
        break;
      case PasswordException::ALPHA_MISSING:
        cout << "Cause : Le mot de passe doit contenir au moins une lettre" << endl;
        break;
      case PasswordException::DIGIT_MISSING:
        cout << "Cause : Le mot de passe doit contenir au moins un chiffre" << endl;
        break;
      case PasswordException::NO_PASSWORD:
        cout << "Cause : L'employe ne possede pas de mot de passe" << endl;
        break;
      default:
        cout << "Cause : Erreur de mot de passe inconnue" << endl;
        break;
    }
  }
  catch (const std::exception& e)
  {
    cout << "ERREUR STANDARD : " << e.what() << endl;
  }
  
  cout << endl;
}
