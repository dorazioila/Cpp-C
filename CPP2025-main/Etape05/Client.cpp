#include "Client.h"
#include <sstream>

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

std::ostream& operator<<(std::ostream& os, const Client& c) {
    os << c.toString();
    return os;
}