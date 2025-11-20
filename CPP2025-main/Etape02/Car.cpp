#include "Car.h"

#include <iostream>
#include <string>

carconfig::Car::Car() : name("default"), model()
{ 
    for (int i = 0; i < 5; ++i) {
        options[i] = nullptr;
    }
}

carconfig::Car::Car(const std::string& n, const carconfig::Model& m, carconfig::Option* inOptions[5]) : name(n), model(m)
{ 
    for (int i = 0; i < 5; ++i) {
        if (inOptions != nullptr && inOptions[i] != nullptr) {
            options[i] = new carconfig::Option(*inOptions[i]);
        } else {
            options[i] = nullptr;
        }
    }
}

carconfig::Car::Car(const carconfig::Car& car) : name(car.getName()), model(car.getModel())
{ 
    for (int i = 0; i < 5; ++i) {
        if (car.options[i] != nullptr) {
            options[i] = new carconfig::Option(*car.options[i]);
        } else {
            options[i] = nullptr;
        }
    }
}

carconfig::Car::~Car()
{ 
    for (int i = 0; i < 5; ++i) {
        delete options[i];
    }
}

void carconfig::Car::setName(const std::string& n)
{
    name = n;
}

const std::string& carconfig::Car::getName() const
{
    return name;
}

void carconfig::Car::setModel(const carconfig::Model& m)
{
    model = m;
}

const carconfig::Model& carconfig::Car::getModel() const
{
    return model;
}

void carconfig::Car::addOption(const carconfig::Option &option)
{
    for (int i = 0; i < 5; ++i) {
        if (options[i] == nullptr) {
            options[i] = new carconfig::Option(option);
            return;
        }
    }
}

void carconfig::Car::removeOption(const std::string code)
{
    for (int i = 0; i < 5; ++i) {
        if (options[i] != nullptr && options[i]->getCode() == code) {
            delete options[i];
            options[i] = nullptr;
            return;
        }
    }
}

float carconfig::Car::getPrice() const
{
    float totalPrice = model.getBasePrice();
    for (int i = 0; i < 5; ++i) {
        if (options[i] != nullptr) {
            totalPrice += options[i]->getPrice();
        }
    }
    return totalPrice;
}

void carconfig::Car::display() const
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