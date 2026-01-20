#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <iostream>

namespace carconfig {
    class Option{
    private:
        std::string code;
        std::string label;
        float price;

    public:
        Option(); 
        Option(const std::string code, const std::string label, float price); 
        Option(const Option& op); 

        ~Option();

        Option& operator=(const Option& op); 
        Option& operator--(); 
        Option operator--(int); 

        friend std::ostream& operator<<(std::ostream& os, const Option& op); 
        friend std::istream& operator>>(std::istream& is, Option& op); 

        void setCode(const std::string code);
        const std::string getCode() const;

        void setLabel(const std::string label);
        const std::string getLabel() const;

        void setPrice(float price);
        float getPrice() const;

        void display() const;
    };
}

#endif 
