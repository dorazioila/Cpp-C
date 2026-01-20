#include "Actor.h"

Actor::Actor() : Person() {
    id = 0;
}

Actor::Actor(const std::string& ln, const std::string& fn, int id) : Person(ln,fn)
{
    setId(id);
}

Actor::Actor(const Actor& a) : Person(a) {
    id = a.id;
}

int Actor::getId() const {
    return id;
}

void Actor::setId(int id) {
    this->id = id;
}

Actor& Actor::operator=(const Actor& a) {
    if (this != &a) {
        Person::operator=(a);
        id = a.id;
    }
    return *this;
}

Actor::~Actor() {
    
}