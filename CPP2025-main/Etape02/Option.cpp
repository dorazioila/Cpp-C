#include "Option.h"
#include <iostream>
#include <cstring>

using namespace carconfig;

Option::Option() // constructeur par défaut
{
    setCode("AAAA");
    setLabel("default");
    setPrice(0.0f);
}

Option::Option(const std::string code, const std::string label, float price) // constructeur d'initialisation
{
    setCode(code);
    setLabel(label);
    setPrice(price);
}

Option::Option(const Option& op) // constructeur de copie
{
    setCode(op.getCode());
    setLabel(op.getLabel());
    setPrice(op.getPrice());
}

Option& Option::operator=(const Option& op) // opérateur d'affectation
{
    if (this != &op) {
        setCode(op.getCode());
        setLabel(op.getLabel());
        setPrice(op.getPrice());
    }
    return *this;
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
