#include "Option.h"
#include <iostream>
#include <sstream>

namespace carconfig {  

Option::Option() : code(""), label(""), price(0.0f) {}

Option::Option(const std::string code, const std::string label, float price)
    : code(code), label(label), price(price) {}

Option::Option(const Option& op) : code(op.code), label(op.label), price(op.price) {}

Option::~Option() {}

Option& Option::operator=(const Option& op) {
    if (this != &op) {
        code = op.code;
        label = op.label;
        price = op.price;
    }
    return *this;
}


Option& Option::operator--() {
    price -= 1.0f;
    return *this;
}

Option Option::operator--(int) {
    Option tmp(*this);
    price -= 1.0f;
    return tmp;
}

void Option::setCode(const std::string code) { this->code = code; }
const std::string Option::getCode() const { return code; }

void Option::setLabel(const std::string label) { this->label = label; }
const std::string Option::getLabel() const { return label; }

void Option::setPrice(float price) { this->price = price; }
float Option::getPrice() const { return price; }

void Option::display() const {
    std::cout << "Option: " << code << " - " << label << " (" << price << ")\n";
}


std::ostream& operator<<(std::ostream& os, const Option& op) {
    os << "<Option>\n";
    os << "<code>\n" << op.code << "\n</code>\n";
    os << "<label>\n" << op.label << "\n</label>\n";
    os << "<price>\n" << op.price << "\n</price>\n";
    os << "</Option>\n";
    return os;
}


std::istream& operator>>(std::istream& is, Option& op) {
    std::string line;
    std::string temp;  

    
    std::getline(is, line);

    
    std::getline(is, line);    
    std::getline(is, op.code);
    std::getline(is, line);    

    
    std::getline(is, line);    
    std::getline(is, temp);    
    op.label = temp;           
    std::getline(is, line);    

    
    std::getline(is, line);    
    std::getline(is, temp);    
    op.price = std::stof(temp);
    std::getline(is, line);    

    
    std::getline(is, line);

    return is;
}


} 
