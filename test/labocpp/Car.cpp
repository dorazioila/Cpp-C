#include "Car.h"
#include <iostream>

using namespace std;

namespace carconfig {

//  Constructeur par défaut-
Car::Car() : name("") {
    for (int i = 0; i < 5; ++i) options[i] = nullptr;
}

//  Constructeur d'initialisation
Car::Car(const string& name, const Model& model) 
    : name(name), model(model) {
    for (int i = 0; i < 5; ++i) options[i] = nullptr;
}

//  Constructeur de copie 
Car::Car(const Car& other) : name(other.name), model(other.model) {
    for (int i = 0; i < 5; ++i) {
        if (other.options[i] != nullptr)
            options[i] = new Option(*other.options[i]);
        else
            options[i] = nullptr;
    }
}

//  Destructeur 
Car::~Car() {
    cout << "Destruction de " << name << endl;
    for (int i = 0; i < 5; ++i) {
        delete options[i];
        options[i] = nullptr;
    }
}

// Setters / Getters 
void Car::setName(const string& n) { name = n; }
string Car::getName() const { return name; }

void Car::setModel(const Model& m) { model = m; }
Model Car::getModel() const { return model; }

//  Gestion des options 
void Car::addOption(const Option& option) {
    for (int i = 0; i < 5; ++i) {
        if (options[i] == nullptr) {
            options[i] = new Option(option);
            return;
        }
    }
    cout << "Impossible d'ajouter l'option " << option.getCode() << " : tableau plein !" << endl;
}

void Car::removeOption(const string& code) {
    for (int i = 0; i < 5; ++i) {
        if (options[i] != nullptr && options[i]->getCode() == code) {
            delete options[i];
            options[i] = nullptr;
            return;
        }
    }
    cout << "Option " << code << " non trouvee." << endl;
}

float Car::getPrice() const {
    float total = model.getBasePrice(); 
    for (int i = 0; i < 5; ++i) {
        if (options[i] != nullptr) total += options[i]->getPrice();
    }
    return total;
}

// Affichage 
void Car::display() const {
    cout << "Projet : " << name << endl;
    cout << "Modele de base : ";
    model.display();
    cout << "Options :" << endl;
    bool hasOptions = false;
    for (int i = 0; i < 5; ++i) {
        if (options[i] != nullptr) {
            cout << " - ";
            options[i]->display();
            hasOptions = true;
        }
    }
    if (!hasOptions) cout << " Aucune option." << endl;
    cout << "Prix total : " << getPrice() << " EUR" << endl << endl;
}

//surcharge operateurs
Car& Car::operator=(const Car& other) {
    if (this != &other) {
        name = other.name;
        model = other.model;

        // Liberer les anciennes options
        for (int i = 0; i < 5; ++i) {
            delete options[i];
            options[i] = nullptr;
        }

        // Copie profonde des options
        for (int i = 0; i < 5; ++i) {
            if (other.options[i] != nullptr)
                options[i] = new Option(*other.options[i]);
        }
    }
    return *this;
}

// Surcharge operateur + (Car + Option)
Car Car::operator+(const Option& option) const {
    Car newCar(*this);  // copie de l’objet courant
    newCar.addOption(option);
    return newCar;
}

// Surcharge operateur + (Option + Car)
Car operator+(const Option& option, const Car& car) {
    return car + option; // reutilisation de la version precendente
}

// Surcharge operateur - (Car - Option)
Car Car::operator-(const Option& option) const {
    Car newCar(*this);
    newCar.removeOption(option.getCode());
    return newCar;
}

// Surcharge operateur - (Car - "code") 
Car Car::operator-(const std::string& code) const {
    Car newCar(*this);
    newCar.removeOption(code);
    return newCar;
}
//  Surcharge operateur < 
bool Car::operator<(const Car& other) const {
    return this->getPrice() < other.getPrice();
}

//  Surcharge oprateur > 
bool Car::operator>(const Car& other) const {
    return this->getPrice() > other.getPrice();
}

//  Surcharge operateur == 
bool Car::operator==(const Car& other) const {
    return this->getPrice() == other.getPrice();
}
ostream& operator<<(ostream& os, const Car& c) {
    os << "Projet : " << c.name << endl;
    os << "Modele : " << c.model << endl; // utilise operator<< de Model

    os << "Options :" << endl;
    bool hasOption = false;
    for (int i = 0; i < 5; ++i) {
        if (c.options[i] != nullptr) {
            os << " - " << *c.options[i] << endl; // utilise operator<< de Option
            hasOption = true;
        }
    }
    if (!hasOption)
        os << " Aucune option." << endl;

    os << "Prix total : " << c.getPrice() << " EUR";
    return os;
}

//  Surcharge operateur [] 
Option* Car::operator[](int index) {
    if (index >= 0 && index < 5)
        return options[index];
    else
        return nullptr; //si jamais l'index est hors limite
}

//  Version const 
const Option* Car::operator[](int index) const {
    if (index >= 0 && index < 5)
        return options[index];
    else
        return nullptr;
}


} // namespace carconfig
