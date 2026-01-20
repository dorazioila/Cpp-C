#ifndef CAR_H
#define CAR_H

#include "Model.h"
#include "Option.h"
#include <string>

namespace carconfig {

class Car
{
private:
    std::string name;
    Model model;
	Option* options[5];
public:
	Car(); 
	Car(const std::string& n, const Model& m, Option* options[5] = nullptr); 
	Car(const Car& car); // constructeur de copie

	~Car();

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

#endif