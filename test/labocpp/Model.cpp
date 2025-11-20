	#include "Model.h"
	#include <iostream>

	namespace carconfig{

	Model::Model() // constructeur par défaut
	{
		name = nullptr;
		setName("default");
		setPower(80);
		setEngine(Engine::Petrol);
		setBasePrice(15000);
	}

	Model::Model(const char* n, int p, Engine e, float bp) // constructeur d'initialisation
	{
		name = nullptr;
		setName(n);
		setPower(p);
		setEngine(e);
		setBasePrice(bp);
	}

	Model::Model(const Model& mod) // constructeur de copie
	{
		name = nullptr;
		setName(mod.getName());
		setPower(mod.getPower());
		setEngine(mod.getEngine());
		setBasePrice(mod.getBasePrice());
	}

	Model::~Model()//destructeur
	{
		if (name != nullptr) delete name;
	}

	void Model::setPower(int p)
	{
		if(p >= 0) power = p;
	}

	int Model::getPower() const
	{
		return power;
	}

	void Model::setName(const char* n)
	{
		if (name != nullptr) delete name;
		name = new char[strlen(n)+1];
		strcpy(name,n);
	}

	const char* Model::getName() const
	{
		return name;
	}

	void Model::setEngine(Engine e)
	{
		engine = e;
	}

	Engine Model::getEngine() const
	{
		return engine;
	}

	void Model::setBasePrice(float bp)
	{
		basePrice = bp;
	}

	float Model::getBasePrice() const
	{
		return basePrice;
	}

	void Model::display() const
	{
		cout << "Nom : " << name << endl;
		cout << "Puissace : " << power << endl;
		cout << "Moteur : " << engine << endl; // !!!
		cout << "Prix de base : " << basePrice << endl;
	}
	ostream& operator<<(ostream& os, const Model& m) {
    os << "Modele: " << m.getName()
       << " (" << m.getPower() << " ch, ";

    // Affichage du type de moteur
    switch (m.getEngine()) {
        case Engine::Petrol:
            os << "Essence";
            break;
        case Engine::Diesel:
            os << "Diesel";
            break;
        default:
            os << "Type inconnu";
            break;
    }

    os << "), prix de base: " << m.getBasePrice() << " EUR";
    return os;
	}

	istream& operator>>(istream& is, Model& m) {
	    string name;
	    int power;
	    int engineChoice;
	    float price;

	    cout << "Nom du modele: ";
	    getline(is >> ws, name);
	    cout << "Puissance (en ch): ";
	    is >> power;
	    cout << "Type de moteur (0 = Essence, 1 = Diesel): ";
	    is >> engineChoice;
	    cout << "Prix de base: ";
	    is >> price;

	    // Conversion et affectation
	    m.setName(name.c_str());
	    m.setPower(power);
	    m.setEngine(static_cast<Engine>(engineChoice));
	    m.setBasePrice(price);

	    return is;
	}
	}
