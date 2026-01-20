#include "Option.h"
#include <iostream>
#include <cstring>
#include <limits>

using namespace carconfig;

Option::Option() 
{
    setCode("AAAA");
    setLabel("default");
    setPrice(0.0f);
}

Option::Option(const std::string code, const std::string label, float price) 
{
    setCode(code);
    setLabel(label);
    setPrice(price);
}

Option::Option(const Option& op) 
{
    setCode(op.getCode());
    setLabel(op.getLabel());
    setPrice(op.getPrice());
}

Option& Option::operator=(const Option& op) 
{
    if (this != &op) {
        setCode(op.getCode());
        setLabel(op.getLabel());
        setPrice(op.getPrice());
    }
    return *this;
}

namespace carconfig {

std::ostream& operator<<(std::ostream& os, const Option& op) 
{
    os << "Code : " << op.getCode() << std::endl;
    os << "Label : " << op.getLabel() << std::endl;
    os << "Prix : " << op.getPrice() << " EUR" << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Option& op) 
{
    std::string code;
    std::string label;
    float price;

    std::cout << "Entrez le code (4 caracteres) : ";
    is >> code;
    op.setCode(code);

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    std::cout << "Entrez le label : ";
    std::getline(is, label);
    op.setLabel(label);

    std::cout << "Entrez le prix : ";
    is >> price;
    op.setPrice(price);

    return is;
}

}

Option& Option::operator--() 
{
    price -= 50.0f; 
    if (price < 0.0f) price = 0.0f; 
    return *this;
}

Option Option::operator--(int) 
{
    Option temp = *this; 
    price -= 50.0f; 
    if (price < 0.0f) price = 0.0f; 
    return temp; 
}

Option::~Option()
{
}

void Option::setCode(const std::string c)
{
    if (c.empty() || c.length() != 4) {
        return;
    }
    code = c;
}

const std::string Option::getCode() const
{
    if (code.empty()) {
        return "";
    }
    return code;
}

void Option::setLabel(const std::string l)
{
    if (l.empty()) {
        return;
    }
    label = l;
}

const std::string Option::getLabel() const
{
    if (label.empty()) {
        return "";
    }
    return label;
}

void Option::setPrice(float p)
{
    price = p;
}

float Option::getPrice() const
{
    return price;
}

void Option::display() const
{
    std::cout << "Code : " << getCode() << std::endl;
    std::cout << "Label : " << getLabel() << std::endl;
    std::cout << "Prix de base : " << getPrice() << std::endl;
}
