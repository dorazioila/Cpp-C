#include "Model.h"
#include <iostream>
#include <cstring>

using namespace carconfig;

Model::Model() // constructeur par défaut
{
    name = nullptr;
    setName("default");
    setPower(80);
    setEngine(Engine::Petrol);
    setBasePrice(15000);
}

Model::Model(const char* n, int p, Engine e, float bp) 
{
    name = nullptr;
    if (n != nullptr) {
        setName(n);
    }
    setPower(p);
    setEngine(e);
    setBasePrice(bp);
}

Model::Model(const Model& mod) 
{
    name = nullptr;
    if (mod.getName() != nullptr) {
        setName(mod.getName());
    }
    setPower(mod.getPower());
    setEngine(mod.getEngine());
    setBasePrice(mod.getBasePrice());
}

Model& Model::operator=(const Model& mod) 
{
    if (this != &mod) {
        setName(mod.getName());
        setPower(mod.getPower());
        setEngine(mod.getEngine());
        setBasePrice(mod.getBasePrice());
    }
    return *this;
}

Model::~Model()
{
    if (name != nullptr) {
        delete[] name;
        name = nullptr;
    }
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
    if (n == nullptr) {
        return;
    }
    if (name != nullptr) delete[] name;
    name = new char[strlen(n)+1];
    strcpy(name,n);
}

const char* Model::getName() const
{
    if (name == nullptr) {
        return "";
    }
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
    std::cout << "Nom : " << getName() << std::endl;
    std::cout << "Puissance : " << getPower() << std::endl;
    std::cout << "Moteur : " << getEngine() << std::endl; // !!!
    std::cout << "Prix de base : " << getBasePrice() << std::endl;
}
