#ifndef CLIENT_H
#define CLIENT_H

#include "Actor.h"
#include <string>
#include <ostream>
#include <istream>

class Client : public Actor {
    private:
        std::string gsm;

    public:
        Client();
        Client(const std::string& ln, const std::string& fn, int id, const std::string& gsm);
        Client(const Client& c);
        ~Client();

        std::string getGsm() const;
        void setGsm(const std::string& gsm);

        virtual std::string tuple() const override;
        virtual std::string toString() const override;

        Client& operator=(const Client& c);
        friend std::ostream& operator<<(std::ostream& os, const Client& c);
        friend std::istream& operator>>(std::istream& is, Client& c); // ajouté pour désérialisation
};

#endif // CLIENT_H
