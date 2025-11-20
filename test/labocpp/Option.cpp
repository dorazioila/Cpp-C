#include "Option.h"
#include <iostream>
#include <string>
using namespace std;

namespace carconfig {

// Constructeur par defaut
Option::Option() : code(""), label(""), price(0.0f) {}

// Constructeur initialisation 
Option::Option(const std::string& c, const std::string& l, float p)
    : code(c), label(l), price(p) {}

// Constructeur de copie
Option::Option(const Option& other)
    : code(other.code), label(other.label), price(other.price) {}

// Destructeur 
Option::~Option() {
}

// Setters / Getters 
void Option::setCode(const std::string& c) { code = c; }
std::string Option::getCode() const { return code; }

void Option::setLabel(const std::string& l) { label = l; }
std::string Option::getLabel() const { return label; }

void Option::setPrice(float p) { price = p; }
float Option::getPrice() const { return price; }

// Affichage 
void Option::display() const {
    cout << "Code : " << code << ", Label : " << label << ", Prix : " << price << " EUR"<< endl;
}

// Surcharge operateur <<
ostream& operator<<(ostream& os, const Option& o) {
    os << "[" << o.getCode() << "] " << o.getLabel() << " : " << o.getPrice() << " EUR";
    return os;
}

// Surcharge operateur >>
istream& operator>>(istream& is, Option& o) {
    string code, label;
    float price;

    cout << "Code de l'option: ";
    getline(is >> ws, code);
    cout << "Label de l'option: ";
    getline(is, label);
    cout << "Prix de l'option: ";
    is >> price;

    o.setCode(code);
    o.setLabel(label);
    o.setPrice(price);

    return is;
}
//  Pre decrementation : --op 
Option& Option::operator--() {
    // Si le prix est au-dessus de 50 on le diminue
    if (price >= 50.0f)
        price -= 50.0f;
    else
        price = 0.0f;  // pour pas avoir d eprix en negatif 

    return *this; // retourne lobjet modifie
}

// Post-decrementation : op-- 
Option Option::operator--(int) {
    Option temp(*this); // sauvegarde etat actuel
    --(*this);          // utilise le pre-decrement pour eviter de dupliquer le code
    return temp;        // renvoie etat AVANT decrementation
}

} // namespace carconfig
