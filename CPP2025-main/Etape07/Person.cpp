#include "Person.h"
#include <iostream>


Person::Person() {
    lastName = "";
    firstName = "";
}

Person::Person(const std::string& ln, const std::string& fn) {
    lastName = ln;
    firstName = fn;
}

Person::Person(const Person& p)
{
    lastName = p.lastName;
    firstName = p.firstName;
}


std::string Person::getLastName() const {
    return lastName;
}

std::string Person::getFirstName() const {
    return firstName;
}


void Person::setLastName(const std::string& ln) {
    lastName = ln;
}

void Person::setFirstName(const std::string& fn) {
    firstName = fn;
}


std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << p.lastName << " " << p.firstName;
    return os;
}

std::istream& operator>>(std::istream& is, Person& p) {
    std::cout << "Entrez le nom de famille : ";
    is >> p.lastName;
    std::cout << "Entrez le prénom: ";
    is >> p.firstName;
    return is;
}

Person& Person::operator=(const Person& p) {
    if (this != &p) {
        lastName = p.lastName;
        firstName = p.firstName;
    }
    return *this;
}

Person::~Person() {
    
}
