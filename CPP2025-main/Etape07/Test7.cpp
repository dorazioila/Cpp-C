#include <iostream>
#include "Client.h"
#include "XmlFileSerializer.hpp"

using namespace std;

int  Menu();
void Essai1();
void Essai2();
void Essai3();

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
      default : fini = true ; break;
    }
  }

  return 0;
}

int Menu()
{
  cout << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 7 ---------------------------------------------------------" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << " 1. Test en ecriture du template XmlFileSerializer avec des entiers" << endl;
  cout << " 2. Test en lecture du template XmlFileSerializer avec des entiers" << endl;
  cout << " 3. Test du template XmlFileSerializer avec des objets Client" << endl;
  cout << " 4. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  cin.ignore();
  return ch;
}

/*******************************************************************************************************/
void Essai1()
{
  cout << "----- 1. Test en écriture du template XmlFileSerializer avec des entiers --------------------" << endl;
  cout << "----- 1.1 Creation du fichier ---------------------------------------------------------------" << endl;
  XmlFileSerializer<int> fsw("integers.xml",XmlFileSerializer<int>::WRITE,"integers");
  cout << "Filename = " << fsw.getFilename() << endl;
  cout << "Collection name  = " << fsw.getCollectionName() << endl;
  cout << "Readable = " << fsw.isReadable() << endl;
  cout << "Writable = " << fsw.isWritable() << endl << endl;

  cout << "----- 1.2 Ecriture dans le fichier ----------------------------------------------------------" << endl;
  for (int i=1 ; i<15 ; i+=2) {
    cout << i << endl;
    fsw.write(i);
  }

  cout << "----- 1.3 Tentative de lecture dans le fichier ouvert en écriture ---------------------------" << endl;
  try {
    int val = fsw.read();
    cout << "val = " << val << endl << endl;
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
  }
}

/*******************************************************************************************************/
void Essai2()
{
  cout << "----- 2. Test en lecture du template XmlFileSerializer avec des entiers ---------------------" << endl;
  cout << "----- 2.1 Test d'ouverture d'un fichier non existant ----------------------------------------" << endl;
  try {
    XmlFileSerializer<int> fsr("XXX.xml",XmlFileSerializer<int>::READ);
    cout << "Filename = " << fsr.getFilename() << endl;
    cout << "Collection name = " << fsr.getCollectionName() << endl;
    cout << "Readable = " << fsr.isReadable() << endl;
    cout << "Writable = " << fsr.isWritable() << endl << endl;
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl << endl;
  }

  cout << "----- 2.2 Tentative d'écriture dans le fichier ouvert en lecture ----------------------------" << endl;
  try {
    XmlFileSerializer<int> fsr("integers.xml",XmlFileSerializer<int>::READ);
    cout << "Filename = " << fsr.getFilename() << endl;
    cout << "Collection name = " << fsr.getCollectionName() << endl;
    cout << "Readable = " << fsr.isReadable() << endl;
    cout << "Writable = " << fsr.isWritable() << endl << endl;
    fsr.write(17); // !!!
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
  }

  cout << "----- 2.3 Lecture dans le fichier -----------------------------------------------------------" << endl;
  XmlFileSerializer<int> *fsr = nullptr;
  try {
    fsr = new XmlFileSerializer<int>("integers.xml",XmlFileSerializer<int>::READ);
    cout << "Filename = " << fsr->getFilename() << endl;
    cout << "Collection name = " << fsr->getCollectionName() << endl;
    cout << "Readable = " << fsr->isReadable() << endl;
    cout << "Writable = " << fsr->isWritable() << endl << endl;
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
  }

  if (fsr != nullptr) {
    cout << "Debut de lecture..." << endl;
    bool end = false;
    while (!end) {
      try {
        int val = fsr->read();
        cout << "Lu : " << val << endl;
      } catch(const XmlFileSerializerException& e) {
        if (e.getCode() == XmlFileSerializerException::END_OF_FILE) { 
          end = true;
          cout << "Fin de fichier atteinte." << endl;
        } else {
          cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
        }
      }
    }
    cout << "Fin de lecture." << endl;
    delete fsr;
  }
}

/*******************************************************************************************************/
void Essai3()
{
  cout << "----- 3. Test du template XmlFileSerializer avec des objets Client --------------------------" << endl;
  cout << "----- 3.1 Creation du fichier ---------------------------------------------------------------" << endl;
  XmlFileSerializer<Client> *fsw = new XmlFileSerializer<Client>("clients.xml",XmlFileSerializer<Client>::WRITE,"clients");
  cout << "Filename = " << fsw->getFilename() << endl;
  cout << "Collection name = " << fsw->getCollectionName() << endl;
  cout << "Readable = " << fsw->isReadable() << endl;
  cout << "Writable = " << fsw->isWritable() << endl << endl;

  cout << "----- 3.2 Ecriture dans le fichier ----------------------------------------------------------" << endl;
  fsw->write(Client("Wagner","Jean-Marc",11,"0476.12.45.98"));
  fsw->write(Client("Quettier","Patrick",3,"0479.18.35.08"));
  fsw->write(Client("Leonard","Annne",17,"0495.11.22.88"));

  delete fsw; // pour forcer la fermeture du fichier

  cout << "----- 3.3 Lecture dans le fichier -----------------------------------------------------------" << endl;
  XmlFileSerializer<Client> *fsr = nullptr;
  try {
    fsr = new XmlFileSerializer<Client>("clients.xml",XmlFileSerializer<Client>::READ);
    cout << "Filename = " << fsr->getFilename() << endl;
    cout << "Collection name = " << fsr->getCollectionName() << endl;
    cout << "Readable = " << fsr->isReadable() << endl;
    cout << "Writable = " << fsr->isWritable() << endl << endl;
  } catch(const XmlFileSerializerException& e) {
    cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
  }

  if (fsr != nullptr) {
    cout << "Debut de lecture..." << endl;
    bool end = false;
    while (!end) {
      try {
        Client val = fsr->read();
        cout << "Lu : " << val.toString() << endl;
      } catch(const XmlFileSerializerException& e) {
        if (e.getCode() == XmlFileSerializerException::END_OF_FILE) { 
          end = true;
          cout << "Fin de fichier atteinte." << endl;
        } else {
          cout << "Erreur : " << e.getMessage() << " (code = " << e.getCode() << ")" << endl;
        }
      }
    }
    cout << "Fin de lecture." << endl;
    delete fsr;
  }
}
