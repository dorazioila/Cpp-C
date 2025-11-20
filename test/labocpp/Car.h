#ifndef CAR_H
#define CAR_H
#include <iostream>
#include <string>
#include "Model.h"   // pour utiliser la classe Model
#include "Option.h"
namespace carconfig {

class Car {
private:
    std::string name;  
    Model model;       // Modele de base
    Option* options[5]; // tableau de pointeurs vers Option

public:
    //operateur = + -
    //  Surcharge des operateurs d’affectation
    Car& operator=(const Car& other);             // Affectation profonde
    Car operator+(const Option& option) const;    // Ajout d'une option
    friend Car operator+(const Option& option, const Car& car); // Ordre inverse
    Car operator-(const Option& option) const;    // Retrait d'une option
    Car operator-(const std::string& code) const; // Retrait par code

    //  Surcharge des operateurs de comparaison 
    bool operator<(const Car& other) const;
    bool operator>(const Car& other) const;
    bool operator==(const Car& other) const;

    //  Surcharge operateur d’insertion 
    friend std::ostream& operator<<(std::ostream& os, const Car& c);

    //  Surcharge de l’opérateur [] 
    Option* operator[](int index);
    const Option* operator[](int index) const;

    // Constructeurs 
    Car();                                     // Constructeur par défaut
    Car(const std::string& name, const Model& model); // Constructeur d'initialisation
    Car(const Car& other);                     // Constructeur de copie

    //  Destructeur 
    ~Car();

    //  Setters / Getters 
    void setName(const std::string& name);
    std::string getName() const;

    void setModel(const Model& model);
    Model getModel() const;

    // Gestion des options 
    void addOption(const Option& options);
    void removeOption(const std::string& code);
    float getPrice() const;


    // Méthode d’affichage 
    void display() const;
};

} // namespace carconfig

#endif
