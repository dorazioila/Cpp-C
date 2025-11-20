#include <iostream>
using namespace std;

#include "Person.h"
#include "Client.h"
#include "Employee.h"

int  Menu();
void Essai1();
void Essai2();
void Essai3();
void Essai4();
void Essai5();
void Essai6();

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
      case 5 : Essai5(); break;
      case 6 : Essai6(); break;
      default : fini = true ; break;
    }
  }

  return 0;
}

int Menu()
{
  cout << endl;
  cout << "----------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 4 ----------------------------------------------------------" << endl;
  cout << "----------------------------------------------------------------------------" << endl;
  cout << " 1. Test de la classe Person" << endl;
  cout << " 2. Test de la classe Client" << endl;
  cout << " 3. Test de la classe Employee" << endl;
  cout << " 4. Heritage et virtualite : Test des methodes virtuelles" << endl;
  cout << " 5. Test du downcasting et du dynamic-cast" << endl;
  cout << " 6. Test des variables statiques de la classe Employee" << endl;
  cout << " 7. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  cin.ignore();
  return ch;
}

/***********************************************************************************************/
// A FAIRE : la classe Person qui contient le lastName (string) et le firstName (string) d'une Person  
//           les methodes << et >> de Person
//           l'operateur d'affectation (=) de Person
void Essai1()
{
  cout << "----- 1.1 Test du constructeur par defaut de Person ------------------------" << endl;
  Person p1;
  cout << "--> Voici p1 : " << p1 << endl;
  cout << endl;
 
  cout << "----- 1.2 Test du constructeur d'initialisation de Person ------------------" << endl;
  Person p2("Wagner","Jean-Marc");
  cout << "--> Voici p2 : " << p2 << endl;
  cout << endl;

  cout << "----- 1.3 Test du constructeur de copie de Person --------------------------" << endl;
  Person p3(p2);
  cout << "--> Voici p3 : " << p3 << endl;
  cout << endl;

  cout << "----- 1.4 Test des getXXX et setXXX de Person ------------------------------" << endl;
  p3.setLastName("Quettier");
  p3.setFirstName("Patrick");
  cout << "Nom : " << p3.getLastName() << endl;
  cout << "Prenom : " << p3.getFirstName() << endl;
  cout << endl;

  cout << "----- 1.5 Test de l'operateur >> de Person ---------------------------------" << endl;
  cout << "Encodez une Person : " << endl;
  cin >> p3;
  cout << "Voici la Person encodee : " << p3 << endl;
  cout << endl;

  cout << "----- 1.6 Test de l'operateur = de Person -----------------------------------" << endl;
  p1 = p3;
  cout << "Voici p1 apres affectation : " << p1 << endl;
}

/***********************************************************************************************/
// A FAIRE : la classe abstraite Actor qui hérite de Person et qui possède un id (int)
//           et les deux méthodes virtuelles pures tuple() et toString()
//           la classe Client qui herite de Actor, contenant en plus un numero de gsm (string)
void Essai2()
{
  cout << "----- 2.1 Test du constructeur par defaut ----------------------------------" << endl;
  Client c1;
  cout << "--> Voici c1 : " << c1 << endl;
  cout << endl;

  cout << "----- 2.2 Test des setters -------------------------------------------------" << endl;
  c1.setLastName("Lagalere");
  c1.setFirstName("Pierre");
  c1.setId(17);
  c1.setGsm("0498/15.23.69");
  cout << "--> Voici c1 (apres les setters) : " << c1 << endl;
  cout << endl;
  
  cout << "----- 2.3 Test des getters -------------------------------------------------" << endl;
  cout << "Nom    : " << c1.getLastName() << endl;
  cout << "Prenom : " << c1.getFirstName() << endl;
  cout << "Id     : " << c1.getId() << endl;
  cout << "GSM    : " << c1.getGsm() << endl;
  cout << endl;

  cout << "----- 2.4 Test du constructeur d'initialisation ----------------------------" << endl;
  Client c2("Issier","Pol",41,"0485/12.12.23");
  cout << "--> Voici c2 : " << c2 << endl; 
  cout << endl;

  cout << "----- 2.5 Test des methodes tuple() et toString()  -------------------------" << endl;
  cout << "--> Pour c2 : " << endl;
  cout << "toString() : --" << c2.toString() << "--" << endl;
  cout << "tuple()    : --" << c2.tuple() << "--" << endl; 
  cout << endl;

  cout << "----- 2.6 Allocation dynamique de Client avec pointeur de type Client + test du constructeur de copie ------" << endl;
  cout << "--> Copie de c2..." << endl;
  Client *p1 = new Client(c2); // Vive le constructeur de copie !
  cout << "--> Voici la copie de c2 : " << *p1 << endl;
  cout << "--> Destruction de la copie..." << endl;
  delete p1;
  cout << "--> Revoici c2 : " << c2 << endl;
  cout << endl;

  cout << "----- 2.7 Test de l'operateur d'affectation --------------------------------" << endl;
  Client c3;
  cout << "--> Execution du code c3 = c2; :" << endl;
  c3 = c2;
  cout << "--> c3 = " << c3 << endl;
}

/***********************************************************************************************/
// A FAIRE : la classe Employee qui herite de Actor
//           contenant en plus une fonction (string), un login (string) et un mot de passe (string)
//           deux variables statiques constantes SELLER et ADMINISTRATIVE
void Essai3()
{
  cout << "----- 3.1 Test du constructeur par defaut ----------------------------------" << endl;
  Employee e1;
  cout << "--> Voici e1 : " << e1 << endl;
  cout << endl;

  cout << "----- 3.2 Test des setters -------------------------------------------------" << endl;
  e1.setLastName("Tombale");
  e1.setFirstName("Pierre");
  e1.setId(4);
  e1.setLogin("tombpier");
  e1.setPassword("azerty34");
  e1.setRole("Vendeur");
  cout << "--> Voici e1 (apres les setters) :" << e1 << endl;
  cout << endl;

  cout << "----- 3.3 Test des getters -------------------------------------------------" << endl;
  cout << "Nom          : " << e1.getLastName() << endl;
  cout << "Prenom       : " << e1.getFirstName() << endl;
  cout << "Id           : " << e1.getId() << endl;
  cout << "Login        : " << e1.getLogin() << endl;
  cout << "Mot de passe : " << e1.getPassword() << endl;
  cout << "Fonction     : " << e1.getRole() << endl;
  cout << endl;

  cout << "----- 3.4 Test du constructeur d'initialisation ----------------------------" << endl;
  Employee e2("Dugenou","Jean-Paul",2,"dugejean","Administratif");
  // Le pointeur password est initialise a nullptr. Le mot de passe ne peut etre modifie (intialise)
  // qu'avec la methode setPassword ou resetPassword (qui remet le pointeur a nullptr).
  e2.setPassword("qsdf1234");
  cout << "--> Voici e2 : " << e2 << endl; 
  cout << "Son mot de passe est : " << e2.getPassword() << endl;
  cout << endl;

  cout << "----- 3.5 Test des methodes tuple() et toString()  -------------------------" << endl;
  cout << "--> Pour e2 : " << endl;
  cout << "toString() : --" << e2.toString() << "--" << endl;
  cout << "tuple()    : --" << e2.tuple() << "--" << endl; 
  cout << endl;

  cout << "----- 3.6 Allocation dynamique de Employee + test du constructeur de copie ------" << endl;
  cout << "--> Copie de e2..." << endl;
  Employee *p1 = new Employee(e2); // Vive le constructeur de copie !
  // Le constructeur de copie copie tout, y compris le mot de passe
  cout << "--> Voici la copie de e2 : " << *p1 << endl;
  cout << "Son mot de passe est : " << p1->getPassword() << endl;
  cout << "--> Destruction de la copie..." << endl;
  delete p1;
  cout << "--> Revoici e2 :" << e2 << endl;
  cout << "Son mot de passe est : " << e2.getPassword() << endl;
  cout << endl;

  cout << "----- 3.7 Test de l'operateur d'affectation --------------------------------" << endl;
  Employee e3;
  cout << "--> Execution du code e3 = e2; :" << endl;
  e3 = e2;
  cout << "--> e3 = " << e3 << endl;
}

/******************************************************************************************/
// A FAIRE : normalement rien dans vos classes...
//           juste comprendre et tester le code ci-dessous
void Essai4()
{
  srand((unsigned)time(NULL));

  cout << "----- 4.1 Allocation dynamique d'actors --------------------------------" << endl;
  Actor* actors[10];

  for (int i=0 ; i<10 ; i++)   // Tracez vos constructeurs !!!
  {
    cout << endl << "actors[" << i << "] : ";
    int n = rand()%3;
    switch(n)
    {
      case 0 : actors[i] = new Client("Issier","Pol",41,"0485/12.12.23");
               cout << "Client" << endl;
               break;

      case 1 : actors[i] = new Employee("Dugenou","Jean-Paul",2,"dugejean","Administratif");
               cout << "Employee (Administratif)" << endl;
               break;

      case 2 : actors[i] = new Employee("Coptere","Eli",7,"copteeli","Vendeur");
               cout << "Employee (Vendeur)" << endl;
               break;
    }
  }
  cout << endl;

  cout << "----- 4.2 Test des methodes VIRTUELLE toString() et tuple() ---------------------------------------------" << endl;
  for (int i=0 ; i<10 ; i++)
  {
    cout << endl << "actors[" << i << "] : " << actors[i]->toString();
    cout << endl << "actors[" << i << "] : " << actors[i]->tuple() << endl;
  }
  cout << endl;
  
  cout << "----- 4.3 Liberation memoire ----------------------------------------------------------------------------" << endl;
  for (int i=0 ; i<10 ; i++) delete actors[i];  // Tout se passe-t-il comme vous voulez ?
  // Pour etre plus precis, quid des destructeurs et de la virtualite ?
}

/*********************************************************************************************/
// A FAIRE : normalement rien dans vos classes...
//           juste comprendre et tester le code ci-dessous
void Essai5()
{
  srand((unsigned)time(NULL));

  cout << "----- 5.1 Allocation dynamique d'actors --------------------------------" << endl;
  Actor* actors[10];

  for (int i=0 ; i<10 ; i++)   // Tracez vos constructeurs !!!
  {
    cout << endl << "actors[" << i << "] : ";
    int n = rand()%2;
    switch(n)
    {
      case 0 : actors[i] = new Client("Issier","Pol",41,"0485/12.12.23");
               cout << "Client" << endl;
               break;

      case 1 : actors[i] = new Employee("Coptere","Eli",7,"copteeli","Vendeur");
               cout << "Employee" << endl;
               break;
    }
  }
  cout << endl;

  cout << "----- 5.2 Test du downcasting et dynamic-cast ------------------------------" << endl;
  for (int i=0 ; i<10 ; i++)
  {
    cout << "actors[" << i << "] ";
    Client* pClient = dynamic_cast<Client*>(actors[i]);
    if (pClient != NULL) 
    {
      cout << "est un Client" << endl;
      cout << "--> GSM = " << pClient->getGsm() << endl;
    }
    Employee* pEmployee = dynamic_cast<Employee*>(actors[i]);
    if (pEmployee != NULL) 
    {
      cout << "est un Employee" << endl;
      cout << "--> fonction = " << pEmployee->getRole() << endl;
    }
  }
  cout << endl;

  cout << "----- 5.3 Liberation memoire ----------------------------------------------------------------------------" << endl;
  for (int i=0 ; i<10 ; i++) delete actors[i];
}

/******************************************************************************************/
// A FAIRE : Les deux variables statiques ADMINISTRATIVE et SELLER (const string) de la classe Employee
void Essai6()
{
  cout << "Les deux fonctions possibles pour un Employee sont :" << endl;
  cout << " - " << Employee::ADMINISTRATIVE << endl;
  cout << " - " << Employee::SELLER << endl << endl;

  Employee e("Dugenou","Jean-Paul",2,"dugejean",Employee::ADMINISTRATIVE);
  cout << e << endl;
  e.setRole(Employee::SELLER);
  cout << e << endl;
}
