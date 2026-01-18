#include "Option.h"
#include <iostream>
#include <sstream>
#include "OptionException.h"
using namespace carconfig;
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
    if (price - 50 < 0){
        throw OptionException("Prix négatif interdit");
    }
    price -= 50;
    return *this;
}

Option Option::operator--(int) {
    Option tmp(*this);
    --(*this);
    return tmp;
}

void Option::setCode(const std::string code) { this->code = code; }
const std::string Option::getCode() const { return code; }

void Option::setLabel(const std::string label) { this->label = label; }
const std::string Option::getLabel() const { return label; }

void Option::setPrice(float price) { this->price = price; }
float Option::getPrice() const { return price; }
std::string Option::toString() const {
    return code + " - " + label + " (" + std::to_string(price) + ")";
}
void Option::display() const {
    std::cout << "Option: " << code << " - " << label << " (" << price << ")\n";
}

// Serialisation XML pour Option
std::ostream& operator<<(std::ostream& os, const Option& op) {
    os << "<Option>\n";
    os << "<code>\n" << op.code << "\n</code>\n";
    os << "<label>\n" << op.label << "\n</label>\n";
    os << "<price>\n" << op.price << "\n</price>\n";
    os << "</Option>\n";
    return os;
}

// Désérialisation XML pour Option
std::istream& operator>>(std::istream& is, Option& op) {
    std::string line;
    std::string temp;  // variable temporaire

    // <Option>
    std::getline(is, line);

    // <code>
    std::getline(is, line);    // <code>
    std::getline(is, op.code);
    std::getline(is, line);    // </code>

    // <label>
    std::getline(is, line);    // <label>
    std::getline(is, temp);    // on lit dans temp
    op.label = temp;           // on assigne après
    std::getline(is, line);    // </label>

    // <price>
    std::getline(is, line);    // <price>
    std::getline(is, temp);    // lit le prix dans temp
    op.price = std::stof(temp);
    std::getline(is, line);    // </price>

    // </Option>
    std::getline(is, line);

    return is;
}


} // namespace carconfig  
