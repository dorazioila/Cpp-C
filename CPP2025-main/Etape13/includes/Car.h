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
	void save();
    void load(string projectName);
	Car(); 
	Car(const std::string& n, const Model& m, Option* options[5] = nullptr); 
	Car(const Car& car); 

	~Car();

	Car& operator=(const Car& mod); 
	Car operator+(const Option& op) const; 
	friend Car operator+(const Option& op, const Car& car); 
	Car operator-(const std::string code) const; 
	Car operator-(const Option& op) const; 
	bool operator>(const Car& car) const; 
	bool operator<(const Car& car) const; 
	bool operator==(const Car& car) const; 
	Option* operator[](int index); 
	Option* operator[](int index) const; 

	friend std::ostream& operator<<(std::ostream& os, const Car& car); 
    friend std::istream& operator>>(std::istream& is, Car& car); 

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
