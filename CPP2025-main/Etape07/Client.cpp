#include "Client.h"
#include <sstream>
#include <iostream>

Client::Client() : Actor() {
    gsm = "";
}

Client::Client(const std::string& ln, const std::string& fn, int id, const std::string& gsm) 
    : Actor(ln, fn, id) {
    this->gsm = gsm;
}

Client::Client(const Client& c) : Actor(c) {
    gsm = c.gsm;
}

Client::~Client() {
}

std::string Client::getGsm() const {
    return gsm;
}

void Client::setGsm(const std::string& gsm) {
    this->gsm = gsm;
}

std::string Client::tuple() const {
    std::ostringstream oss;
    oss << getId() << ";" << getLastName() << ";" << getFirstName() << ";" << gsm;
    return oss.str();
}

std::string Client::toString() const {
    std::ostringstream oss;
    oss << "[C" << getId() << "] " << getLastName() << " " << getFirstName();
    return oss.str();
}

Client& Client::operator=(const Client& c) {
    if (this != &c) {
        Actor::operator=(c);
        gsm = c.gsm;
    }
    return *this;
}


std::ostream& operator<<(std::ostream& s, const Client& c) {
    s << "<Client>\n";

    s << "<lastName>\n"
      << c.getLastName() << "\n"
      << "</lastName>\n";

    s << "<firstName>\n"
      << c.getFirstName() << "\n"
      << "</firstName>\n";

    s << "<id>\n"
      << c.getId() << "\n"
      << "</id>\n";

    s << "<gsm>\n"
      << c.getGsm() << "\n"
      << "</gsm>\n";

    s << "</Client>\n";

    return s;
}


std::istream& operator>>(std::istream& s, Client& c) {
    std::string tag;

    
    std::getline(s, tag);

    
    std::getline(s, tag);              
    std::string tmpLastName;
    std::getline(s, tmpLastName);      
    c.setLastName(tmpLastName);
    std::getline(s, tag);              

    
    std::getline(s, tag);              
    std::string tmpFirstName;
    std::getline(s, tmpFirstName);     
    c.setFirstName(tmpFirstName);
    std::getline(s, tag);              

    
    std::getline(s, tag);              
    int tmpId;
    std::getline(s, tag);              
    tmpId = std::stoi(tag);
    c.setId(tmpId);
    std::getline(s, tag);              

    
    std::getline(s, tag);              
    std::string tmpGsm;
    std::getline(s, tmpGsm);           
    c.setGsm(tmpGsm);
    std::getline(s, tag);              

    
    std::getline(s, tag);

    return s;
}

