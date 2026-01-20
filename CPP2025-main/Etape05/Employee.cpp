#include "Employee.h"
#include "PasswordException.h"
#include <sstream>
#include <cctype>

const std::string Employee::ADMINISTRATIVE = "Administratif";
const std::string Employee::SELLER = "Vendeur";

Employee::Employee() : Actor() {
    login = "";
    password = nullptr;
    role = "";
}

Employee::Employee(const std::string& ln, const std::string& fn, int id, const std::string& login, const std::string& role)
    : Actor(ln, fn, id) {
    this->login = login;
    this->password = nullptr;
    this->role = role;
}

Employee::Employee(const Employee& e) : Actor(e) {
    login = e.login;
    if (e.password != nullptr) {
        password = new std::string(*e.password);
    } else {
        password = nullptr;
    }
    role = e.role;
}

Employee::~Employee() {
    if (password != nullptr) {
        delete password;
        password = nullptr;
    }
}

std::string Employee::getLogin() const {
    return login;
}

void Employee::setLogin(const std::string& login) {
    this->login = login;
}

std::string Employee::getPassword() const {
    if (password == nullptr) {
        throw PasswordException("L'employe ne possede pas de mot de passe", PasswordException::NO_PASSWORD);
    }
    return *password;
}

void Employee::setPassword(const std::string& mdp) {
    // Vérifier la longueur du mot de passe
    if (mdp.length() < 6) {
        throw PasswordException("Le mot de passe doit contenir au moins 6 caracteres", PasswordException::INVALID_LENGTH);
    }
    
    
    bool hasAlpha = false;
    for (char c : mdp) {
        if (std::isalpha(c)) {
            hasAlpha = true;
            break;
        }
    }
    if (!hasAlpha) {
        throw PasswordException("Le mot de passe doit contenir au moins une lettre", PasswordException::ALPHA_MISSING);
    }
    
    bool hasDigit = false;
    for (char c : mdp) {
        if (std::isdigit(c)) {
            hasDigit = true;
            break;
        }
    }
    if (!hasDigit) {
        throw PasswordException("Le mot de passe doit contenir au moins un chiffre", PasswordException::DIGIT_MISSING);
    }
    
 
    if (password != nullptr) {
        delete password;
    }
    password = new std::string(mdp);
}

void Employee::resetPassword() {
    if (password != nullptr) {
        delete password;
        password = nullptr;
    }
}

std::string Employee::getRole() const {
    return role;
}

void Employee::setRole(const std::string& role) {
    this->role = role;
}

std::string Employee::tuple() const {
    std::ostringstream oss;
    oss << getId() << ";" << getLastName() << ";" << getFirstName() << ";" << role;
    return oss.str();
}

std::string Employee::toString() const {
    std::ostringstream oss;
    char prefix = (role == SELLER) ? 'V' : 'A';
    oss << "[" << prefix << getId() << "] " << getLastName() << " " << getFirstName();
    return oss.str();
}

Employee& Employee::operator=(const Employee& e) {
    if (this != &e) {
        Actor::operator=(e);
        login = e.login;
        if (e.password != nullptr) {
            if (password != nullptr) {
                *password = *e.password;
            } else {
                password = new std::string(*e.password);
            }
        } else {
            if (password != nullptr) {
                delete password;
                password = nullptr;
            }
        }
        role = e.role;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Employee& e) {
    os << e.toString();
    return os;
}