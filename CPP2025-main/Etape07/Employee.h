#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Actor.h"
#include <string>
#include <ostream>

class Employee : public Actor {
    private:
        std::string login;
        std::string* password;
        std::string role;

    public:
        Employee();
        Employee(const std::string& ln, const std::string& fn, int id, const std::string& login, const std::string& role);
        Employee(const Employee& e);
        ~Employee();

        static const std::string ADMINISTRATIVE;
        static const std::string SELLER;

        std::string getLogin() const;
        void setLogin(const std::string& login);

        std::string getPassword() const;
        void setPassword(const std::string& mdp);
        void resetPassword();

        std::string getRole() const;
        void setRole(const std::string& role);

        virtual std::string tuple() const override;
        virtual std::string toString() const override;

        Employee& operator=(const Employee& e);
        friend std::ostream& operator<<(std::ostream& os, const Employee& e);
};

#endif