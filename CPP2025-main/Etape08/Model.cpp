#include "Model.h"
#include <cstring>
#include <sstream>
#include <iostream>
using namespace carconfig;
namespace carconfig {  

Model::Model() : name(nullptr), power(0), engine(Petrol), basePrice(0.0f) {
    name = new char[1];
    name[0] = '\0';
}

Model::Model(const char* n, int p, Engine e, float bp) : power(p), engine(e), basePrice(bp) {
    if (n) {
        size_t len = std::strlen(n) + 1;
        name = new char[len];
        std::strcpy(name, n);
    } else {
        name = new char[1];
        name[0] = '\0';
    }
}

Model::Model(const Model& mod) : power(mod.power), engine(mod.engine), basePrice(mod.basePrice) {
    if (mod.name) {
        size_t len = std::strlen(mod.name) + 1;
        name = new char[len];
        std::strcpy(name, mod.name);
    } else {
        name = new char[1];
        name[0] = '\0';
    }
}

Model::~Model() {
    delete[] name;
}

Model& Model::operator=(const Model& mod) {
    if (this != &mod) {
        delete[] name;
        if (mod.name) {
            size_t len = std::strlen(mod.name) + 1;
            name = new char[len];
            std::strcpy(name, mod.name);
        } else {
            name = new char[1];
            name[0] = '\0';
        }
        power = mod.power;
        engine = mod.engine;
        basePrice = mod.basePrice;
    }
    return *this;
}

void Model::setPower(int p) { power = p; }
int Model::getPower() const { return power; }

void Model::setName(const char* n) {
    delete[] name;
    if (n) {
        size_t len = std::strlen(n) + 1;
        name = new char[len];
        std::strcpy(name, n);
    } else {
        name = new char[1];
        name[0] = '\0';
    }
}
const char* Model::getName() const { return name; }

void Model::setEngine(Engine e) { engine = e; }
Engine Model::getEngine() const { return engine; }  

void Model::setBasePrice(float bp) { basePrice = bp; }
float Model::getBasePrice() const { return basePrice; }

void Model::display() const {
    std::cout << "Model: " << (name ? name : "") << " power=" << power
              << " engine=" << engine << " basePrice=" << basePrice << std::endl;
}

std::string Model::toString() const {
    std::ostringstream oss;
    oss << (name ? name : "") << " (" << power << "ch, ";
    switch (engine) {
        case Petrol: oss << "essence"; break;
        case Diesel: oss << "diesel"; break;
        case Electric: oss << "electrique"; break;
        case Hybrid: oss << "hybride"; break;
    }
    oss << ", " << basePrice << "€)";
    return oss.str();
}


std::ostream& operator<<(std::ostream& os, const Model& mod) {  
    os << "<Model>\n";
    os << "<name>\n" << (mod.name ? mod.name : "") << "\n</name>\n";
    os << "<power>\n" << mod.power << "\n</power>\n";
    os << "<engine>\n";
    switch (mod.engine) {
        case Petrol: os << "essence"; break;
        case Diesel: os << "diesel"; break;
        case Electric: os << "electrique"; break;
        case Hybrid: os << "hybride"; break;
    }
    os << "\n</engine>\n";
    os << "<basePrice>\n" << mod.basePrice << "\n</basePrice>\n";
    os << "</Model>\n";
    return os;
}

std::istream& operator>>(std::istream& is, Model& mod) {
    std::string line;
    std::string temp;

    
    std::getline(is, line);

    
    std::getline(is, line);      
    std::getline(is, temp);      
    mod.setName(temp.c_str());
    std::getline(is, line);      

    
    std::getline(is, line);      
    std::getline(is, temp);      
    mod.setPower(std::stoi(temp));
    std::getline(is, line);      

        
    std::getline(is, line);              
    std::getline(is, line);              
    if (line == "essence") mod.setEngine(Petrol);
    else if (line == "diesel") mod.setEngine(Diesel);
    else if (line == "electrique") mod.setEngine(Electric);
    else if (line == "hybride") mod.setEngine(Hybrid);
    else mod.setEngine(Petrol);          
    std::getline(is, line);              


    
    std::getline(is, line);      
    std::getline(is, temp);      
    mod.setBasePrice(std::stof(temp));
    std::getline(is, line);      

    
    std::getline(is, line);



    return is;
}

} 
