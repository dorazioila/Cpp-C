#ifndef MODEL_H
#define MODEL_H

namespace carconfig {
	enum Engine { Petrol, Diesel, Electric, Hybrid };

	class Model
	{
	private:
		char* name;
		int power;
		Engine engine;
		float basePrice;

	public:
		Model(); 
		Model(const char* n, int p, Engine e, float bp); 
		Model(const Model& mod); 

		~Model();

		Model& operator=(const Model& mod); 

		void setPower(int p);
		int getPower() const;

		void setName(const char* n);
		const char* getName() const;

		void setEngine(Engine e);
		Engine getEngine() const;

		void setBasePrice(float bp);
		float getBasePrice() const;

		void display() const;
	};
}

#endif