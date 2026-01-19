#ifndef PERSON_H
#define PERSON_H

#include <ostream>
#include <istream>
#include <string>

class Person {
    private: 
        std::string lastName;
        std::string firstName;
    
    public:
        Person(); // constructeur par défaut
        Person(const std::string& ln, const std::string& fn); // constructeur d'initialisation
        Person(const Person& p); // constructeur de copie
            
        // getters
        std::string getLastName() const;
        std::string getFirstName() const;
    
        // setters
        void setLastName(const std::string& ln);
        void setFirstName(const std::string& fn);
    
        // operators
        friend std::ostream& operator<<(std::ostream& os, const Person& p);
        friend std::istream& operator>>(std::istream& is, Person& p);
        Person& operator=(const Person& p);
        virtual ~Person();
    };

#endif