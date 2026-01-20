#include "Model.h"
#include <iostream>
#include <cstring>
#include <limits>

using namespace carconfig;

Model::Model() 
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

namespace carconfig {

std::ostream& operator<<(std::ostream& os, const Model& mod) 
{
    os << "Nom : " << mod.getName() << std::endl;
    os << "Puissance : " << mod.getPower() << std::endl;
    os << "Moteur : " << mod.getEngine() << std::endl; // !!!
    os << "Prix de base : " << mod.getBasePrice() << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Model& mod) 
{
    char buffer[100];
    int power;
    int engineInt;
    float basePrice;

    std::cout << "Entrez le nom du modèle : ";
    is.getline(buffer, 100);
    mod.setName(buffer);

    std::cout << "Entrez la puissance (en ch) : ";
    is >> power;
    mod.setPower(power);

    std::cout << "Entrez le type de moteur (0: Petrol, 1: Diesel, 2: Electric, 3: Hybrid) : ";
    is >> engineInt;
    if (engineInt >= 0 && engineInt <= 3) {
        mod.setEngine(static_cast<Engine>(engineInt));
    } else {
        mod.setEngine(Engine::Petrol); 
    }

    std::cout << "Entrez le prix de base : ";
    is >> basePrice;
    mod.setBasePrice(basePrice);

    
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return is;
}

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
