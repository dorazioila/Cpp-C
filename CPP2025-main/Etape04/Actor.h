#ifndef ACTOR_H
#define ACTOR_H

#include "Person.h"
#include <string>

class Actor : public Person {
    private:
        int id;

    public:
        Actor();
        Actor(const std::string& ln, const std::string& fn, int id);
        Actor(const Actor& a);

        int getId() const;
        void setId(int id);

        virtual std::string tuple() const = 0;
        virtual std::string toString() const = 0;

        Actor& operator=(const Actor& a);
        virtual ~Actor();
    };

#endif