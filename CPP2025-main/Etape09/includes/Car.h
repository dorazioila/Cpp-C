#ifndef CAR_H
#define CAR_H

#include "Model.h"
#include "Option.h"
#include <string>
#include <istream>

namespace carconfig {

class Car
{
private:
    std::string name;
    Model model;
	Option* options[5];
public:
	Car(); // constructeur par défaut
	Car(const std::string& n, const Model& m, Option* options[5] = nullptr); // constructeur d'initialisation
	Car(const Car& car); // constructeur de copie

	~Car();

	Car& operator=(const Car& mod); // opérateur d'affectation
	Car operator+(const Option& op) const; // opérateur d'ajout d'option
	friend Car operator+(const Option& op, const Car& car); // opérateur d'ajout d'option (option + car)
	Car operator-(const std::string code) const; // opérateur de retrait d'option par code
	Car operator-(const Option& op) const; // opérateur de retrait d'option par option
	bool operator>(const Car& car) const; // opérateur de comparaison >
	bool operator<(const Car& car) const; // opérateur de comparaison <
	bool operator==(const Car& car) const; // opérateur de comparaison d'égalité
	Option* operator[](int index); // opérateur d'accès aux options
	Option* operator[](int index) const; // opérateur d'accès aux options (const)

	friend std::ostream& operator<<(std::ostream& os, const Car& car); // opérateur d'insertion (XML)
    friend std::istream& operator>>(std::istream& is, Car& car); // opérateur d'extraction (XML)

	void setName(const std::string& n);
	const std::string& getName() const;

	void addOption(const Option &option);
	void removeOption(const std::string code);

	float getPrice() const;

	void setModel(const Model& m);
	const Model& getModel() const;

	void display() const;
};

}

#endif // CAR_H
