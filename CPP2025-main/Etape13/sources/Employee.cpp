#include "Employee.h"
#include "PasswordException.h"
#include <sstream>
#include <cctype>

const std::string Employee::ADMINISTRATIVE = "Administratif";
const std::string Employee::SELLER = "Vendeur";

Employee::Employee() : Actor() {
    login = "";
    role = "";
    password = "";
    hasPassword = false;

}

Employee::Employee(const std::string& ln, const std::string& fn, int id, const std::string& login, const std::string& role) : Actor(ln, fn, id) {
    this->login = login;
    this->role = role;
    this->password = "";
    this->hasPassword = false;
}

Employee::Employee(const Employee& e) : Actor(e)
{
    login = e.login;
    password = e.password;
    hasPassword = e.hasPassword;
    role = e.role;
}

Employee::~Employee() = default;

std::string Employee::getLogin() const {
    return login;
}

void Employee::setLogin(const std::string& login) {
    this->login = login;
}

std::string Employee::getPassword() const {
    if (!hasPassword){
        throw PasswordException("L'employe ne possede pas de mot de passe",PasswordException::NO_PASSWORD);
    }
    return password;
}

void Employee::setPassword(const std::string& mdp) {
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
    
    password = mdp;        
    hasPassword = true;    
}

void Employee::resetPassword() {
    password = "";
    hasPassword = false;
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

Employee& Employee::operator=(const Employee& e)
{
    if (this != &e)
    {
        Actor::operator=(e);
        login = e.login;
        password = e.password;
        hasPassword = e.hasPassword;
        role = e.role;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Employee& e)
{
    os << "<Employee>\n";
    os << "<id>\n" << e.getId() << "\n</id>\n";
    os << "<lastName>\n" << e.getLastName() << "\n</lastName>\n";
    os << "<firstName>\n" << e.getFirstName() << "\n</firstName>\n";
    os << "<login>\n" << e.getLogin() << "\n</login>\n";
    os << "<role>\n" << e.getRole() << "\n</role>\n";
    os << "</Employee>\n";
    return os;
}

std::istream& operator>>(std::istream& is, Employee& e)
{
    std::string tmp, line;

    std::getline(is, line); 

    std::getline(is, line); std::getline(is, tmp); e.setId(std::stoi(tmp)); std::getline(is, line);
    std::getline(is, line); std::getline(is, tmp); e.setLastName(tmp); std::getline(is, line);
    std::getline(is, line); std::getline(is, tmp); e.setFirstName(tmp); std::getline(is, line);
    std::getline(is, line); std::getline(is, tmp); e.setLogin(tmp); std::getline(is, line);
    std::getline(is, line); std::getline(is, tmp); e.setRole(tmp); std::getline(is, line);

    std::getline(is, line);
    return is;
}