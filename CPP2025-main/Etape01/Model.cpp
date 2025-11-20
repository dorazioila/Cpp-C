#include "Model.h"

using namespace std;
#include <iostream>
#include <cstring>

Model::Model() // constructeur par défaut
{
    name = nullptr;
    setName("default");
    setPower(80);
    setEngine(Engine::Petrol);
    setBasePrice(15000);
}

Model::Model(const char* n, int p, Engine e, float bp) // constructeur d'initialisation
{
    name = nullptr;
    setName(n);
    setPower(p);
    setEngine(e);
    setBasePrice(bp);
}

Model::Model(const Model& mod) // constructeur de copie
{
    name = nullptr;
    setName(mod.getName());
    setPower(mod.getPower());
    setEngine(mod.getEngine());
    setBasePrice(mod.getBasePrice());
}

Model::~Model()
{
    if (name != nullptr) delete name;
}

void Model::setPower(int p)
{
    if(p >= 0) power = p;
}

int Model::getPower() const
{
    return power;
}

void Model::setName(const char* n)
{
    if (name != nullptr) delete name;
    name = new char[strlen(n)+1];
    strcpy(name,n);
}

const char* Model::getName() const
{
    return name;
}

void Model::setEngine(Engine e)
{
    engine = e;
}

Engine Model::getEngine() const
{
    return engine;
}

void Model::setBasePrice(float bp)
{
    basePrice = bp;
}

float Model::getBasePrice() const
{
    return basePrice;
}

void Model::display() const
{
    cout << "Nom : " << name << endl;
    cout << "Puissance : " << power << endl;
    cout << "Moteur : " << engine << endl; // !!!
    cout << "Prix de base : " << basePrice << endl;
}
