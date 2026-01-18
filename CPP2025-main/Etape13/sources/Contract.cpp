#include "Contract.h"
#include <sstream>
#include <iostream>

Contract::Contract(): id(0), vendeurId(0), clientId(0), projectName("") {}
Contract::Contract(int id, int vendeurId, int clientId, const std::string& projectName): id(id), vendeurId(vendeurId), clientId(clientId), projectName(projectName) {}
int Contract::getId() const 
{ 
    return id; 
}
int Contract::getVendeurId() const 
{ 
    return vendeurId; 
}
int Contract::getClientId() const 
{ 
    return clientId; 
}
std::string Contract::getProjectName() const 
{ 
    return projectName; 
}
std::string Contract::tuple() const
{
    std::ostringstream oss;
    oss << id << ";" << vendeurId << ";" << clientId << ";" << projectName;
    return oss.str();
}

bool Contract::operator<(const Contract& other) const
{
    return id < other.id;
}

std::ostream& operator<<(std::ostream& os, const Contract& c)
{
    os << "<Contract>\n";
    os << "<id>\n" << c.id << "\n</id>\n";
    os << "<vendeurId>\n" << c.vendeurId << "\n</vendeurId>\n";
    os << "<clientId>\n" << c.clientId << "\n</clientId>\n";
    os << "<projectName>\n" << c.projectName << "\n</projectName>\n";
    os << "</Contract>\n";
    return os;
}

std::istream& operator>>(std::istream& is, Contract& c)
{
    std::string line, tmp;

    std::getline(is, line);

    std::getline(is, line); std::getline(is, tmp); c.id = std::stoi(tmp); std::getline(is, line);
    std::getline(is, line); std::getline(is, tmp); c.vendeurId = std::stoi(tmp); std::getline(is, line);
    std::getline(is, line); std::getline(is, tmp); c.clientId = std::stoi(tmp); std::getline(is, line);
    std::getline(is, line); std::getline(is, tmp); c.projectName = tmp; std::getline(is, line);

    std::getline(is, line);
    return is;
}
