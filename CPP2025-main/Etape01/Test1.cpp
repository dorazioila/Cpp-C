#include <iostream>
using namespace std;
#include "Model.h"

// Quelques conseils avant de commencer...
// * N'oubliez pas de tracer (cout << ...) tous les constructeurs et le destructeur !!! Ca, c'est pas un conseil,
//   c'est obligatoire :-)
// * N'essayez pas de compiler ce programme entierement immediatement. Mettez tout en commentaires
//   sauf le point (1) et creez votre classe (dans ce fichier pour commencer) afin de compiler et tester 
//   le point (1). Une fois que cela fonctionne, decommentez le point (2) et modifier votre classe en 
//   consequence. Vous developpez, compilez et testez donc etape par etape. N'attendez pas d'avoir encode 
//   300 lignes pour compiler...
// * Une fois que tout le programme compile et fonctionne correctement, creez le .h contenant la declaration
//   de la classe, le .cpp contenant la definition des methodes, et ensuite le makefile permettant de compiler
//   le tout grace a la commande make 

int main()
{
  cout << endl << "(1) ***** Test constructeur par defaut + display ************************" << endl;
  {
    Model model;
    model.display();
  } // La presence des accolades assure que le destructeur de Model sera appele --> a tracer !

  
  cout << endl << "(2) ***** Test des setters et getters ***********************************" << endl;
  {
    Model model;
    model.setName("208 Active 1.5 BlueHDi 5P");
    model.setPower(100);
    model.setEngine(Engine::Diesel);
    model.setBasePrice(21800.0f);
    model.display();
    cout << "Nom          = " << model.getName() << endl;
    cout << "Puissance    = " << model.getPower() << " Ch" << endl;
    cout << "Moteur       = " << model.getEngine() << endl;
    cout << "Prix de base = " << model.getBasePrice() << " euros" << endl;
  }

  cout << endl << "(3) ***** Test du constructeur d'initialisation *************************" << endl;
  {
    Model model("308 Allure 1.6 Hybrid 5P",150,Engine::Hybrid,38650.0f);
    model.display();
  }

  cout << endl << "(4) ***** Test du constructeur de copie *********************************" << endl;
  {
    Model model1("2008 GT 1.2 PureTech 130 Man.6",130,Engine::Petrol,31400.0f);
    cout << "model1 (AVANT) :" << endl;
    model1.display();
    {   
      Model model2(model1);
      cout << "model2 :" << endl;
      model2.display();
      model2.setName("2008 GT 1.2 PureTech 130 EAT8");
      model2.display();
    } // de nouveau, les {} assurent que model2 sera detruit avant la suite
    cout << "model1 (APRES) :" << endl;
    model1.display();
  }

  cout << endl << "(5) ***** Test d'allocation dynamique (constructeur par defaut) *********" << endl;
  {
    Model *p = new Model();
    p->setName("308 Allure 1.5 BlueHDi 5P");
    p->setPower(130);
    p->setEngine(Engine::Diesel);
    p->setBasePrice(31650.0f);
    p->display();
    cout << "Le prix de base de ce model est : " << p->getBasePrice() << " euros" << endl;
    delete p;
  }

  cout << endl << "(6) ***** Test d'allocation dynamique (constructeur de copie) ***********" << endl;
  {
    Model model1("508 GT 1.6 Hybrid 225 EAT8",225,Engine::Hybrid,50100.0f);
    cout << "model1 (AVANT) :" << endl;
    model1.display();
    Model* p = new Model(model1);
    cout << "La copie :" << endl;
    p->display();
    cout << "Destruction de la copie..." << endl; 
    delete p;
    cout << "model1 (APRES) :" << endl;
    model1.display();
  }

  return 0;
}
