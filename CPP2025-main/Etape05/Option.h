#ifndef OPTION_H
#define OPTION_H

#include <string>

namespace carconfig {
    class Option
    {
    private:
        std::string code;
        std::string label;
        float price;

    public:
        Option(); // constructeur par défaut
        Option(const std::string code, const std::string label, float price); // constructeur d'initialisation
        Option(const Option& op); // constructeur de copie

        ~Option();

        Option& operator=(const Option& op); // opérateur d'affectation
        Option& operator--(); // opérateur de pré-décrémentation
        Option operator--(int); // opérateur de post-décrémentation

        friend std::ostream& operator<<(std::ostream& os, const Option& op); // opérateur d'insertion
		friend std::istream& operator>>(std::istream& is, Option& op); // opérateur d'extraction

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