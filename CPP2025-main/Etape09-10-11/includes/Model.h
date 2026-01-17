#ifndef MODEL_H
#define MODEL_H

#include <ostream>
#include <istream>
#include <string>
using namespace std;
namespace carconfig {
	enum Engine { Petrol, Diesel, Electric, Hybrid };

	class Model
	{
	private:
		char* name;
		int power;
		Engine engine;
		float basePrice;
		string image;

	public:
		string getImage() const { return image; }
    	void setImage(const string& img) { image = img; }
		Model(); // constructeur par défaut
		Model(const char* n, int p, Engine e, float bp); // constructeur d'initialisation
		Model(const Model& mod); // constructeur de copie

		~Model();

		Model& operator=(const Model& mod); // opérateur d'affectation
		
		friend std::ostream& operator<<(std::ostream& os, const Model& mod); // opérateur d'insertion (XML)
		friend std::istream& operator>>(std::istream& is, Model& mod); // opérateur d'extraction (XML)

		void setPower(int p);
		int getPower() const;

		void setName(const char* n);
		const char* getName() const;

		void setEngine(Engine e);
		Engine getEngine() const;

		void setBasePrice(float bp);
		float getBasePrice() const;

		void display() const;

        // méthode utilitaire utilisée par les tests
        std::string toString() const;
	};
}

#endif // MODEL_H
