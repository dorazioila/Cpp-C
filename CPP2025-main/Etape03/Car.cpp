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

carconfig::Car& carconfig::Car::operator=(const carconfig::Car& car)
{
    if (this != &car) {
        name = car.getName();
        model = car.getModel();
        for (int i = 0; i < 5; ++i) {
            delete options[i];
            if (car.options[i] != nullptr) {
                options[i] = new carconfig::Option(*car.options[i]);
            } else {
                options[i] = nullptr;
            }
        }
    }
    return *this;
}

carconfig::Car carconfig::Car::operator+(const carconfig::Option& op) const
{
    carconfig::Car newCar(*this);
    newCar.addOption(op);
    return newCar;
}

namespace carconfig {

Car operator+(const Option& op, const Car& car)
{
    Car newCar(car);
    newCar.addOption(op);
    return newCar;
}

}

carconfig::Car carconfig::Car::operator-(const std::string code) const
{
    carconfig::Car newCar(*this);
    newCar.removeOption(code);
    return newCar;
}

carconfig::Car carconfig::Car::operator-(const carconfig::Option& op) const
{
    return *this - op.getCode();
}

bool carconfig::Car::operator>(const carconfig::Car& car) const
{
    return this->getPrice() > car.getPrice();
}

bool carconfig::Car::operator<(const carconfig::Car& car) const
{
    return this->getPrice() < car.getPrice();
}

bool carconfig::Car::operator==(const carconfig::Car& car) const
{
    return this->getPrice() == car.getPrice();
}

namespace carconfig {

std::ostream& operator<<(std::ostream& os, const Car& car)
{
    os << "Nom : " << car.name << std::endl;
    os << "Modèle : " << std::endl;
    os << car.model;
    os << "Prix total : " << car.getPrice() << " EUR" << std::endl;
    os << "Options :" << std::endl;
    for (int i = 0; i < 5; ++i) {
        if (car.options[i] != nullptr) {
            os << *(car.options[i]) << std::endl;
        }
    }
    return os;
}

}

carconfig::Option* carconfig::Car::operator[](int index)
{
    if (index < 0 || index >= 5)
        throw std::out_of_range("Index hors limites");
    return options[index];
}

carconfig::Option* carconfig::Car::operator[](int index) const
{
    if (index < 0 || index >= 5)
        throw std::out_of_range("Index hors limites");
    return options[index];
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