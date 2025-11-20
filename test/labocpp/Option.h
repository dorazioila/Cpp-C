#ifndef OPTION_H
#define OPTION_H
#include <iostream>
#include <string>

namespace carconfig {

class Option {
private:
    std::string code;
    std::string label;
    float price;

public:
    Option();
    Option(const std::string& c, const std::string& l, float p);
    Option(const Option& other);
    ~Option();
    // Surcharge des operateurs de dcrementation 
    Option& operator--();     // pre-decrementation (--op)
    Option operator--(int);   // post-decrementation (op--)

    void setCode(const std::string& c);
    std::string getCode() const;

    void setLabel(const std::string& l);
    std::string getLabel() const;

    void setPrice(float p);
    float getPrice() const;

    void display() const;

    //  Surcharge operateurs flux
    friend std::ostream& operator<<(std::ostream& os, const Option& o);
    friend std::istream& operator>>(std::istream& is, Option& o);
};

} // namespace carconfig

#endif
