#include "Car.h"
#include "OptionException.h"

#include <iostream>
#include <string>

namespace carconfig {  

Car::Car() : name("default"), model()
{ 
    for (int i = 0; i < 5; ++i) {
        options[i] = nullptr;
    }
}

Car::Car(const std::string& n, const Model& m, Option* inOptions[5]) : name(n), model(m)
{ 
    for (int i = 0; i < 5; ++i) {
        if (inOptions != nullptr && inOptions[i] != nullptr) {
            options[i] = new Option(*inOptions[i]);
        } else {
            options[i] = nullptr;
        }
    }
}

Car::Car(const Car& car) : name(car.getName()), model(car.getModel())
{ 
    for (int i = 0; i < 5; ++i) {
        if (car.options[i] != nullptr) {
            options[i] = new Option(*car.options[i]);
        } else {
            options[i] = nullptr;
        }
    }
}

Car::~Car()
{ 
    for (int i = 0; i < 5; ++i) {
        delete options[i];
    }
}

Car& Car::operator=(const Car& car)
{
    if (this != &car) {
        name = car.getName();
        model = car.getModel();
        for (int i = 0; i < 5; ++i) {
            delete options[i];
            if (car.options[i] != nullptr) {
                options[i] = new Option(*car.options[i]);
            } else {
                options[i] = nullptr;
            }
        }
    }
    return *this;
}

Car Car::operator+(const Option& op) const
{
    Car newCar(*this);
    newCar.addOption(op);
    return newCar;
}

Car operator+(const Option& op, const Car& car)
{
    Car newCar(car);
    newCar.addOption(op);
    return newCar;
}

Car Car::operator-(const std::string code) const
{
    Car newCar(*this);
    newCar.removeOption(code);
    return newCar;
}

Car Car::operator-(const Option& op) const
{
    return *this - op.getCode();
}

bool Car::operator>(const Car& car) const
{
    return this->getPrice() > car.getPrice();
}

bool Car::operator<(const Car& car) const
{
    return this->getPrice() < car.getPrice();
}

bool Car::operator==(const Car& car) const
{
    return this->getPrice() == car.getPrice();
}

// Serialisation XML
std::ostream& operator<<(std::ostream& s, const Car& car)
{
    s << "<Car>\n";

    s << "<name>\n"
      << car.name << "\n"
      << "</name>\n";

    s << "<model>\n";
    s << car.model;   // Appel Model::operator<<
    s << "</model>\n";

    s << "<options>\n";
    for (int i = 0; i < 5; ++i) {
        if (car.options[i] != nullptr) {
            s << *(car.options[i]);   // Appel Option::operator<<
        }
    }
    s << "</options>\n";

    s << "</Car>\n";

    return s;
}

// Désérialisation XML
std::istream& operator>>(std::istream& s, Car& car)
{
    std::string ligne;

    // <Car>
    std::getline(s, ligne);

    // <name>
    std::getline(s, ligne);        // <name>
    std::getline(s, car.name);     // lire le nom complet 
    std::getline(s, ligne);        // </name>

    // <model>
    std::getline(s, ligne);        // <model>
    s >> car.model;                // Appel Model::operator>> 
    std::getline(s, ligne);        // </model>

    // <options>
    std::getline(s, ligne);        // <options>

    // nettoyer avant lecture
    for (int i = 0; i < 5; ++i) {
        delete car.options[i];
        car.options[i] = nullptr;
    }

    int index = 0;
    while (true) {
        std::streampos pos = s.tellg();
        std::getline(s, ligne);    // lire la première ligne de l'option ou </options>

        if (ligne == "</options>") {
            break;
        }

        // revenir en arrière pour que Option::operator>> lise <Option>
        s.seekg(pos);

        if (index < 5) {
            car.options[index] = new Option();
            s >> *car.options[index];   // Option::operator>>
            index++;
        } else {
            Option tmp;
            s >> tmp;                   // ignorer les options supplémentaires
        }
    }

    // </Car>
    std::getline(s, ligne);

    return s;
}


Option* Car::operator[](int index)
{
    if (index < 0 || index >= 5)
        throw std::out_of_range("Index hors limites");
    return options[index];
}

Option* Car::operator[](int index) const
{
    if (index < 0 || index >= 5)
        throw std::out_of_range("Index hors limites");
    return options[index];
}

void Car::setName(const std::string& n)
{
    name = n;
}

const std::string& Car::getName() const
{
    return name;
}

void Car::setModel(const Model& m)
{
    model = m;
}

const Model& Car::getModel() const
{
    return model;
}

void Car::addOption(const Option &option)
{
    bool hasEmptySlot = false;
    for (int i = 0; i < 5; ++i) {
        if (options[i] == nullptr) {
            hasEmptySlot = true;
            break;
        }
    }
    if (!hasEmptySlot)
        throw OptionException("La voiture contient deja 5 options");

    for (int i = 0; i < 5; ++i) {
        if (options[i] != nullptr && options[i]->getCode() == option.getCode()) {
            throw OptionException("L'option est deja presente dans la voiture");
        }
    }

    for (int i = 0; i < 5; ++i) {
        if (options[i] == nullptr) {
            options[i] = new Option(option);
            return;
        }
    }
}

void Car::removeOption(const std::string code)
{
    for (int i = 0; i < 5; ++i) {
        if (options[i] != nullptr && options[i]->getCode() == code) {
            delete options[i];
            options[i] = nullptr;
            return;
        }
    }
    throw OptionException("L'option a supprimer n'est pas presente dans la voiture");
}

float Car::getPrice() const
{
    float totalPrice = model.getBasePrice();
    for (int i = 0; i < 5; ++i) {
        if (options[i] != nullptr) {
            totalPrice += options[i]->getPrice();
        }
    }
    return totalPrice;
}

void Car::display() const
{
    std::cout << "Nom : " << name << std::endl;
    std::cout << "Modèle : " << std::endl;
    model.display();
    std::cout << "Prix total : " << getPrice() << " EUR" << std::endl;
    std::cout << "Options :" << std::endl;
    for (int i = 0; i < 5; ++i) {
        if (options[i] != nullptr) {
            options[i]->display();
        }
    }
}

} // namespace carconfig  
