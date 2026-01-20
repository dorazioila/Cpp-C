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
		Model(); 
		Model(const char* n, int p, Engine e, float bp); 
		Model(const Model& mod); 

		~Model();

		Model& operator=(const Model& mod); 
		
		friend std::ostream& operator<<(std::ostream& os, const Model& mod); 
		friend std::istream& operator>>(std::istream& is, Model& mod); 

		void setPower(int p);
		int getPower() const;

		void setName(const char* n);
		const char* getName() const;

		void setEngine(Engine e);
		Engine getEngine() const;

		void setBasePrice(float bp);
		float getBasePrice() const;

		void display() const;

        
        std::string toString() const;
	};
}

#endif 
