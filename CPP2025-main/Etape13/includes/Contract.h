#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>

class Contract
{
private:
    int id;
    int vendeurId;         
    int clientId;          
    std::string projectName;
public:
    Contract();
    Contract(int id, int vendeurId, int clientId, const std::string& projectName);
    int getId() const;
    int getVendeurId() const;
    int getClientId() const;
    std::string getProjectName() const;
    std::string tuple() const;
    bool operator<(const Contract& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Contract& c);
    friend std::istream& operator>>(std::istream& is, Contract& c);
};

#endif
